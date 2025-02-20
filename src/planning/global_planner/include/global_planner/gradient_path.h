
#ifndef _GRADIENT_PATH_H_
#define _GRADIENT_PATH_H_

#include "global_planner/traceback.h"
#include <math.h>
#include <algorithm>

namespace global_planner 
{

class GradientPath : public Traceback 
{
    public:
        GradientPath(PotentialCalculator* p_calc);
        ~GradientPath();

        void setSize(int xs, int ys);

        //
        // Path construction
        // Find gradient at array points, interpolate path
        // Use step size of pathStep, usually 0.5 pixel
        //
        // Some sanity checks:
        //  1. Stuck at same index position
        //  2. Doesn't get near goal
        //  3. Surrounded by high potentials
        //
        bool getPath(float* potential, double start_x, double start_y, double end_x, double end_y, std::vector<std::pair<float, float> >& path);
    private:
        inline int getNearestPoint(int stc, float dx, float dy) 
        {
            int pt = stc + (int)round(dx) + (int)(xs_ * round(dy));
            return std::max(0, std::min(xs_ * ys_ - 1, pt));
        }
        float gradCell(float* potential, int n);

        float *gradx_, *grady_; /**< gradient arrays, size of potential array */

        float pathStep_; /**< step size for following gradient */
};

} //end namespace global_planner
#endif
