#ifndef COSTMAP_2D_COSTMAP_2D_ROS_H_
#define COSTMAP_2D_COSTMAP_2D_ROS_H_

#include "costmap/costmap_ros/layered_costmap.h"
#include "costmap/layers/layer.h"
#include "costmap/costmap_ros/costmap_2d_publisher.h"
#include "costmap/Costmap2DConfig.h"
#include "costmap/utils/footprint.h"
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <dynamic_reconfigure/server.h>
#include <pluginlib/class_loader.hpp>
#include <tf2/LinearMath/Transform.h>

class SuperValue : public XmlRpc::XmlRpcValue
{
public: 
  void setStruct(XmlRpc::XmlRpcValue::ValueStruct *a)
  {
    _type = TypeStruct;
    _value.asStruct = new XmlRpc::XmlRpcValue::ValueStruct(*a);
  }
  void setArray(XmlRpc::XmlRpcValue::ValueArray *a)
  {
    _type = TypeArray;
    _value.asArray = new std::vector<XmlRpc::XmlRpcValue>(*a);
  }
};

namespace UstarCostmap
{

  /** @brief A ROS wrapper for a 2D Costmap. Handles subscribing to
 * topics that provide observations about obstacles in either the form
 * of PointCloud or LaserScan messages. */
  class Costmap2DROS
  {
  public:
    /**
   * @brief  Constructor for the wrapper
   * @param name The name for this costmap
   * @param tf A reference to a TransformListener
   */
    Costmap2DROS(const std::string &name, tf2_ros::Buffer &tf);
    ~Costmap2DROS();

    /**
   * @brief  Subscribes to sensor topics if necessary and starts costmap
   * updates, can be called to restart the costmap after calls to either
   * stop() or pause()
   */
    void start();

    /**
   * @brief  Stops costmap updates and unsubscribes from sensor topics
   */
    void stop();

    /**
   * @brief  Stops the costmap from updating, but sensor data still comes in over the wire
   */
    void pause();

    /**
   * @brief  Resumes costmap updates
   */
    void resume();

    void updateMap();

    /**
   * @brief Reset each individual layer
   */
    void resetLayers();

    /** @brief Same as getLayeredCostmap()->isCurrent(). */
    bool isCurrent() const
    {
      return layered_costmap_->isCurrent();
    }

    /**
   * @brief Is the costmap stopped
   */
    bool isStopped() const
    {
      return stopped_;
    }

    /**
   * @brief Get the pose of the robot in the global frame of the costmap
   * @param global_pose Will be set to the pose of the robot in the global frame of the costmap
   * @return True if the pose was set successfully, false otherwise
   */
    bool getRobotPose(geometry_msgs::PoseStamped &global_pose) const;

    /** @brief Returns costmap name */
    std::string getName() const
    {
      return name_;
    }

    /** @brief Returns the delay in transform (tf) data that is tolerable in seconds */
    double getTransformTolerance() const
    {
      return transform_tolerance_;
    }

    /** @brief Return a pointer to the "master" costmap which receives updates from all the layers.
   *
   * Same as calling getLayeredCostmap()->getCostmap(). */
    Costmap2D *getCostmap() const
    {
      return layered_costmap_->getCostmap();
    }

    /**
   * @brief  Returns the global frame of the costmap
   * @return The global frame of the costmap
   */
    std::string getGlobalFrameID() const
    {
      return global_frame_;
    }

    /**
   * @brief  Returns the local frame of the costmap
   * @return The local frame of the costmap
   */
    std::string getBaseFrameID() const
    {
      return robot_base_frame_;
    }
    LayeredCostmap *getLayeredCostmap() const
    {
      return layered_costmap_;
    }

    /** @brief Returns the current padded footprint as a geometry_msgs::Polygon. */
    geometry_msgs::Polygon getRobotFootprintPolygon() const
    {
      return UstarCostmap::toPolygon(padded_footprint_);
    }

    /** @brief Return the current footprint of the robot as a vector of points.
   *
   * This version of the footprint is padded by the footprint_padding_
   * distance, set in the rosparam "footprint_padding".
   *
   * The footprint initially comes from the rosparam "footprint" but
   * can be overwritten by dynamic reconfigure or by messages received
   * on the "footprint" topic. */
    std::vector<geometry_msgs::Point> getRobotFootprint() const
    {
      return padded_footprint_;
    }

