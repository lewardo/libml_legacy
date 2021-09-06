#pragma once

/*
 *  actfunc type, a struct consisting of two functions, the activation function itself and its derivative
 */

using actfunc_t = struct {
    float (* f_x)(float), (* df_dx)(float);
};


/*
 *  actfunc namespace, to clarify useage
 */

namespace actfunc {
    /*
     *  sigmoid activation
     */

    extern actfunc_t sigmoid;


    /*
     *  hyperbolic tangent activation
     */

    extern actfunc_t tanh;


    /*
     *  Rectified Linear Unit activation
     */

    extern actfunc_t ReLU;
    

    /*
     *  Linear activation
     */

    extern actfunc_t linear;
};