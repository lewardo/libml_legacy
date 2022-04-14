#pragma once

#include "actfunc.h"
#include "lossfunc.h"

#include "types.h"


using metadata_t = struct {
    ml::types::flt lr, mo, cutoff;
    unsigned int batch;
    ml::lossf::value_type lf;
};

using mlp_param_t = struct {
    std::vector<size_t> npl;
    ml::actf::value_type af;
};
