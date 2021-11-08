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
    using LossType = std::function<float (float, float)>;


    /*
     *  inheritable class to be able to pass all lossfuncs as a single pointer
     */

    struct Lossfunc {
        /*
         *  loss function itself
         */

        LossType f_x;


        /*
         *  derivative of the loss function
         */

        LossType df_dx;
    };


    /*
     *  Accumulator function to simplify error calculation
     */

    float accumulate(vfloat, vfloat, LossType);


    /*
     *  Mean Squared Error (L2)
     */

    extern Lossfunc MeanSquared;


    /*
     *  Mean Absolute Error (L1)
     */

    extern Lossfunc MeanAbsolute;


    /*
     *  Cross Entropy or Log Loss Error
     */

    extern Lossfunc CrossEntropy;
};