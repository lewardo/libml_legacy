#pragma once

#include <cmath>
#include <concepts>
#include <functional>

#include "types.h"


/*
 *  actfunc namespace, to clarify useage
 */

namespace ml::actf {
    /*
     *  using declarations
     */

    using namespace ml::types;


    /*
     *  actfunc type, a struct consisting of two functions, the activation function itself and its derivative
     */

    struct value_type {
        /*
         *  activation function itself
         */

        std::function<flt (flt)> f;


        /*
         *  derivative of the activation function in terms of the original output
         */

        std::function<flt (flt)> df;
    };


    /*
     *  sigmoid activation
     */

    extern value_type sigmoid;


    /*
     *  hyperbolic tangent activation
     */

    extern value_type tanh;


    /*
     *  Rectified Linear Unit activation
     */

    extern value_type relu;


    /*
     *  Linear activation
     */

    extern value_type linear;
}
