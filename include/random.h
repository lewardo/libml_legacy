#pragma once

#include <random>
#include <concepts>
#include <ranges>
#include <ctime>

#include "types.h"
#include "utils.h"

constexpr const double RAND_COEFF = RAND_MAX / 2;

namespace ml::internal::random {
    template <typename T> requires std::convertible_to<T, flt>
    void generate(T& value) {
        [[ maybe_unused ]]
        static auto seed = []() { 
            std::srand( std::time(nullptr) );
            return 0;
        } ();
        
        value = std::rand() / RAND_COEFF - 1.0f;
    }
    
    template <typename T> requires std::ranges::range<T>
    void generate(T& container) {
        for(auto& i : container) generate(i);
    }
} 