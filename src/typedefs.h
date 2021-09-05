#pragma once

#include <vector>
#include <cstdbool>

#include "actfunc.h"

using vfloat = std::vector<float>;
using mfloat = std::vector<vfloat>;


using metadata_t = struct {
    float lr, mo;
    uint32_t batch;

    struct {
        bool mode; 
        union {
            uint32_t nepochs;
            float err;
        };
    } cutoff;
};

using mlp_param_t = struct {
    std::vector<size_t> npl;
    actfunc_t af;
};