#include <cmath>

#include "actfunc.h"


/*
 *  sigmoid activation
 */

actfunc::type actfunc::Sigmoid = {
    [](float x) -> float {
        return 1.0f / (1.0f + expf(-1.0f * x));
    },
    
    [](float x) -> float {
        return x * (1.0f - x);
    }
};


/*
 *  hyperbolic tangent activation
 */

actfunc::type actfunc::Tanh = {
    [] (float x) -> float {
        return tanhf(x);
    },

    [] (float x) -> float {
        return 1.0f - x * x;
    }
};


/*
 *  Rectified Linear Unit activation
 */

actfunc::type actfunc::ReLU = {
    [] (float x) -> float {
        if(x > 0.0f) return x;
        else return 0.0f;
    },

    [] (float x) -> float {
        if(x > 0.0f) return 1.0f;
        else return 0.0f;
    }
};


/*
 *  Linear activation
 */

actfunc::type actfunc::Linear = {
    [] (float x) -> float {
        return x;
    },
    
    [] (float x) -> float {
        return 1.0f;
    }
};
