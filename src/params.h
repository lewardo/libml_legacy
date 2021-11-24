#pragma once

#include "actfunc.h"
#include "lossfunc.h"

using metadata_t = struct {
    float lr, mo, cutoff;
    uint32_t batch;
    lossfunc::type lf;
};

using mlp_param_t = struct {
    std::vector<size_t> npl;
    actfunc::type af;
};