#pragma once

#include <vector>
#include <concepts>

#include "types.h"

namespace ml::net {
    using namespace ml::types;

    template <typename Ti, typename To>
    class network;
    
    template <typename Ti, typename To>
    flt train(network<Ti, To>&);

    template <typename Ti, typename To>    
    flt predict(network<Ti, To>&);

    class mlp;
};

namespace ml {
    using namespace ml::types;
    
    template <typename Ti, typename To>
    using network = net::network<Ti, To>;
};