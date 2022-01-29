#pragma once

#include <vector>
#include <functional>

#include "neural.h"
#include "types.h"

/*
 *  lossfunc namespace, to clarify useage
 */

namespace lossfunc {
    /*
     *  using declarations
     */  

    using namespace mltypes;
    using lf = std::function<f32 (f32, f32)>;


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

    float accumulate(vf32, vf32, lf);


    /*
     *  Mean Squared Error (L2)
     */

    extern ::lossfunc::type mse;


    /*
     *  Mean Absolute Error (L1)
     */

    extern ::lossfunc::type mae;


    /*
     *  Cross Entropy or Log Loss Error
     */

    extern ::lossfunc::type xee;
};