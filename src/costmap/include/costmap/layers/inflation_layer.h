#ifndef COSTMAP_2D_INFLATION_LAYER_H_
#define COSTMAP_2D_INFLATION_LAYER_H_

#include <ros/ros.h>
#include "costmap/layers/layer.h"
#include "costmap/costmap_ros/layered_costmap.h"
#include "costmap/InflationPluginConfig.h"
#include <dynamic_reconfigure/server.h>
#include <boost/thread.hpp>

namespace UstarCostmap
{
  /**
   * @class CellData
   * @brief Storage for cell information used during obstacle inflation
   */
  class CellData
  {
    public:
      /**
       * @brief  Constructor for a CellData objects
       * @param  i The index of the cell in the cost map
       * @param  x The x coordinate of the cell in the cost map
       * @param  y The y coordinate of the cell in the cost map
       * @param  sx The x coordinate of the closest obstacle cell in the costmap
       * @param  sy The y coordinate of the closest obstacle cell in the costmap
       * @return
       */
      CellData(double i, unsigned int x, unsigned int y, unsigned int sx, unsigned int sy) : index_(i), x_(x), y_(y), src_x_(sx), src_y_(sy)
      {
      }
      unsigned int index_; 
      unsigned int x_, y_;
      unsigned int src_x_, src_y_;
  };

  class InflationLayer : public Layer
  {
  public:
    InflationLayer();

    virtual ~InflationLayer()
    {
      deleteKernels();
      if (dsrv_)
        delete dsrv_;
      if (seen_)
        delete[] seen_;
    }

    virtual void onInitialize();
    virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double *min_x, double *min_y,
                              double *max_x, double *max_y);
    virtual void updateCosts(UstarCostmap::Costmap2D &master_grid, int min_i, int min_j, int max_i, int max_j);
    virtual bool isDiscretized()
    {
      return true;
    }
    virtual void matchSize();

    virtual void reset() { onInitialize(); }

    /** @brief  Given a distance, compute a cost.
     * @param  distance The distance from an obstacle in cells
     * @return A cost value for the distance */
    virtual inline unsigned char computeCost(double distance) const
    {
      //ROS_INFO_STREAM(inscribed_radius_);
      unsigned char cost = 0;
      if (distance == 0)
        cost = LETHAL_OBSTACLE;
      else if (distance * resolution_ <= (inscribed_radius_))
        cost = INSCRIBED_INFLATED_OBSTACLE;
      else
      {
        // make sure cost falls off by Euclidean distance
        double euclidean_distance = distance * resolution_;
        double factor = exp(-1.0 * weight_ * (euclidean_distance - inscribed_radius_));
        cost = (unsigned char)((INSCRIBED_INFLATED_OBSTACLE - 1) * factor); 
      }
      return cost;
    }

    /**
     * @brief Change the values of the inflation radius parameters
     * @param inflation_radius The new inflation radius
     * @param cost_scaling_factor The new weight
     */
    void setInflationParameters(double inflation_radius, double cost_scaling_factor);

  protected:
    virtual void onFootprintChanged();
    boost::recursive_mutex *inflation_access_;

    double resolution_;
    double inflation_radius_;
    double inscribed_radius_;
    double weight_;
    bool inflate_unknown_;

  private:
    /**
     * @brief  Lookup pre-computed distances
     * @param mx The x coordinate of the current cell
     * @param my The y coordinate of the current cell
     * @param src_x The x coordinate of the source cell
     * @param src_y The y coordinate of the source cell
     * @return
     */
    inline double distanceLookup(int mx, int my, int src_x, int src_y)
    {
      unsigned int dx = abs(mx - src_x);
      unsigned int dy = abs(my - src_y);
      return cached_distances_[dx][dy];
    }

    /**
     * @brief  Lookup pre-computed costs
     * @param mx The x coordinate of the current cell
     * @param my The y coordinate of the current cell
     * @param src_x The x coordinate of the source cell
     * @param src_y The y coordinate of the source cell
     * @return
     */
    inline unsigned char costLookup(int mx, int my, int src_x, int src_y)
    {
      unsigned int dx = abs(mx - src_x);
      unsigned int dy = abs(my - src_y);
      return cached_costs_[dx][dy];
    }

    void computeCaches();
    void deleteKernels();
    void inflate_area(int min_i, int min_j, int max_i, int max_j, unsigned char *master_grid);

    unsigned int cellDistance(double world_dist)
    {
      return layered_costmap_->getCostmap()->cellDistance(world_dist);
    }

    inline void enqueue(unsigned int index, unsigned int mx, unsigned int my,
                        unsigned int src_x, unsigned int src_y);

    unsigned int cell_inflation_radius_;
    unsigned int cached_cell_inflation_radius_;
    std::map<double, std::vector<CellData> > inflation_cells_;

    bool *seen_;
    int seen_size_; 

    unsigned char **cached_costs_;
    double **cached_distances_;
    double last_min_x_, last_min_y_, last_max_x_, last_max_y_;

    dynamic_reconfigure::Server<UstarCostmap::InflationPluginConfig> *dsrv_;
    void reconfigureCB(UstarCostmap::InflationPluginConfig &config, uint32_t level);

    bool need_reinflation_; ///< Indicates that the entire costmap should be reinflated next time around.
  };

} // namespace UstarCostmap

#endif // COSTMAP_2D_INFLATION_LAYER_H_
