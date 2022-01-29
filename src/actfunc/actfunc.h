#pragma once

#include <functional>

#include "types.h"


/*
 *  actfunc namespace, to clarify useage
 */

namespace actfunc {
    /*
     *  using declarations
     */  

    using namespace mltypes;
    using af = std::function<f32 (f32)>;


    /*
     *  actfunc type, a struct consisting of two functions, the activation function itself and its derivative
     */

    struct type {
        /*
         *  activation function itself
         */

        af f_x;


        /*
         *  activation of the loss function
         */

        af df_dx;
    };


    /*
     *  sigmoid activation
     */

    extern ::actfunc::type sigmoid;


    /*
     *  hyperbolic tangent activation
     */

    extern ::actfunc::type tanh;


    /*
     *  Rectified Linear Unit activation
     */

    extern ::actfunc::type relu;
    

    /*
     *  Linear activation
     */

    extern ::actfunc::type linear;
};