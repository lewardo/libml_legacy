#pragma once

#include <cmath>
#include <numeric>
#include <utility>
#include <functional>
#include <execution>

#include "types.h"

/*
 *  lossfunc namespace
 */

namespace ml::lossf {
    
    /*
     *  detail namespace as to not import other namespaces to `namespace network` directly
     */

    namespace detail {
        /*
         *  using declarations
         */

        using namespace internal::types;


        /*
         *  inheritable class to be able to pass all lossfuncs as a single pointer
         */

        struct value_type {
            /*
             *  loss function itself
             */

            std::function<float_type (float_type, float_type)> f;


            /*
             *  derivative of the loss function
             */

            std::function<float_type (float_type, float_type)> df;
            
        };

        /*
         *  Accumulator function to simplify error calculation
         */

        float_type accumulate(const vector &a, const vector &b, std::function<float_type (float_type, float_type)> &f);


        /*
         *  Mean Squared Error (L2)
         */

        extern value_type mse;


        /*
         *  Mean Absolute Error (L1)
         */

        extern value_type mae;


        /*
         *  Cross Entropy or Log Loss Error
         */

        extern value_type xee;
        
    }
    
    
    /*
     *  export detail symbols to outer namespace
     */
    
    using detail::value_type;
    using detail::mse, detail::mae, detail::xee;
    using detail::accumulate;
    
};
