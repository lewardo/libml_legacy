#pragma once

#include <vector>
#include <functional>

#include "neural.h"


/*
 *  lossfunc namespace, to clarify useage
 */

namespace lossfunc {
    /*
     *  using declarations
     */  

    using vfloat = std::vector<float>;
    using lf = std::function<float (float, float)>;


    /*
     *  inheritable class to be able to pass all lossfuncs as a single pointer
     */

    struct type {
        /*
         *  loss function itself
         */

        lf f_x;


        /*
         *  derivative of the loss function
         */

        lf df_dx;
    };


    /*
     *  Accumulator function to simplify error calculation
     */

    float accumulate(vfloat, vfloat, lf);


    /*
     *  Mean Squared Error (L2)
     */

    extern ::lossfunc::type MeanSquared;


    /*
     *  Mean Absolute Error (L1)
     */

    extern ::lossfunc::type MeanAbsolute;


    /*
     *  Cross Entropy or Log Loss Error
     */

    extern ::lossfunc::type CrossEntropy;
};