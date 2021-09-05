#include <cmath>

#include "actfunc.h"

actfunc_t actfunc::sigmoid = {
    [](float x) -> float {
        return 1.0f / (1.0f + expf(-x));
    },
    
    [](float x) -> float {
        return x * (1.0f - x);
    }
};

actfunc_t actfunc::tanh = {
    [] (float x) -> float {
        return tanhf(x);
    },

    [] (float x) -> float {
        return 1.0f - x * x;
    }
};

actfunc_t actfunc::ReLU = {
    [] (float x) -> float {
        if(x > 0.0f) return x;
        else return 0;
    },

    [] (float x) -> float {
        if(x > 0.0f) return 1;
        else return 0;
    }
};

actfunc_t actfunc::linear = {
    [] (float x) -> float {
        return x;
    },
    
    [] (float x) -> float {
        return 1;
    }
};
