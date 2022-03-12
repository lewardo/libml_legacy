#pragma once

#include <cmath>
#include <numeric>
#include <functional>
#include <execution>

#include "neural.h"
#include "vector.h"
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

        std::function<flt (flt, flt)> f;


        /*
         *  derivative of the loss function
         */

        std::function<flt (flt, flt)> df;
    };


    /*
     *  Accumulator function to simplify error calculation
     */

    [[maybe_unused]]
    static float accumulate(const vector &a, const vector &b, std::function<flt (flt, flt)> &f) {
        const std::vector<flt> &sa = types::std(a), &sb = types::std(b);
        
        if(sa.size() != sb.size()) return -1;  // return if mismatched sizes

        return std::transform_reduce(std::execution::par, sa.begin(), sa.end(), sb.begin(), 0.0f, std::plus<flt>(), f);
    };


    /*
     *  Mean Squared Error (L2)
     */

    static lossf::value_type mse = {
        [](flt x, flt t) -> flt {
            flt d = t - x;
            return 0.5f * d * d;
        },

        [](flt x, flt t) -> flt {
            return x - t;
        },
    };


    /*
     *  Mean Absolute Error (L1)
     */

    static lossf::value_type mae = {
        [](flt x, flt t) -> flt {
            return fabsf(t - x);
        },

        [](flt x, flt t) -> flt {
            if(x < t) return -1.0f;
            else if(x > t) return 1.0f;

            return 0.0f;
        },
    };


    /*
     *  Cross Entropy or Log Loss Error
     */

    static lossf::value_type xee = {
        [](flt x, flt t) -> flt {
            if(t == 1.0f) return -1.0f * logf(x);
            return -1.0f * logf(1.0f - x);
        },

        [](flt x, flt t) -> flt {
            if(t == 1.0f) return -1.0f / x;
            return -1.0f / (1.0f - t);
        },
    };
};
