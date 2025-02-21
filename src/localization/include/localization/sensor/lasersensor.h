#ifndef _LASERSENSOR_H_
#define _LASERSENSOR_H_

#include "localization/sensor/sensor.h"
#include "localization/map/map.h"

namespace UstarLocalization
{

typedef enum
{
  LASER_MODEL_BEAM,
  LASER_MODEL_LIKELIHOOD_FIELD,
  LASER_MODEL_LIKELIHOOD_FIELD_PROB
} laser_model_t;

// Laser sensor data
class LaserSensorData : public SensorData
{
  public:
    LaserSensorData () {ranges=NULL;};
    virtual ~LaserSensorData() {delete [] ranges;};
  // Laser range data (range, bearing tuples)
  public: int range_count;
  public: double range_max;
  public: double (*ranges)[2];
};


// Laseretric sensor model
class LaserSensor : public Sensor
{
  // Default constructor
  public: LaserSensor(size_t max_beams, map_t* map);

  public: virtual ~LaserSensor(); 

  public: void SetModelBeam(double z_hit,
                            double z_short,
                            double z_max,
                            double z_rand,
                            double sigma_hit,
                            double lambda_short,
                            double chi_outlier);

  public: void SetModelLikelihoodField(double z_hit,
                                       double z_rand,
                                       double sigma_hit,
                                       double max_occ_dist);

  //a more probabilistically correct model - also with the option to do beam skipping
  public: void SetModelLikelihoodFieldProb(double z_hit,
					   double z_rand,
					   double sigma_hit,
					   double max_occ_dist, 
					   bool do_beamskip, 
					   double beam_skip_distance, 
					   double beam_skip_threshold, 
					   double beam_skip_error_threshold);

  // Update the filter based on the sensor model.  Returns true if the
  // filter has been updated.
  public: virtual bool UpdateSensor(pf_t *pf, SensorData *data);

  // Set the laser's pose after construction
  public: void SetLaserPose(pf_vector_t& laser_pose) 
          {this->laser_pose = laser_pose;}

  // Determine the probability for the given pose
  private: static double BeamModel(LaserSensorData *data, 
                                   pf_sample_set_t* set);
  // Determine the probability for the given pose
  private: static double LikelihoodFieldModel(LaserSensorData *data, 
                                              pf_sample_set_t* set);

  // Determine the probability for the given pose - more probablistic model 
  private: static double LikelihoodFieldModelProb(LaserSensorData *data, 
					     pf_sample_set_t* set);

  private: void reallocTempData(int max_samples, int max_obs);

  private: laser_model_t model_type;

  // Current data timestamp
  private: double time;

  // The laser map
  private: map_t *map;

  // Laser offset relative to robot
  private: pf_vector_t laser_pose;
  
  // Max beams to consider
  private: int max_beams;

  // Beam skipping parameters (used by LikelihoodFieldModelProb model)
  private: bool do_beamskip; 
  private: double beam_skip_distance; 
  private: double beam_skip_threshold; 
  //threshold for the ratio of invalid beams - at which all beams are integrated to the likelihoods 
  //this would be an error condition 
  private: double beam_skip_error_threshold;

  //temp data that is kept before observations are integrated to each particle (requried for beam skipping)
  private: int max_samples;
  private: int max_obs;
  private: double **temp_obs;

  // Laser model params
  //
  // Mixture params for the components of the model; must sum to 1
  private: double z_hit;
  private: double z_short;
  private: double z_max;
  private: double z_rand;
  //
  // Stddev of Gaussian model for laser hits.
  private: double sigma_hit;
  // Decay rate of exponential model for short readings.
  private: double lambda_short;
  // Threshold for outlier rejection (unused)
  private: double chi_outlier;
};


}

#endif
