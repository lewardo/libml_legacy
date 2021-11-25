#pragma once

#include <functional>


/*
 *  actfunc namespace, to clarify useage
 */

namespace actfunc {
    /*
     *  using declarations
     */  

    using af = std::function<float (float)>;


    /*
     *  actfunc type, a struct consisting of two functions, the activation function itself and its derivative
     */

    struct type {
        /*
         *  activation function itself
         */

        af f_x;


        /*
         *  activation of the loss function
         */

        af df_dx;
    };


    /*
     *  sigmoid activation
     */

    extern ::actfunc::type Sigmoid;


    /*
     *  hyperbolic tangent activation
     */

    extern ::actfunc::type Tanh;


    /*
     *  Rectified Linear Unit activation
     */

    extern ::actfunc::type ReLU;
    

    /*
     *  Linear activation
     */

    extern ::actfunc::type Linear;
};