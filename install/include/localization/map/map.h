#ifndef _MAP_H_
#define _MAP_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
struct _rtk_fig_t;

  
// Limits
#define MAP_WIFI_MAX_LEVELS 8

  
// Description for a single map cell.
typedef struct
{
  // Occupancy state (-1 = free, 0 = unknown, +1 = occ)
  int occ_state;

  // Distance to the nearest occupied cell
  double occ_dist;

  // Wifi levels
  //int wifi_levels[MAP_WIFI_MAX_LEVELS];

} map_cell_t;


// Description for a map
typedef struct
{
  // Map origin; the map is a viewport onto a conceptual larger map.
  double origin_x, origin_y;
  
  // Map scale (m/cell)
  double scale;

  // Map dimensions (number of cells)
  int size_x, size_y;
  
  // The map data, stored as a grid
  map_cell_t *cells;

  // Max distance at which we care about obstacles, for constructing
  // likelihood field
  double max_occ_dist;
  
} map_t;



/**************************************************************************
 * Basic map functions
 **************************************************************************/

// Create a new (empty) map
map_t *map_alloc(void);

// Destroy a map
void map_free(map_t *map);

// Get the cell at the given point
map_cell_t *map_get_cell(map_t *map, double ox, double oy, double oa);

// Load an occupancy map
int map_load_occ(map_t *map, const char *filename, double scale, int negate);

// Load a wifi signal strength map
//int map_load_wifi(map_t *map, const char *filename, int index);

// Update the cspace distances
void map_update_cspace(map_t *map, double max_occ_dist);


/**************************************************************************
 * Range functions
 **************************************************************************/

// Extract a single range reading from the map
double map_calc_range(map_t *map, double ox, double oy, double oa, double max_range);


/**************************************************************************
 * GUI/diagnostic functions
 **************************************************************************/

// Draw the occupancy grid
void map_draw_occ(map_t *map, struct _rtk_fig_t *fig);

// Draw the cspace map
void map_draw_cspace(map_t *map, struct _rtk_fig_t *fig);

// Draw a wifi map
void map_draw_wifi(map_t *map, struct _rtk_fig_t *fig, int index);


/**************************************************************************
 * Map manipulation macros
 **************************************************************************/

// Convert from map index to world coords
#define MAP_WXGX(map, i) (map->origin_x + ((i) - map->size_x / 2) * map->scale)
#define MAP_WYGY(map, j) (map->origin_y + ((j) - map->size_y / 2) * map->scale)

// Convert from world coords to map coords
#define MAP_GXWX(map, x) (floor((x - map->origin_x) / map->scale + 0.5) + map->size_x / 2)
#define MAP_GYWY(map, y) (floor((y - map->origin_y) / map->scale + 0.5) + map->size_y / 2)

// Test to see if the given map coords lie within the absolute map bounds.
#define MAP_VALID(map, i, j) ((i >= 0) && (i < map->size_x) && (j >= 0) && (j < map->size_y))

// Compute the cell index for the given map coords.
#define MAP_INDEX(map, i, j) ((i) + (j) * map->size_x)

#ifdef __cplusplus
}
#endif

#endif
