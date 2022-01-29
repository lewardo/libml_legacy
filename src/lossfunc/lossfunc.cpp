#include <cstdlib>
#include <vector>
#include <functional>
#include <numeric>

#include "lossfunc.h"


/*
 *  Accumulator function to simplify error calculation
 */

lossfunc::f32 lossfunc::accumulate(vf32 a, vf32 b, lossfunc::lf f) {
    vf32 merged;

    // return if mismatched sizes
    if(a.size() != b.size()) return -1.0f;

    // transform vectors into third vector with the lossfunc (f) as the action function
    std::transform(a.begin(), a.end(), b.begin(), /* b.end(), */ std::back_inserter(merged), f);

    // accumulate across the merged vector and return the total
    return std::accumulate(merged.begin(), merged.end(), 0.0f);
};


/*
 *  Mean Squared Error (L2)
 */

lossfunc::type lossfunc::mse = {
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

lossfunc::type lossfunc::mae = {
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
 *  Cross Entropy or Log Loss Error, target consists of only 0s or 1s, used for classification problems
 */

lossfunc::type lossfunc::xee = {
    [](f32 x, f32 t) -> f32 {
        if(t == 1.0f) 
            return -1.0f * logf(x);
        return -1.0f * logf(1.0f - x);
    },

    [](f32 x, f32 t) -> f32 {
        if(t == 1.0f) 
            return -1.0f / x;
        return -1.0f / (1.0f - t);
    },
};