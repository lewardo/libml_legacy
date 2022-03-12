#pragma once

#include <cmath>
#include <numeric>
#include <functional>
#include <execution>

#include "neural.h"
#include "types.h"

/*
 *  lossfunc namespace, to clarify useage
 */

namespace ml::lossf {
    /*
     *  using declarations
     */

    using namespace ml::types;


    /*
     *  inheritable class to be able to pass all lossfuncs as a single pointer
     */

    struct value_type {
        /*
         *  loss function itself
         */

        std::function<f32 (f32, f32)> f;


        /*
         *  derivative of the loss function
         */

        std::function<f32 (f32, f32)> df;
    };


    /*
     *  Accumulator function to simplify error calculation
     */

    [[maybe_unused]]
    static float accumulate(const vf32& a, const vf32& b, std::function<f32 (f32, f32)>& f) {
        if(a.size() > b.size()) return -1;  // return if mismatched sizes

        return std::transform_reduce(std::execution::par, a.begin(), a.end(), b.begin(), 0.0f, std::plus<f32>(), f);
    };


    /*
     *  Mean Squared Error (L2)
     */

    static lossf::value_type mse = {
        [](f32 x, f32 t) -> f32 {
            f32 d = t - x;
            return 0.5f * d * d;
        },

        [](f32 x, f32 t) -> f32 {
            return x - t;
        },
    };


    /*
     *  Mean Absolute Error (L1)
     */

    static lossf::value_type mae = {
        [](f32 x, f32 t) -> f32 {
            return fabsf(t - x);
        },

        [](f32 x, f32 t) -> f32 {
            if(x < t) return -1.0f;
            else if(x > t) return 1.0f;

            return 0.0f;
        },
    };


    /*
     *  Cross Entropy or Log Loss Error
     */

    static lossf::value_type xee = {
        [](f32 x, f32 t) -> f32 {
            if(t == 1.0f) return -1.0f * logf(x);
            return -1.0f * logf(1.0f - x);
        },

        [](f32 x, f32 t) -> f32 {
            if(t == 1.0f) return -1.0f / x;
            return -1.0f / (1.0f - t);
        },
    };
};
