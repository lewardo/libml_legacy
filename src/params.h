#pragma once

#include "actfunc.h"
#include "lossfunc.h"

#include "types.h"

using namespace mltypes;

using metadata_t = struct {
    f32 lr, mo, cutoff;
    u32 batch;
    lossfunc::type lf;
};

using mlp_param_t = struct {
    std::vector<size_t> npl;
    actfunc::type af;
};