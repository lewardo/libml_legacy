#pragma once

#include <vector>

#define types(n, t)                     \
    n = t;                              \
    using p ## n = std::unique_ptr<t>;  \
    using d ## n = std::pair<t, t>;     \
    using v ## n = std::vector<t>;      \
    using m ## n = std::vector<v ## n>

namespace mltypes {
    using types(f32, float);
    using types(i32, int32_t);
    using types(u32, uint32_t);
}