#pragma once

#include <cstdint>
#include <vector>
#include <array>


/*
 *  c++ style casting function for vanilla c cast; i.e. c_cast<to>(from)
 */

template <typename T>
T c_cast(auto&& o) {
    return ((T) (o));
};


/*
 *  namespace types
 */

namespace ml::internal::types {
    
    /*
     *  library-wide decimal precision, for example 
     */
     
    using flt = float;
    
    
    /*
     *  vector and matrix type aliases
     */
     
    using vector = std::vector<flt>;
    using matrix = std::vector<std::vector<flt>>;
    
    
    /*
     *  time series of fixed length as array
     */
     
    template <std::size_t N, typename T>
    using series = std::array<T, N>;
    
};
