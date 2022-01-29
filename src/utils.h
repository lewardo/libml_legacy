#pragma once

#include <random>

#include "types.h"

namespace utils {
    using namespace mltypes;

    inline f32 random() {
        return 2 * rand() / RAND_MAX - 1.0f;
    };
}