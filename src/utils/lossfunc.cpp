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
    float_type accumulate(const vector &a, const vector &b, std::function<float_type (float_type, float_type)> &f) {
        if(a.size() != b.size()) throw std::invalid_argument("accumulate vector size mismatch");  // throw if mismatched sizes

        return std::transform_reduce(std::execution::par_unseq, a.begin(), a.end(), b.begin(), (float_type) 0, std::plus<float_type>(), f);
    };


    /*
     *  Mean Squared Error (L2)
     */

    value_type mse = {
        [](float_type x, float_type t) -> float_type {
            float_type d = t - x;
            return 0.5f * d * d;
        },

        [](float_type x, float_type t) -> float_type {
            return x - t;
        },
    };


    /*
     *  Mean Absolute Error (L1)
     */

    value_type mae = {
        [](float_type x, float_type t) -> float_type {
            return std::abs(t - x);
        },

        [](float_type x, float_type t) -> float_type {
            if(x < t) return -1.0f;
            else if(x > t) return 1.0f;

            return 0.0f;
        },
    };


    /*
     *  Cross Entropy or Log Loss Error
     */

    value_type xee = {
        [](float_type x, float_type t) -> float_type {
            if(t == 1.0f) return -1.0f * std::log(x);
            return -1.0f * std::log(1.0f - x);
        },

        [](float_type x, float_type t) -> float_type {
            if(t == 1.0f) return -1.0f / x;
            return -1.0f / (1.0f - t);
        },
    };
}
