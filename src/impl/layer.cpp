#include <cstddef>
#include <algorithm>

#include "layer.h"
#include "random.h"
#include "utils.h"

namespace ml::networks::detail {
    network_layer::network_layer(size_t size, size_t next_size)
    :   _x(size), _dx(size),
        _b(size), _db(size),
        _w(next_size, vector(size)), _dw(next_size, vector(size)),
        _af(actf::sigmoid) {
        random::generate(_b);
        random::generate(_b);
    };

    void network_layer::forward_propagate(network_layer& next) {
        ifnt(next._x.size() != _w.size()) return;

    };

    void network_layer::consume_parameters(float_type) {

        // reset parameters
        std::ranges::fill(_db, 0);
        std::ranges::fill(_dw, vector(_x.size()));
    };
};
