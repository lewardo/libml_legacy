#pragma once

#include <cstddef>
#include <variant>
#include <vector>
#include <array>

#include "pproc.h"


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

ml_namespace(internal, types) {

    using index_t = decltype(0); // default integer rvalue type

    enum slice_t: index_t {
        SLICE = 0,
    };

    /*
     *  library-wide decimal precision, for example
     */

    using flt = float;


    /*
     *  vector and matrix type aliases
     */

    using vector = std::vector<flt>;
    using matrix = std::vector<std::vector<flt>>;


    using empty_type = std::monostate;


    /*
     *  time series of fixed length as array
     */

    template <size_t N, typename T>
    using series = std::array<T, N>;

};
