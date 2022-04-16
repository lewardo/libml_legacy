#pragma once

#include "types.h"

namespace ml::networks {
    using namespace internal::types;

    template <typename iT, typename oT>
    class base_type;
    
    template <typename iT, typename oT>
    flt train(base_type<iT, oT>&);

    template <typename iT, typename oT>    
    flt predict(base_type<iT, oT>&);

    class mlp;
};

namespace ml { 
    template <typename iT, typename oT>
    using network = networks::base_type<iT, oT>;
};