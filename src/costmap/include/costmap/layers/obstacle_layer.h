#ifndef COSTMAP_2D_OBSTACLE_LAYER_H_
#define COSTMAP_2D_OBSTACLE_LAYER_H_

#include <ros/ros.h>
#include "costmap/layers/costmap_layer.h"
#include "costmap/costmap_ros/layered_costmap.h"
#include "costmap/utils/observation_buffer.h"

#include <nav_msgs/OccupancyGrid.h>

#include <sensor_msgs/LaserScan.h>
#include <laser_geometry/laser_geometry.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <tf2_ros/message_filter.h>
#include <message_filters/subscriber.h>
#include <dynamic_reconfigure/server.h>
#include <costmap/ObstaclePluginConfig.h>
#include "costmap/utils/footprint.h"

namespace UstarCostmap
{

  class ObstacleLayer : public CostmapLayer
  {
  public:
    ObstacleLayer()
    {
      costmap_ = NULL; // this is the unsigned char* member of parent class Costmap2D.
    }

    virtual ~ObstacleLayer();
    virtual void onInitialize();
    virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double *min_x, double *min_y,
                              double *max_x, double *max_y);
    virtual void updateCosts(UstarCostmap::Costmap2D &master_grid, int min_i, int min_j, int max_i, int max_j);

    virtual void activate();
    virtual void deactivate();
    virtual void reset();

    /**
   * @brief  A callback to handle buffering LaserScan messages
   * @param message The message returned from a message notifier
   * @param buffer A pointer to the observation buffer to update
   */
    void laserScanCallback(const sensor_msgs::LaserScanConstPtr &message,
                           const boost::shared_ptr<UstarCostmap::ObservationBuffer> &buffer);

    /**
    * @brief A callback to handle buffering LaserScan messages which need filtering to turn Inf values into range_max.
    * @param message The message returned from a message notifier
    * @param buffer A pointer to the observation buffer to update
    */
    void laserScanValidInfCallback(const sensor_msgs::LaserScanConstPtr &message,
                                   const boost::shared_ptr<ObservationBuffer> &buffer);

    /**
   * @brief  A callback to handle buffering PointCloud messages
   * @param message The message returned from a message notifier
   * @param buffer A pointer to the observation buffer to update
   */
    void pointCloudCallback(const sensor_msgs::PointCloudConstPtr &message,
                            const boost::shared_ptr<UstarCostmap::ObservationBuffer> &buffer);

    /**
   * @brief  A callback to handle buffering PointCloud2 messages
   * @param message The message returned from a message notifier
   * @param buffer A pointer to the observation buffer to update
   */
    void pointCloud2Callback(const sensor_msgs::PointCloud2ConstPtr &message,
                             const boost::shared_ptr<UstarCostmap::ObservationBuffer> &buffer);

    // for testing purposes
    void addStaticObservation(UstarCostmap::Observation &obs, bool marking, bool clearing);
    void clearStaticObservations(bool marking, bool clearing);

  protected:
    virtual void setupDynamicReconfigure(ros::NodeHandle &nh);

    /**
   * @brief  Get the observations used to mark space
   * @param marking_observations A reference to a vector that will be populated with the observations
   * @return True if all the observation buffers are current, false otherwise
   */
    bool getMarkingObservations(std::vector<UstarCostmap::Observation> &marking_observations) const;

    /**
   * @brief  Get the observations used to clear space
   * @param clearing_observations A reference to a vector that will be populated with the observations
   * @return True if all the observation buffers are current, false otherwise
   */
    bool getClearingObservations(std::vector<UstarCostmap::Observation> &clearing_observations) const;

    /**
   * @brief  Clear freespace based on one observation
   * @param clearing_observation The observation used to raytrace
   * @param min_x
   * @param min_y
   * @param max_x
   * @param max_y
   */
    virtual void raytraceFreespace(const UstarCostmap::Observation &clearing_observation, double *min_x, double *min_y,
                                   double *max_x, double *max_y);

    void updateRaytraceBounds(double ox, double oy, double wx, double wy, double range, double *min_x, double *min_y,
                              double *max_x, double *max_y);

    std::vector<geometry_msgs::Point> transformed_footprint_;
    bool footprint_clearing_enabled_;
    void updateFootprint(double robot_x, double robot_y, double robot_yaw, double *min_x, double *min_y,
                         double *max_x, double *max_y);

    std::string global_frame_;   ///< @brief The global frame for the costmap
    double max_obstacle_height_; ///< @brief Max Obstacle Height

    laser_geometry::LaserProjection projector_; ///< @brief Used to project laser scans into point clouds

    std::vector<boost::shared_ptr<message_filters::SubscriberBase> > observation_subscribers_; ///< @brief Used for the observation message filters
    std::vector<boost::shared_ptr<tf2_ros::MessageFilterBase> > observation_notifiers_;        ///< @brief Used to make sure that transforms are available for each sensor
    std::vector<boost::shared_ptr<UstarCostmap::ObservationBuffer> > observation_buffers_;       ///< @brief Used to store observations from various sensors
    std::vector<boost::shared_ptr<UstarCostmap::ObservationBuffer> > marking_buffers_;           ///< @brief Used to store observation buffers used for marking obstacles
    std::vector<boost::shared_ptr<UstarCostmap::ObservationBuffer> > clearing_buffers_;          ///< @brief Used to store observation buffers used for clearing obstacles

    // Used only for testing purposes
    std::vector<UstarCostmap::Observation> static_clearing_observations_, static_marking_observations_;

    bool rolling_window_;
    dynamic_reconfigure::Server<UstarCostmap::ObstaclePluginConfig> *dsrv_;

    int combination_method_;

  private:
    void reconfigureCB(UstarCostmap::ObstaclePluginConfig &config, uint32_t level);
  };

} // namespace UstarCostmap

#endif // COSTMAP_2D_OBSTACLE_LAYER_H_
