#pragma once

#include <random>
#include <concepts>
#include <cstdbool>

#include "types.h"

namespace ml::utils {
    using namespace types;

    inline f32 random() {
        return 2 * rand() / RAND_MAX - 1.0f;
    }
}
