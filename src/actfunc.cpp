#include <cmath>

#include "actfunc.h"


/*
 *  sigmoid activation
 */

actfunc_t actfunc::sigmoid = {
    [](float x) {
        return 1.0f / (1.0f + expf(-1.0f * x));
    },
    
    [](float x) {
        return x * (1.0f - x);
    }
};


/*
 *  hyperbolic tangent activation
 */

actfunc_t actfunc::tanh = {
    [] (float x) {
        return tanhf(x);
    },

    [] (float x) {
        return 1.0f - x * x;
    }
};


/*
 *  Rectified Linear Unit activation
 */

actfunc_t actfunc::ReLU = {
    [] (float x) {
        if(x > 0.0f) return x;
        else return 0.0f;
    },

    [] (float x) {
        if(x > 0.0f) return 1.0f;
        else return 0.0f;
    }
};


/*
 *  Linear activation
 */

actfunc_t actfunc::linear = {
    [] (float x) {
        return x;
    },
    
    [] (float x) {
        return 1.0f;
    }
};
