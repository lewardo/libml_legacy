#pragma once

#include <cmath>
#include <concepts>
#include <functional>

#include "types.h"


/*
 *  actfunc namespace 
 */

namespace ml::actf {
    
    /*
     *  detail namespace as to not import other namespaces to `namespace network` directly
     */

    namespace detail {
        
        /*
         *  using declarations
         */

        using namespace internal::types;


        /*
         *  actfunc type, a struct consisting of two functions, the activation function itself and its derivative
         */

        struct value_type {
            /*
             *  activation function itself
             */

            std::function<flt (flt)> f;


            /*
             *  derivative of the activation function in terms of the original output
             */

            std::function<flt (flt)> df;
        };
    
        
        /*
         *  utility to create pair with (a, b)
         */
         
        inline std::pair<value_type, value_type> operator,(value_type& l, value_type& r) {
            return std::make_pair(l, r);
        }


        /*
         *  sigmoid activation
         */

        extern value_type sigmoid;


        /*
         *  hyperbolic tangent activation
         */

        extern value_type tanh;


        /*
         *  Rectified Linear Unit activation
         */

        extern value_type relu;


        /*
         *  Linear activation
         */

        extern value_type linear;
        
    }
    
    
    /*
     *  export detail symbols to outer namespace
     */
    
    using detail::value_type;
    using detail::sigmoid, detail::tanh, detail::relu, detail::linear;

}
