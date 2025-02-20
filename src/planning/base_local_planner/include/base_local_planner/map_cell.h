#ifndef TRAJECTORY_ROLLOUT_MAP_CELL_H_
#define TRAJECTORY_ROLLOUT_MAP_CELL_H_

#include <base_local_planner/trajectory_inc.h>

namespace base_local_planner {
  /**
   * @class MapCell
   * @brief Stores path distance and goal distance information used for scoring trajectories
   */
  class MapCell{
    public:
      /**
       * @brief  Default constructor
       */
      MapCell();

      /**
       * @brief  Copy constructor
       * @param mc The MapCell to be copied
       */
      MapCell(const MapCell& mc);

      unsigned int cx, cy; ///< @brief Cell index in the grid map

      double target_dist; ///< @brief Distance to planner's path

      bool target_mark; ///< @brief Marks for computing path/goal distances

      bool within_robot; ///< @brief Mark for cells within the robot footprint
  };
};

#endif
