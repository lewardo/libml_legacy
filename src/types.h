#pragma once

#include <vector>

template <typename T, typename S>
T c_cast(const S& o) {
    return ((T) (o));
};

namespace ml::types {
    using flt = float;  // or a double if you want a global change

    class vector;
    class matrix;

    template <typename T = vector>
    using series = std::vector<T>;
}
