#include <cmath>

#include "actfunc.h"


/*
 *  sigmoid activation
 */

actfunc::type actfunc::sigmoid = {
    [](f32 x) -> f32 {
        return 1.0f / (1.0f + expf(-1.0f * x));
    },
    
    [](f32 x) -> f32 {
        return x * (1.0f - x);
    }
};


/*
 *  hyperbolic tangent activation
 */

actfunc::type actfunc::tanh = {
    [] (f32 x) -> f32 {
        return tanhf(x);
    },

    [] (f32 x) -> f32 {
        return 1.0f - x * x;
    }
};


/*
 *  Rectified Linear Unit activation
 */

actfunc::type actfunc::relu = {
    [] (f32 x) -> f32 {
        if(x > 0.0f) return x;
        else return 0.0f;
    },

    [] (f32 x) -> f32 {
        if(x > 0.0f) return 1.0f;
        else return 0.0f;
    }
};


/*
 *  Linear activation
 */

actfunc::type actfunc::linear = {
    [] (f32 x) -> f32 {
        return x;
    },
    
    [] (f32 x) -> f32 {
        return 1.0f;
    }
};
