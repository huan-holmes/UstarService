#include "gmapping/gmapping.h"
#include <iostream>
#include <time.h>
#include "ros/ros.h"
#include "ros/console.h"
#include "nav_msgs/MapMetaData.h"
#include "gmapping/sensor/rangesensor.h"
#include "gmapping/sensor/odometrysensor.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

// compute linear index for given map coords
#define MAP_IDX(sx, i, j) ((sx) * (j) + (i))
namespace UstarSlam
{
  UstarGMapping::UstarGMapping() : map_to_odom_(tf::Transform(tf::createQuaternionFromRPY(0, 0, 0), tf::Point(0, 0, 0))),
                                   laser_count_(0), private_nh_("~"), scan_filter_sub_(NULL), scan_filter_(NULL), transform_thread_(NULL)
  {
    seed_ = time(NULL);
    init();
  }

  UstarGMapping::UstarGMapping(ros::NodeHandle &nh, ros::NodeHandle &pnh) : 
                               map_to_odom_(tf::Transform(tf::createQuaternionFromRPY(0, 0, 0), tf::Point(0, 0, 0))),
                               laser_count_(0), node_(nh), private_nh_(pnh), scan_filter_sub_(NULL), scan_filter_(NULL), transform_thread_(NULL)
  {
    seed_ = time(NULL);
    init();
  } 

  UstarGMapping::UstarGMapping(long unsigned int seed, long unsigned int max_duration_buffer) : 
                               map_to_odom_(tf::Transform(tf::createQuaternionFromRPY(0, 0, 0), tf::Point(0, 0, 0))),
                               laser_count_(0), private_nh_("~"), scan_filter_sub_(NULL), scan_filter_(NULL), transform_thread_(NULL),
                               seed_(seed), tf_(ros::Duration(max_duration_buffer))
  {
    init();
  }

