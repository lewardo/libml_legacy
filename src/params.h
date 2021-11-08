#pragma once

#include "actfunc.h"
#include "lossfunc.h"

using metadata_t = struct {
    float lr, mo;
    uint32_t batch;
    lossfunc::Lossfunc lf;

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
    actfunc::Actfunc af;
};