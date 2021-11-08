#pragma once

#include <vector>
#include <functional>

#include "neural.h"


/*
 *  lossfunc namespace, to clarify useage
 */

namespace lossfunc {
    /*
     *  using declaration to link define float vector
     */  

    using vfloat = std::vector<float>;


    /*
     *  Accumulator function to simplify error calculation
     */

    float accumulate(vfloat, vfloat, std::function<float (float, float)>);


    /*
     *  Mean Squared Error (L2)
     */

    class MSE {
        public:
            /*
             *  loss function itself
             */

            static float f_x(float, float);


            /*
             *  derivative of the loss function
             */

            static float df_dx(float, float);
    };


    /*
     *  Mean Absolute Error (L1)
     */

    class MAE {
        public:
            /*
             *  loss function itself
             */

            static float f_x(float, float);


            /*
             *  derivative of the loss function
             */

            static float df_dx(float, float);
    };


    /*
     *  Cross Entropy or Log Loss Error
     */

    class XEE {
        public:
            /*
             *  loss function itself
             */

            static float f_x(float, float);


            /*
             *  derivative of the loss function
             */

            static float df_dx(float, float);
    };
};