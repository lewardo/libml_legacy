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

    static actf::value_type sigmoid = {
        [](flt x) -> flt {
            return 1.0f / (1.0f + expf(-1.0f * x));
        },

        [](flt x) -> flt {
            return x * (1.0f - x);
        }
    };


    /*
     *  hyperbolic tangent activation
     */

    static actf::value_type tanh = {
        [] (flt x) -> flt {
            return tanhf(x);
        },

        [] (flt x) -> flt {
            return 1.0f - x * x;
        }
    };


    /*
     *  Rectified Linear Unit activation
     */

    static actf::value_type relu = {
        [] (flt x) -> flt {
            if(x > 0.0f) return x;
            else return 0.0f;
        },

        [] (flt x) -> flt {
            if(x > 0.0f) return 1.0f;
            else return 0.0f;
        }
    };


    /*
     *  Linear activation
     */

    static actf::value_type linear = {
        [] (flt x) -> flt {
            return x;
        },

        [] (flt x) -> flt {
            return 1.0f;
        }
    };
}
