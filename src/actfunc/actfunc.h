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

        std::function<f32 (f32)> f;


        /*
         *  derivative of the activation function in terms of the original output
         */

        std::function<f32 (f32)> df;
    };


    /*
     *  sigmoid activation
     */

    static actf::value_type sigmoid = {
        [](f32 x) -> f32 {
            return 1.0f / (1.0f + expf(-1.0f * x));
        },

        [](f32 x) -> f32 {
            return x * (1.0f - x);
        }
    };


    /*
     *  hyperbolic tangent activation
     */

    static actf::value_type tanh = {
        [] (f32 x) -> f32 {
            return tanhf(x);
        },

        [] (f32 x) -> f32 {
            return 1.0f - x * x;
        }
    };


    /*
     *  Rectified Linear Unit activation
     */

    static actf::value_type relu = {
        [] (f32 x) -> f32 {
            if(x > 0.0f) return x;
            else return 0.0f;
        },

        [] (f32 x) -> f32 {
            if(x > 0.0f) return 1.0f;
            else return 0.0f;
        }
    };


    /*
     *  Linear activation
     */

    static actf::value_type linear = {
        [] (f32 x) -> f32 {
            return x;
        },

        [] (f32 x) -> f32 {
            return 1.0f;
        }
    };
}
