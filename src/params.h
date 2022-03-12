#pragma once

#include "actfunc.h"
#include "lossfunc.h"

#include "types.h"


using metadata_t = struct {
    ml::types::f32 lr, mo, cutoff;
    ml::types::u32 batch;
    ml::lossf::value_type lf;
};

using mlp_param_t = struct {
    std::vector<size_t> npl;
    ml::actf::value_type af;
};