  void UstarGMapping::init()
  {
    // log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME)->setLevel(ros::console::g_level_lookup[ros::console::levels::Debug]);

    // The library is pretty chatty
    //gsp_ = new GMapping::GridSlamProcessor(std::cerr);
    gsp_ = new UstarSlam::MatchProcessor();
    ROS_ASSERT(gsp_);

    tfB_ = new tf::TransformBroadcaster();
    ROS_ASSERT(tfB_);

    gsp_laser_ = NULL;
    gsp_odom_ = NULL;

    got_first_scan_ = false;
    got_map_ = false;

    // Parameters used by our GMapping wrapper
    if (!private_nh_.getParam("throttle_scans", throttle_scans_))
      throttle_scans_ = 1;
    if (!private_nh_.getParam("base_frame", base_frame_))
      base_frame_ = "base_link";
    if (!private_nh_.getParam("map_frame", map_frame_))
      map_frame_ = "map";
    if (!private_nh_.getParam("odom_frame", odom_frame_))
      odom_frame_ = "odom";

    private_nh_.param("transform_publish_period", transform_publish_period_, 0.05);

    double tmp;
    if (!private_nh_.getParam("map_update_interval", tmp))
      tmp = 5.0;
    map_update_interval_.fromSec(tmp);

    // Parameters used by GMapping itself
    maxUrange_ = 0.0;
    maxRange_ = 0.0; // preliminary default, will be set in initMapper()
    if (!private_nh_.getParam("minimumScore", minimum_score_))
      minimum_score_ = 0;
    if (!private_nh_.getParam("sigma", sigma_))
      sigma_ = 0.05;
    if (!private_nh_.getParam("kernelSize", kernelSize_))
      kernelSize_ = 1;
    if (!private_nh_.getParam("lstep", lstep_))
      lstep_ = 0.05;
    if (!private_nh_.getParam("astep", astep_))
      astep_ = 0.05;
    if (!private_nh_.getParam("iterations", iterations_))
      iterations_ = 5;
    if (!private_nh_.getParam("lsigma", lsigma_))
      lsigma_ = 0.075;
    if (!private_nh_.getParam("ogain", ogain_))
      ogain_ = 3.0;
    if (!private_nh_.getParam("lskip", lskip_))
      lskip_ = 0;
    if (!private_nh_.getParam("srr", srr_))
      srr_ = 0.1;
    if (!private_nh_.getParam("srt", srt_))
      srt_ = 0.2;
    if (!private_nh_.getParam("str", str_))
      str_ = 0.1;
    if (!private_nh_.getParam("stt", stt_))
      stt_ = 0.2;
    if (!private_nh_.getParam("linearUpdate", linearUpdate_))
      linearUpdate_ = 1.0;
    if (!private_nh_.getParam("angularUpdate", angularUpdate_))
      angularUpdate_ = 0.5;
    if (!private_nh_.getParam("temporalUpdate", temporalUpdate_))
      temporalUpdate_ = -1.0;
    if (!private_nh_.getParam("resampleThreshold", resampleThreshold_))
      resampleThreshold_ = 0.5;
    if (!private_nh_.getParam("particles", particles_))
      particles_ = 30;
    if (!private_nh_.getParam("xmin", xmin_))
      xmin_ = -100.0;
    if (!private_nh_.getParam("ymin", ymin_))
      ymin_ = -100.0;
    if (!private_nh_.getParam("xmax", xmax_))
      xmax_ = 100.0;
    if (!private_nh_.getParam("ymax", ymax_))
      ymax_ = 100.0;
    if (!private_nh_.getParam("delta", delta_))
      delta_ = 0.05;
    if (!private_nh_.getParam("occ_thresh", occ_thresh_))
      occ_thresh_ = 0.25;
    if (!private_nh_.getParam("llsamplerange", llsamplerange_))
      llsamplerange_ = 0.01;
    if (!private_nh_.getParam("llsamplestep", llsamplestep_))
      llsamplestep_ = 0.01;
    if (!private_nh_.getParam("lasamplerange", lasamplerange_))
      lasamplerange_ = 0.005;
    if (!private_nh_.getParam("lasamplestep", lasamplestep_))
      lasamplestep_ = 0.005;

    if (!private_nh_.getParam("tf_delay", tf_delay_))
      tf_delay_ = transform_publish_period_;
  }

  void UstarGMapping::startLiveSlam()
  {
    entropy_publisher_ = private_nh_.advertise<std_msgs::Float64>("entropy", 1, true);
    sst_ = node_.advertise<nav_msgs::OccupancyGrid>("map", 1, true);
    sstm_ = node_.advertise<nav_msgs::MapMetaData>("map_metadata", 1, true);
    ss_ = node_.advertiseService("dynamic_map", &UstarGMapping::mapCallback, this);
    scan_filter_sub_ = new message_filters::Subscriber<sensor_msgs::LaserScan>(node_, "scan", 5);
    scan_filter_ = new tf::MessageFilter<sensor_msgs::LaserScan>(*scan_filter_sub_, tf_, odom_frame_, 5);
    scan_filter_->registerCallback(boost::bind(&UstarGMapping::laserCallback, this, _1));

    transform_thread_ = new boost::thread(boost::bind(&UstarGMapping::publishLoop, this, transform_publish_period_));
  }

