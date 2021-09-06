#include <cstdlib>
#include <numeric>

#include "typedefs.h"
#include "lossfunc.h"

/*
 *  Accumulator function to simplify error calculation
 */

float lossfunc::accumulate(vfloat a, vfloat b, float (* f)(float, float)) {
    vfloat merged;

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

lossfunc_t lossfunc::MSE = {
    [](float x, float t) {
        float d = t - x;
        return 0.5f * d * d;
    },

    [](float x, float t) {
        return x - t;
    }
};

/*
 *  Mean Absolute Error (L1)
 */

lossfunc_t lossfunc::MAE = {
    [](float x, float t) {
        return fabsf(t - x);
    },

    [](float x, float t) {
        if(x < t) return -1.0f;
        else if(x > t) return 1.0f;

        return 0.0f;
    }
};


/*
 *  Cross Entropy or Log Loss Error, out consists of only 0s or 1s, used for classification problems
 */

lossfunc_t lossfunc::XEE = {
    [](float x, float t) {
        if(t == 1.0f) return -1.0f * logf(x);

        return -1.0f * logf(1.0f - x);
    },

    [](float x, float t) {
        if(t == 1.0f) return -1.0f / x;

        return -1.0f / (1.0f - t);
    }
};