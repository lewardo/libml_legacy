#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <numeric>

#include "algeb.h"
#include "lossfunc.h"

using namespace ml::types;
using namespace ml::lossf;

/*
 *  Accumulator function to simplify error calculation
 */

[[ maybe_unused ]]
flt accumulate(const vector &a, const vector &b, std::function<flt (flt, flt)> &f) {        
    if(a.size() != b.size()) return -1;  // return if mismatched sizes

    return std::transform_reduce(std::execution::par, a.begin(), a.end(), b.begin(), 0.0f, std::plus<flt>(), f);
};


/*
 *  Mean Squared Error (L2)
 */

value_type ml::lossf::mse = {
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

value_type ml::lossf::mae = {
    [](flt x, flt t) -> flt {
        return fabs(t - x);
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

value_type ml::lossf::xee = {
    [](flt x, flt t) -> flt {
        if(t == 1.0f) return -1.0f * log(x);
        return -1.0f * log(1.0f - x);
    },

    [](flt x, flt t) -> flt {
        if(t == 1.0f) return -1.0f / x;
        return -1.0f / (1.0f - t);
    },
};