  void UstarGMapping::startReplay(const std::string &bag_fname, std::string scan_topic)
  {
    double transform_publish_period;
    ros::NodeHandle private_nh_("~");
    entropy_publisher_ = private_nh_.advertise<std_msgs::Float64>("entropy", 1, true);
    sst_ = node_.advertise<nav_msgs::OccupancyGrid>("map", 1, true);
    sstm_ = node_.advertise<nav_msgs::MapMetaData>("map_metadata", 1, true);
    ss_ = node_.advertiseService("dynamic_map", &UstarGMapping::mapCallback, this);

    rosbag::Bag bag;
    bag.open(bag_fname, rosbag::bagmode::Read);

    std::vector<std::string> topics;
    topics.push_back(std::string("/tf"));
    topics.push_back(scan_topic);
    rosbag::View viewall(bag, rosbag::TopicQuery(topics));

    // Store up to 5 messages and there error message (if they cannot be processed right away)
    std::queue<std::pair<sensor_msgs::LaserScan::ConstPtr, std::string> > s_queue;
    foreach (rosbag::MessageInstance const m, viewall)
    {
      tf::tfMessage::ConstPtr cur_tf = m.instantiate<tf::tfMessage>();
      if (cur_tf != NULL)
      {
        for (size_t i = 0; i < cur_tf->transforms.size(); ++i)
        {
          geometry_msgs::TransformStamped transformStamped;
          tf::StampedTransform stampedTf;
          transformStamped = cur_tf->transforms[i];
          tf::transformStampedMsgToTF(transformStamped, stampedTf);
          tf_.setTransform(stampedTf);
        }
      }

      sensor_msgs::LaserScan::ConstPtr s = m.instantiate<sensor_msgs::LaserScan>();
      if (s != NULL)
      {
        if (!(ros::Time(s->header.stamp)).is_zero())
        {
          s_queue.push(std::make_pair(s, ""));
        }
        // Just like in live processing, only process the latest 5 scans
        if (s_queue.size() > 5)
        {
          ROS_WARN_STREAM("Dropping old scan: " << s_queue.front().second);
          s_queue.pop();
        }
        // ignoring un-timestamped tf data
      }

      // Only process a scan if it has tf data
      while (!s_queue.empty())
      {
        try
        {
          tf::StampedTransform t;
          tf_.lookupTransform(s_queue.front().first->header.frame_id, odom_frame_, s_queue.front().first->header.stamp, t);
          this->laserCallback(s_queue.front().first);
          s_queue.pop();
        }
        // If tf does not have the data yet
        catch (tf2::TransformException &e)
        {
          // Store the error to display it if we cannot process the data after some time
          s_queue.front().second = std::string(e.what());
          break;
        }
      }
    }

    bag.close();
  }

  void UstarGMapping::publishLoop(double transform_publish_period)
  {
    if (transform_publish_period == 0)
      return;

    ros::Rate r(1.0 / transform_publish_period);
    while (ros::ok())
    {
      publishTransform();
      r.sleep();
    }
  }

  UstarGMapping::~UstarGMapping()
  {
    if (transform_thread_)
    {
      transform_thread_->join();
      delete transform_thread_;
    }

    delete gsp_;
    if (gsp_laser_)
      delete gsp_laser_;
    if (gsp_odom_)
      delete gsp_odom_;
    if (scan_filter_)
      delete scan_filter_;
    if (scan_filter_sub_)
      delete scan_filter_sub_;
  }

  bool UstarGMapping::getOdomPose(UstarSlam::OrientedPoint &gmap_pose, const ros::Time &t)
  {
    // Get the pose of the centered laser at the right time
    centered_laser_pose_.stamp_ = t;
    // Get the laser's pose that is centered
    tf::Stamped<tf::Transform> odom_pose;
    try
    {
      tf_.transformPose(odom_frame_, centered_laser_pose_, odom_pose);
    }
    catch (tf::TransformException e)
    {
      ROS_WARN("Failed to compute odom pose, skipping scan (%s)", e.what());
      return false;
    }
    double yaw = tf::getYaw(odom_pose.getRotation());

    gmap_pose = UstarSlam::OrientedPoint(odom_pose.getOrigin().x(),
                                         odom_pose.getOrigin().y(),
                                         yaw);
    return true;
  }

