#include <cmath>

#include "actfunc.h"

namespace ml::actf::detail {

    /*
     *  sigmoid activation
     */

    value_type sigmoid = {
        [](float_type x) -> float_type {
            return 1.0f / (1.0f + std::exp(-1.0f * x));
        },

        [](float_type x) -> float_type {
            return x * (1.0f - x);
        }
    };


    /*
     *  hyperbolic tangent activation
     */

    value_type tanh = {
        [] (float_type x) -> float_type {
            return std::tanh(x);
        },

        [] (float_type x) -> float_type {
            return 1.0f - x * x;
        }
    };


    /*
     *  Rectified Linear Unit activation
     */

    value_type relu = {
        [] (float_type x) -> float_type {
            if(x > 0.0f) return x;
            else return 0.0f;
        },

        [] (float_type x) -> float_type {
            if(x > 0.0f) return 1.0f;
            else return 0.0f;
        }
    };


    /*
     *  Linear activation
     */

    value_type linear = {
        [] (float_type x) -> float_type {
            return x;
        },

        [] (float_type) -> float_type {
            return 1.0f;
        }
    };
}