#include <iostream>

#include "types.h"
#include "utils.h"
#include "network.h"

#include "mlp.h"

using namespace ml::internal::types;
using namespace ml::internal::utils;

namespace ml::networks::detail {
    flt mlp_impl::propagate_values(const vector&, vector&) {
        
        return default_value<float>::value;
    };

    int mlp_impl::calculate_update(const vector&, vector&) {

        return default_value<int>::value;
    };

    int mlp_impl::execute_update() {

        return default_value<int>::value;
    };


    int mlp_impl::load_parameters(const std::string) {

        return default_value<int>::value;
    };

    int mlp_impl::save_parameters(const std::string) const {

        return default_value<int>::value;
    };

}