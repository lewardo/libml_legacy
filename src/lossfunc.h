#pragma once

#include <numeric>

#include "typedefs.h"

/*
 *  lossfunc type, a struct consisting of two functions, the loss function itself and its derivative
 */

using lossfunc_t = struct {
    float (* f_x)(float, float), (* df_dx)(float, float);
};


/*
 *  lossfunc namespace, to clarify useage
 */

namespace lossfunc {
    /*
     *  Accumulator function to simplify error calculation
     */

    float accumulate(vfloat, vfloat, float (*)(float, float));


    /*
     *  Mean Squared Error (L2)
     */

    extern lossfunc_t MSE;


    /*
     *  Mean Absolute Error (L1)
     */

    extern lossfunc_t MAE;


    /*
     *  Cross Entropy or Log Loss Error
     */

    extern lossfunc_t XEE;
};