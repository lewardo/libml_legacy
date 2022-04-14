#pragma once

#include <cstdint>
#include <concepts>
#include <vector>
#include <array>

template <typename T>
T c_cast(auto&& o) {
    return ((T) (o));
};

namespace ml::types {
    using flt = float;  // or a double if you want a global change
    
    using vector = std::vector<flt>;
    using matrix = std::vector<vector>;
        
    template <std::size_t N, typename T = vector>
    using series = std::array<T, N>;
};
