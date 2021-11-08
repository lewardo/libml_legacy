#pragma once

#include <functional>


/*
 *  actfunc namespace, to clarify useage
 */

namespace actfunc {
    /*
     *  using declarations
     */  

    using ActType = std::function<float (float)>;


    /*
     *  actfunc type, a struct consisting of two functions, the activation function itself and its derivative
     */

    struct Actfunc {
        /*
         *  activation function itself
         */

        ActType f_x;


        /*
         *  activation of the loss function
         */

        ActType df_dx;
    };


    /*
     *  sigmoid activation
     */

    extern Actfunc Sigmoid;


    /*
     *  hyperbolic tangent activation
     */

    extern Actfunc Tanh;


    /*
     *  Rectified Linear Unit activation
     */

    extern Actfunc ReLU;
    

    /*
     *  Linear activation
     */

    extern Actfunc Linear;
};