  bool UstarGMapping::initMapper(const sensor_msgs::LaserScan &scan)
  {
    laser_frame_ = scan.header.frame_id;
    // Get the laser's pose, relative to base.
    tf::Stamped<tf::Pose> ident;
    tf::Stamped<tf::Transform> laser_pose;
    ident.setIdentity();
    ident.frame_id_ = laser_frame_;
    ident.stamp_ = scan.header.stamp;
    try
    {
      tf_.transformPose(base_frame_, ident, laser_pose);
    }
    catch (tf::TransformException e)
    {
      ROS_WARN("Failed to compute laser pose, aborting initialization (%s)",
               e.what());
      return false;
    }

    // create a point 1m above the laser position and transform it into the laser-frame
    tf::Vector3 v;
    v.setValue(0, 0, 1 + laser_pose.getOrigin().z());
    tf::Stamped<tf::Vector3> up(v, scan.header.stamp,
                                base_frame_);
    try
    {
      tf_.transformPoint(laser_frame_, up, up);
      ROS_DEBUG("Z-Axis in sensor frame: %.3f", up.z());
    }
    catch (tf::TransformException &e)
    {
      ROS_WARN("Unable to determine orientation of laser: %s",
               e.what());
      return false;
    }

    // gmapping doesnt take roll or pitch into account. So check for correct sensor alignment.
    if (fabs(fabs(up.z()) - 1) > 0.001)
    {
      ROS_WARN("Laser has to be mounted planar! Z-coordinate has to be 1 or -1, but gave: %.5f",
               up.z());
      return false;
    }

    gsp_laser_beam_count_ = scan.ranges.size();

    double angle_center = (scan.angle_min + scan.angle_max) / 2;

    if (up.z() > 0)
    {
      do_reverse_range_ = scan.angle_min > scan.angle_max;
      centered_laser_pose_ = tf::Stamped<tf::Pose>(tf::Transform(tf::createQuaternionFromRPY(0, 0, angle_center),
                                                                 tf::Vector3(0, 0, 0)),
                                                   ros::Time::now(), laser_frame_);
      ROS_INFO("Laser is mounted upwards.");
    }
    else
    {
      do_reverse_range_ = scan.angle_min < scan.angle_max;
      centered_laser_pose_ = tf::Stamped<tf::Pose>(tf::Transform(tf::createQuaternionFromRPY(M_PI, 0, -angle_center),
                                                                 tf::Vector3(0, 0, 0)),
                                                   ros::Time::now(), laser_frame_);
      ROS_INFO("Laser is mounted upside down.");
    }

    // Compute the angles of the laser from -x to x, basically symmetric and in increasing order
    laser_angles_.resize(scan.ranges.size());
    // Make sure angles are started so that they are centered
    double theta = -std::fabs(scan.angle_min - scan.angle_max) / 2;
    for (unsigned int i = 0; i < scan.ranges.size(); ++i)
    {
      laser_angles_[i] = theta;
      theta += std::fabs(scan.angle_increment);
    }
    
    ROS_DEBUG("Laser angles in laser-frame: min: %.3f max: %.3f inc: %.3f", scan.angle_min, scan.angle_max,
              scan.angle_increment);
    ROS_DEBUG("Laser angles in top-down centered laser-frame: min: %.3f max: %.3f inc: %.3f", laser_angles_.front(),
              laser_angles_.back(), std::fabs(scan.angle_increment));
    UstarSlam::OrientedPoint gmap_pose(0, 0, 0);

    // setting maxRange and maxUrange here so we can set a reasonable default
    ros::NodeHandle private_nh_("~");
    if (!private_nh_.getParam("maxRange", maxRange_))
      maxRange_ = scan.range_max - 0.01;
    if (!private_nh_.getParam("maxUrange", maxUrange_))
      maxUrange_ = maxRange_;
    // The laser must be called "FLASER".
    // We pass in the absolute value of the computed angle increment, on the
    // assumption that GMapping requires a positive angle increment.  If the
    // actual increment is negative, we'll swap the order of ranges before
    // feeding each scan to GMapping.
    gsp_laser_ = new UstarSlam::RangeSensor("FLASER",
                                            gsp_laser_beam_count_,
                                            fabs(scan.angle_increment),
                                            gmap_pose,
                                            0.0,
                                            maxRange_);
    ROS_ASSERT(gsp_laser_);
    UstarSlam::SensorMap smap;
    smap.insert(make_pair(gsp_laser_->getName(), gsp_laser_));
    gsp_->setSensorMap(smap);
    gsp_odom_ = new UstarSlam::OdometrySensor(odom_frame_);
    ROS_ASSERT(gsp_odom_);

    /// @todo Expose setting an initial pose
    UstarSlam::OrientedPoint initialPose;
    if (!getOdomPose(initialPose, scan.header.stamp))
    {
      ROS_WARN("Unable to determine inital pose of laser! Starting point will be set to zero.");
      initialPose = UstarSlam::OrientedPoint(0.0, 0.0, 0.0);
    }

    gsp_->setMatchingParameters(maxUrange_, maxRange_, sigma_,
                                kernelSize_, lstep_, astep_, iterations_,
                                lsigma_, ogain_, lskip_);

    gsp_->setMotionModelParameters(srr_, srt_, str_, stt_);
    gsp_->setUpdateDistances(linearUpdate_, angularUpdate_, resampleThreshold_);
    gsp_->setUpdatePeriod(temporalUpdate_);
    gsp_->setgenerateMap(false);
    gsp_->MatchProcessor::init(particles_, xmin_, ymin_, xmax_, ymax_,
                               delta_, initialPose);
    gsp_->setllsamplerange(llsamplerange_);
    gsp_->setllsamplestep(llsamplestep_);
    /// @todo Check these calls; in the gmapping gui, they use
    /// llsamplestep and llsamplerange intead of lasamplestep and
    /// lasamplerange.  It was probably a typo, but who knows.
    gsp_->setlasamplerange(lasamplerange_);
    gsp_->setlasamplestep(lasamplestep_);
    gsp_->setminimumScore(minimum_score_);

    // Call the sampling function once to set the seed.
    UstarSlam::sampleGaussian(1, seed_);

    ROS_INFO("Initialization complete");

    return true;
  }

