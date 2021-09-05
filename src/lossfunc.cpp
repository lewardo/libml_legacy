#include <numeric>

#include "typedefs.h"
#include "lossfunc.h"


float lossfunc::MSE(vfloat o, vfloat t) {
    float accumulation = 0.0f;

    if(o.size() != t.size()) return -1.0f;

    for(size_t n = 0, size = o.size(); n < size; ++n) {
        float diff = t[n] - o[n];
        accumulation += diff * diff * 0.5;
    };

    return accumulation;
};
