#include <cstdio>

#include "types.h"
#include "utils.h"
#include "network.h"

#include "mlp.h"

using namespace ml::internal::types;
using namespace ml::internal::utils;

namespace ml::networks::detail {
    mlp_impl::mlp_impl() {
        std::printf("constructing mlp impl\n");
    }
    
    flt mlp_impl::propagate_values(const vector& a, vector& b) {
        std::printf("propagate_values, %ld %ld\n", a.size(), b.size());
        
        return default_value<float>::value;
    };

    int mlp_impl::calculate_update(const vector& a, vector& b) {
        std::printf("calculate_update, %ld %ld\n", a.size(), b.size());

        return default_value<int>::value;
    };

    int mlp_impl::execute_update() {
        std::printf("execute_update\n");

        return default_value<int>::value;
    };


    int mlp_impl::load_parameters(const std::string s) {
        std::printf("load_parameters, %s\n", s.c_str());

        return default_value<int>::value;
    };

    int mlp_impl::save_parameters(const std::string s) const {
        std::printf("save_parameters, %s\n", s.c_str());

        return default_value<int>::value;
    };

}