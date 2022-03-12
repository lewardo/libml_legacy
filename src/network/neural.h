#pragma once

#include <vector>
#include <concepts>

#include "types.h"

namespace ml::net {
    using namespace ml::types;

    template <typename Ti, typename To>
    class network;
    
    template <typename Ti, typename To>
    f32 train(network<Ti, To>&);

    template <typename Ti, typename To>    
    f32 predict(network<Ti, To>&);

    class mlp;
};

namespace ml {
    using namespace types;
    
    template <typename Ti, typename To>
    using network = net::network<Ti, To>;
};