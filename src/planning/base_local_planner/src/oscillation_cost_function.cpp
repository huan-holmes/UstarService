#include <base_local_planner/oscillation_cost_function.h>

#include <cmath>

namespace base_local_planner {

OscillationCostFunction::OscillationCostFunction() {
}

OscillationCostFunction::~OscillationCostFunction() {
  prev_stationary_pos_ = Eigen::Vector3f::Zero();
}

void OscillationCostFunction::setOscillationResetDist(double dist, double angle) {
  oscillation_reset_dist_ = dist;
  oscillation_reset_angle_ = angle;
}

void OscillationCostFunction::updateOscillationFlags(Eigen::Vector3f pos, base_local_planner::Trajectory* traj, double min_vel_trans) {
  if (traj->cost_ >= 0) {
    if (setOscillationFlags(traj, min_vel_trans)) {
      prev_stationary_pos_ = pos;
    }
    //if we've got restrictions... check if we can reset any oscillation flags
    if(forward_pos_only_ || forward_neg_only_
        || strafe_pos_only_ || strafe_neg_only_
        || rot_pos_only_ || rot_neg_only_){
      resetOscillationFlagsIfPossible(pos, prev_stationary_pos_);
    }
  }
}

void OscillationCostFunction::resetOscillationFlagsIfPossible(const Eigen::Vector3f& pos, const Eigen::Vector3f& prev) {
  double x_diff = pos[0] - prev[0];
  double y_diff = pos[1] - prev[1];
  double sq_dist = x_diff * x_diff + y_diff * y_diff;

  double th_diff = pos[2] - prev[2];

  //if we've moved far enough... we can reset our flags
  if (sq_dist > oscillation_reset_dist_ * oscillation_reset_dist_ ||
      fabs(th_diff) > oscillation_reset_angle_) {
    resetOscillationFlags();
  }
}

void OscillationCostFunction::resetOscillationFlags() {
  strafe_pos_only_ = false;
  strafe_neg_only_ = false;
  strafing_pos_ = false;
  strafing_neg_ = false;

  rot_pos_only_ = false;
  rot_neg_only_ = false;
  rotating_pos_ = false;
  rotating_neg_ = false;

  forward_pos_only_ = false;
  forward_neg_only_ = false;
  forward_pos_ = false;
  forward_neg_ = false;
}

bool OscillationCostFunction::setOscillationFlags(base_local_planner::Trajectory* t, double min_vel_trans) {
  bool flag_set = false;
  //set oscillation flags for moving forward and backward
  if (t->xv_ < 0.0) {
    if (forward_pos_) {
      forward_neg_only_ = true;
      flag_set = true;
    }
    forward_pos_ = false;
    forward_neg_ = true;
  }
  if (t->xv_ > 0.0) {
    if (forward_neg_) {
      forward_pos_only_ = true;
      flag_set = true;
    }
    forward_neg_ = false;
    forward_pos_ = true;
  }

  //we'll only set flags for strafing and rotating when we're not moving forward at all
  if (fabs(t->xv_) <= min_vel_trans) {
    //check negative strafe
    if (t->yv_ < 0) {
      if (strafing_pos_) {
        strafe_neg_only_ = true;
        flag_set = true;
      }
      strafing_pos_ = false;
      strafing_neg_ = true;
    }

    //check positive strafe
    if (t->yv_ > 0) {
      if (strafing_neg_) {
        strafe_pos_only_ = true;
        flag_set = true;
      }
      strafing_neg_ = false;
      strafing_pos_ = true;
    }

    //check negative rotation
    if (t->thetav_ < 0) {
      if (rotating_pos_) {
        rot_neg_only_ = true;
        flag_set = true;
      }
      rotating_pos_ = false;
      rotating_neg_ = true;
    }

    //check positive rotation
    if (t->thetav_ > 0) {
      if (rotating_neg_) {
        rot_pos_only_ = true;
        flag_set = true;
      }
      rotating_neg_ = false;
      rotating_pos_ = true;
    }
  }
  return flag_set;
}

double OscillationCostFunction::scoreTrajectory(Trajectory &traj) {
  if ((forward_pos_only_ && traj.xv_ < 0.0) ||
      (forward_neg_only_ && traj.xv_ > 0.0) ||
      (strafe_pos_only_  && traj.yv_ < 0.0) ||
      (strafe_neg_only_  && traj.yv_ > 0.0) ||
      (rot_pos_only_     && traj.thetav_ < 0.0) ||
      (rot_neg_only_     && traj.thetav_ > 0.0)) {
    return -5.0;
  }
  return 0.0;
}

} /* namespace base_local_planner */
