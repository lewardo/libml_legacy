#pragma once

#include <numeric>

#include "typedefs.h"

using lossfunc_t = float (*)(vfloat, vfloat);

namespace lossfunc {
    float MSE(vfloat, vfloat);
};