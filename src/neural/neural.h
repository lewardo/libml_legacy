#pragma once

#include <vector>

#include "types.h"

namespace Neural {
    using namespace mltypes;

    template <typename it, typename ot> 
    class net;

    class mlp;
};

template <typename it, typename ot>
using Network = Neural::net<it, ot>;