  bool UstarGMapping::addScan(const sensor_msgs::LaserScan &scan, UstarSlam::OrientedPoint &gmap_pose)
  {
    if (!getOdomPose(gmap_pose, scan.header.stamp))
      return false;

    if (scan.ranges.size() != gsp_laser_beam_count_)
      return false;

    // GMapping wants an array of doubles...
    double *ranges_double = new double[scan.ranges.size()];
    // If the angle increment is negative, we have to invert the order of the readings.
    if (do_reverse_range_)
    {
      ROS_DEBUG("Inverting scan");
      int num_ranges = scan.ranges.size();
      for (int i = 0; i < num_ranges; i++)
      {
        // Must filter out short readings, because the mapper won't
        if (scan.ranges[num_ranges - i - 1] < scan.range_min)
          ranges_double[i] = (double)scan.range_max;
        else
          ranges_double[i] = (double)scan.ranges[num_ranges - i - 1];
      }
    }
    else
    {
      for (unsigned int i = 0; i < scan.ranges.size(); i++)
      {
        // Must filter out short readings, because the mapper won't
        if (scan.ranges[i] < scan.range_min)
          ranges_double[i] = (double)scan.range_max;
        else
          ranges_double[i] = (double)scan.ranges[i];
      }
    }

    UstarSlam::RangeReading reading(scan.ranges.size(),
                                    ranges_double,
                                    gsp_laser_,
                                    scan.header.stamp.toSec());

    // ...but it deep copies them in RangeReading constructor, so we don't
    // need to keep our array around.
    delete[] ranges_double;

    reading.setPose(gmap_pose);

    /*
  ROS_DEBUG("scanpose (%.3f): %.3f %.3f %.3f\n",
            scan.header.stamp.toSec(),
            gmap_pose.x,
            gmap_pose.y,
            gmap_pose.theta);
            */
    ROS_DEBUG("processing scan");

    return gsp_->processScan(reading);
  }

