#pragma once

#include <random>
#include <concepts>
#include <ranges>
#include <execution>
#include <algorithm>
#include <ctime>

#include "types.h"
#include "utils.h"


static constexpr double RAND_COEFF = RAND_MAX / 2;

namespace ml::internal::random {

    /*
     *  detail namespace as to not import other namespaces to `namespace network` directly
     */

    namespace detail {

        /*
         *  using declarations
         */

        using namespace types;


        /*
         *  float-esque atomic generation of random number in range (-1, 1), with once-executing random seed
         */

        template <typename T> requires std::convertible_to<T, flt>
        void generate(T& value) {
            [[ maybe_unused ]]
            static auto seed = []() {
                std::srand( std::time(nullptr) );
                return 0;
            } ();

            value = std::rand() / RAND_COEFF - 1.0f;
        };


        /*
         *  container concept overload to iterate through all containers and meta-containers until atomic float-esque reached
         */

        template <typename T> requires std::ranges::range<T> && requires { typename T::value_type; }
        void generate(T& container) {
            std::for_each(
                std::execution::par_unseq,
                container.begin(), container.end(),
                [&] (T::value_type& i) {
                    generate(i);
                }
            );
        };
    };


    /*
     *  export detail symbols to outer namespace
     */

    using detail::generate;

};
