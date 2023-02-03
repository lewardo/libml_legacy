#pragma once

#include <cstddef>

#include "actfunc.h"
#include "types.h"

namespace ml::networks {

    namespace detail {
        using namespace internal;
        using namespace internal::types;

        class network_layer {
            network_layer(size_t, size_t);

            void forward_propagate(network_layer&);
            void backward_propagate(network_layer&);

            void consume_parameters(float_type);

            private:
                vector _x, _dx, _b, _db;
                matrix _w, _dw;

                actfunc _af;
        };
    }
}
