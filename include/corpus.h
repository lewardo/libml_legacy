#pragma once

#include <cstdbool>
#include <vector>
#include <variant>
#include <initializer_list>

#include "types.h"

namespace ml::corpus {
    using namespace internal::types;

    template <int N>
    class base_type {
        public:
            base_type(std::string);

            virtual ~base_type() = default;

            virtual T operator[](const int&) = 0;

        protected:
            std::vector<std::array<flt, N>> _data;
    };
    // 
    // 
    // class set :public base<flt> {
    //     public:
    //         using base<flt>::base;
    // 
    //         flt operator [](const int&) override;
    // };
    // 
    // 
    // class map :public base<dflt> {
    //     public:
    //         map(std::string);
    // 
    //         dflt operator [](const int&) override;
    // };
}
