#pragma once

#include <vector>

#include "types.h"


ml::types::vector operator+(const ml::types::vector&, const ml::types::flt&);
ml::types::vector operator+(const ml::types::vector & first, const ml::types::vector&);

ml::types::vector& operator+=(ml::types::vector&, const ml::types::flt&);
ml::types::vector& operator+=(ml::types::vector&, const ml::types::vector&);

ml::types::vector operator-(const ml::types::vector&, const ml::types::flt&);
ml::types::vector operator-(const ml::types::vector&, const ml::types::vector&);

ml::types::vector& operator-=(ml::types::vector&, const ml::types::flt&);
ml::types::vector& operator-=(ml::types::vector&, const ml::types::vector&);

ml::types::flt operator*(const ml::types::vector&, const ml::types::vector&);
ml::types::vector operator*(const ml::types::vector&, const ml::types::flt&);

ml::types::vector operator&(const ml::types::vector&, const ml::types::vector&);
ml::types::vector operator&(const ml::types::vector&, const ml::types::flt&);

ml::types::vector& operator*=(ml::types::vector&, const ml::types::flt&);
ml::types::vector& operator&=(ml::types::vector&, const ml::types::vector&);
