#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <stdexcept>
#include <numeric>

#include "algeb.h"
#include "lossfunc.h"

namespace ml::lossf::detail {

    /*
     *  Accumulator function to simplify error calculation
     */

    [[ maybe_unused ]]
    flt accumulate(const vector &a, const vector &b, std::function<flt (flt, flt)> &f) {
        if(a.size() != b.size()) throw std::invalid_argument("accumulate vector size mismatch");  // throw if mismatched sizes

        return std::transform_reduce(std::execution::par_unseq, a.begin(), a.end(), b.begin(), (flt) 0, std::plus<flt>(), f);
    };


    /*
     *  Mean Squared Error (L2)
     */

    value_type mse = {
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

    value_type mae = {
        [](flt x, flt t) -> flt {
            return std::abs(t - x);
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

    value_type xee = {
        [](flt x, flt t) -> flt {
            if(t == 1.0f) return -1.0f * std::log(x);
            return -1.0f * std::log(1.0f - x);
        },

        [](flt x, flt t) -> flt {
            if(t == 1.0f) return -1.0f / x;
            return -1.0f / (1.0f - t);
        },
    };
}