    /** @brief Return the current unpadded footprint of the robot as a vector of points.
   *
   * This is the raw version of the footprint without padding.
   *
   * The footprint initially comes from the rosparam "footprint" but
   * can be overwritten by dynamic reconfigure or by messages received
   * on the "footprint" topic. */
    std::vector<geometry_msgs::Point> getUnpaddedRobotFootprint() const
    {
      return unpadded_footprint_;
    }

    /**
   * @brief  Build the oriented footprint of the robot at the robot's current pose
   * @param  oriented_footprint Will be filled with the points in the oriented footprint of the robot
   */
    void getOrientedFootprint(std::vector<geometry_msgs::Point> &oriented_footprint) const;

    /** @brief Set the footprint of the robot to be the given set of
   * points, padded by footprint_padding.
   *
   * Should be a convex polygon, though this is not enforced.
   *
   * First expands the given polygon by footprint_padding_ and then
   * sets padded_footprint_ and calls
   * layered_costmap_->setFootprint().  Also saves the unpadded
   * footprint, which is available from
   * getUnpaddedRobotFootprint(). */
    void setUnpaddedRobotFootprint(const std::vector<geometry_msgs::Point> &points);

    /** @brief Set the footprint of the robot to be the given polygon,
   * padded by footprint_padding.
   *
   * Should be a convex polygon, though this is not enforced.
   *
   * First expands the given polygon by footprint_padding_ and then
   * sets padded_footprint_ and calls
   * layered_costmap_->setFootprint().  Also saves the unpadded
   * footprint, which is available from
   * getUnpaddedRobotFootprint(). */
    void setUnpaddedRobotFootprintPolygon(const geometry_msgs::Polygon &footprint);

  protected:
    LayeredCostmap *layered_costmap_;
    std::string name_;
    tf2_ros::Buffer &tf_;          ///< @brief Used for transforming point clouds
    std::string global_frame_;     ///< @brief The global frame for the costmap
    std::string robot_base_frame_; ///< @brief The frame_id of the robot base
    double transform_tolerance_;   ///< timeout before transform errors

  private:
    /** @brief Set the footprint from the new_config object.
   *
   * If the values of footprint and robot_radius are the same in
   * new_config and old_config, nothing is changed. */
    void readFootprintFromConfig(const UstarCostmap::Costmap2DConfig &new_config,
                                 const UstarCostmap::Costmap2DConfig &old_config);

    void loadOldParameters(ros::NodeHandle &nh);
    void warnForOldParameters(ros::NodeHandle &nh);
    void checkOldParam(ros::NodeHandle &nh, const std::string &param_name);
    void copyParentParameters(const std::string &plugin_name, const std::string &plugin_type, ros::NodeHandle &nh);
    void reconfigureCB(UstarCostmap::Costmap2DConfig &config, uint32_t level);
    void movementCB(const ros::TimerEvent &event);
    void mapUpdateLoop(double frequency);
    bool map_update_thread_shutdown_;
    bool stop_updates_, initialized_, stopped_, robot_stopped_;
    boost::thread *map_update_thread_; ///< @brief A thread for updating the map
    ros::Timer timer_;
    ros::Time last_publish_;
    ros::Duration publish_cycle;
    pluginlib::ClassLoader<Layer> plugin_loader_;
    geometry_msgs::PoseStamped old_pose_;
    Costmap2DPublisher *publisher_;
    dynamic_reconfigure::Server<UstarCostmap::Costmap2DConfig> *dsrv_;

    boost::recursive_mutex configuration_mutex_;

    ros::Subscriber footprint_sub_;
    ros::Publisher footprint_pub_;
    std::vector<geometry_msgs::Point> unpadded_footprint_;
    std::vector<geometry_msgs::Point> padded_footprint_;
    float footprint_padding_;
    UstarCostmap::Costmap2DConfig old_config_;
  };
  // class Costmap2DROS
} // namespace UstarCostmap

#endif // COSTMAP_2D_COSTMAP_2D_ROS_H
