#pragma once

#include <random>

namespace utils {
    inline float random() {
        return 2 * rand() / RAND_MAX - 1.0f;
    };
}