  void UstarGMapping::laserCallback(const sensor_msgs::LaserScan::ConstPtr &scan)
  {
    laser_count_++;
    if ((laser_count_ % throttle_scans_) != 0)
      return;

    static ros::Time last_map_update(0, 0);

    // We can't initialize the mapper until we've got the first scan
    if (!got_first_scan_)
    {
      if (!initMapper(*scan))
        return;
      got_first_scan_ = true;
    }

    UstarSlam::OrientedPoint odom_pose;

    if (addScan(*scan, odom_pose))
    {
      ROS_DEBUG("scan processed");

      UstarSlam::OrientedPoint mpose = gsp_->getParticles()[gsp_->getBestParticleIndex()].pose;
      ROS_DEBUG("new best pose: %.3f %.3f %.3f", mpose.x, mpose.y, mpose.theta);
      ROS_DEBUG("odom pose: %.3f %.3f %.3f", odom_pose.x, odom_pose.y, odom_pose.theta);
      ROS_DEBUG("correction: %.3f %.3f %.3f", mpose.x - odom_pose.x, mpose.y - odom_pose.y, mpose.theta - odom_pose.theta);

      tf::Transform laser_to_map = tf::Transform(tf::createQuaternionFromRPY(0, 0, mpose.theta), tf::Vector3(mpose.x, mpose.y, 0.0)).inverse();
      tf::Transform odom_to_laser = tf::Transform(tf::createQuaternionFromRPY(0, 0, odom_pose.theta), tf::Vector3(odom_pose.x, odom_pose.y, 0.0));

      map_to_odom_mutex_.lock();
      map_to_odom_ = (odom_to_laser * laser_to_map).inverse();
      map_to_odom_mutex_.unlock();

      if (!got_map_ || (scan->header.stamp - last_map_update) > map_update_interval_)
      {
        updateMap(*scan);
        last_map_update = scan->header.stamp;
        ROS_DEBUG("Updated the map");
      }
    }
    else
      ROS_DEBUG("cannot process scan");
  }

  double UstarGMapping::computePoseEntropy()
  {
    double weight_total = 0.0;
    for (std::vector<UstarSlam::MatchProcessor::Particle>::const_iterator it = gsp_->getParticles().begin();
         it != gsp_->getParticles().end();
         ++it)
    {
      weight_total += it->weight;
    }
    double entropy = 0.0;
    for (std::vector<UstarSlam::MatchProcessor::Particle>::const_iterator it = gsp_->getParticles().begin();
         it != gsp_->getParticles().end();
         ++it)
    {
      if (it->weight / weight_total > 0.0)
        entropy += it->weight / weight_total * log(it->weight / weight_total);
    }
    return -entropy;
  }

