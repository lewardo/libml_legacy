#pragma once

#include <vector>

namespace Neural {
    using vfloat = std::vector<float>;
    using mfloat = std::vector<vfloat>;

    template <typename inType, typename outType> 
    class Net;

    class mlp;
};

template <typename inType, typename outType>
using Network = Neural::Net<inType, outType>;