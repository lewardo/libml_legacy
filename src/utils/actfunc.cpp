#include <cmath>

#include "actfunc.h"

using namespace ml::types;
using namespace ml::actf;


/*
 *  sigmoid activation
 */

value_type ml::actf::sigmoid = {
    [](flt x) -> flt {
        return 1.0f / (1.0f + std::exp(-1.0f * x));
    },

    [](flt x) -> flt {
        return x * (1.0f - x);
    }
};


/*
 *  hyperbolic tangent activation
 */

value_type ml::actf::tanh = {
    [] (flt x) -> flt {
        return std::tanh(x);
    },

    [] (flt x) -> flt {
        return 1.0f - x * x;
    }
};


/*
 *  Rectified Linear Unit activation
 */

value_type ml::actf::relu = {
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

value_type ml::actf::linear = {
    [] (flt x) -> flt {
        return x;
    },

    [] (flt x) -> flt {
        return 1.0f;
    }
};