  void UstarGMapping::
  updateMap(const sensor_msgs::LaserScan &scan)
  {
    ROS_DEBUG("Update map");
    boost::mutex::scoped_lock map_lock(map_mutex_);
    UstarSlam::ScanMatcher matcher;

    matcher.setLaserParameters(scan.ranges.size(), &(laser_angles_[0]),
                               gsp_laser_->getPose());

    matcher.setlaserMaxRange(maxRange_);
    matcher.setusableRange(maxUrange_);
    matcher.setgenerateMap(true);

    UstarSlam::MatchProcessor::Particle best =
        gsp_->getParticles()[gsp_->getBestParticleIndex()];
    std_msgs::Float64 entropy;
    entropy.data = computePoseEntropy();
    if (entropy.data > 0.0)
      entropy_publisher_.publish(entropy);
    if (!got_map_)
    {
      map_.map.info.resolution = delta_;
      map_.map.info.origin.position.x = 0.0;
      map_.map.info.origin.position.y = 0.0;
      map_.map.info.origin.position.z = 0.0;
      map_.map.info.origin.orientation.x = 0.0;
      map_.map.info.origin.orientation.y = 0.0;
      map_.map.info.origin.orientation.z = 0.0;
      map_.map.info.origin.orientation.w = 1.0;
    }
    UstarSlam::Point center;
    center.x = (xmin_ + xmax_) / 2.0;
    center.y = (ymin_ + ymax_) / 2.0;

    UstarSlam::ScanMatcherMap smap(center, xmin_, ymin_, xmax_, ymax_,
                                   delta_);
    ROS_DEBUG("Trajectory tree:");
    for (UstarSlam::MatchProcessor::TNode *n = best.node;
         n;
         n = n->parent)
    {
      ROS_DEBUG("  %.3f %.3f %.3f",
                n->pose.x,
                n->pose.y,
                n->pose.theta);
      if (!n->reading)
      {
        ROS_DEBUG("Reading is NULL");
        continue;
      }
      matcher.invalidateActiveArea();
      matcher.computeActiveArea(smap, n->pose, &((*n->reading)[0]));
      matcher.registerScan(smap, n->pose, &((*n->reading)[0]));
    }

    // the map may have expanded, so resize ros message as well
    if (map_.map.info.width != (unsigned int)smap.getMapSizeX() || map_.map.info.height != (unsigned int)smap.getMapSizeY())
    {

      // NOTE: The results of ScanMatcherMap::getSize() are different from the parameters given to the constructor
      //       so we must obtain the bounding box in a different way
      UstarSlam::Point wmin = smap.map2world(UstarSlam::IntPoint(0, 0));
      UstarSlam::Point wmax = smap.map2world(UstarSlam::IntPoint(smap.getMapSizeX(), smap.getMapSizeY()));
      xmin_ = wmin.x;
      ymin_ = wmin.y;
      xmax_ = wmax.x;
      ymax_ = wmax.y;

      ROS_DEBUG("map size is now %dx%d pixels (%f,%f)-(%f, %f)", smap.getMapSizeX(), smap.getMapSizeY(),
                xmin_, ymin_, xmax_, ymax_);

      map_.map.info.width = smap.getMapSizeX();
      map_.map.info.height = smap.getMapSizeY();
      map_.map.info.origin.position.x = xmin_;
      map_.map.info.origin.position.y = ymin_;
      map_.map.data.resize(map_.map.info.width * map_.map.info.height);

      ROS_DEBUG("map origin: (%f, %f)", map_.map.info.origin.position.x, map_.map.info.origin.position.y);
    }
    for (int x = 0; x < smap.getMapSizeX(); x++)
    {
      for (int y = 0; y < smap.getMapSizeY(); y++)
      {
        /// @todo Sort out the unknown vs. free vs. obstacle thresholding
        UstarSlam::IntPoint p(x, y);
        double occ = smap.cell(p);
        
        assert(occ <= 1.0);

        if (occ < 0)
 
          map_.map.data[MAP_IDX(map_.map.info.width, x, y)] = -1;
          //ROS_INFO_STREAM(MAP_IDX(map_.map.info.width, x, y));
     
        else if (occ > occ_thresh_)
        {
          //map_.map.data[MAP_IDX(map_.map.info.width, x, y)] = (int)round(occ*100.0);
          map_.map.data[MAP_IDX(map_.map.info.width, x, y)] = 100;
        }
        else
          map_.map.data[MAP_IDX(map_.map.info.width, x, y)] = 0;
      }
    }
    got_map_ = true;

    //make sure to set the header information on the map
    map_.map.header.stamp = ros::Time::now();
    map_.map.header.frame_id = tf_.resolve(map_frame_);

    sst_.publish(map_.map);
    sstm_.publish(map_.map.info);
  }

  bool UstarGMapping::mapCallback(nav_msgs::GetMap::Request &req,
                             nav_msgs::GetMap::Response &res)
  {
    boost::mutex::scoped_lock map_lock(map_mutex_);
    if (got_map_ && map_.map.info.width && map_.map.info.height)
    {
      res = map_;
      return true;
    }
    else
      return false;
  }

  void UstarGMapping::publishTransform()
  {
    map_to_odom_mutex_.lock();
    ros::Time tf_expiration = ros::Time::now() + ros::Duration(tf_delay_);
    tfB_->sendTransform(tf::StampedTransform(map_to_odom_, tf_expiration, map_frame_, odom_frame_));
    map_to_odom_mutex_.unlock();
  }
}; // namespace UstarSlam