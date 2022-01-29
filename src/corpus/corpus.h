#pragma once

#include <cstdbool>
#include <vector>
#include <initializer_list>

#include "types.h"

namespace Corpus {
    using namespace mltypes;

    template <typename t>
    class base {
        public:
            base(std::string);
            base(std::initializer_list<t>);

            virtual ~base() = default;

            virtual t operator [](const i32& idx) = 0;

        protected:
            std::vector<t> data;
    };


    class set :public base<f32> {
        public:
            using base<f32>::base;

            f32 operator [](const i32&) override;
    };


    class map :public base<df32> {
        public:
            map(std::string);
            map(std::initializer_list<df32>);

            df32 operator [](const i32&) override;
    };
}