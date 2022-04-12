#pragma once

#include <initializer_list>

#include "types.h"


namespace ml::types {
    enum vector_class : uint32_t;
    
    template <typename ...Args>
    matrix repeat(const vector_class, const uint32_t, Args&&...);
    
    template <typename ...Args>
    matrix repeat(const vector_class, const uint32_t, std::initializer_list<flt>, Args&&...);
    
    matrix transpose(const matrix&);
    bool verify(const matrix&);
};

/*
 *  addition defintions
 */

ml::types::vector operator+(const ml::types::vector&, const ml::types::flt&);
ml::types::vector operator+(const ml::types::vector&, const ml::types::vector&);

ml::types::matrix operator+(const ml::types::matrix&, const ml::types::flt&);
ml::types::matrix operator+(const ml::types::matrix&, const ml::types::matrix&);

/*
 *  plus-equals defintions
 */

ml::types::vector& operator+=(ml::types::vector&, const ml::types::flt&);
ml::types::vector& operator+=(ml::types::vector&, const ml::types::vector&);

ml::types::matrix& operator+=(ml::types::matrix&, const ml::types::flt&);
ml::types::matrix& operator+=(ml::types::matrix&, const ml::types::matrix&);


/*
 *  subtraction defintions
 */

ml::types::vector operator-(const ml::types::vector&, const ml::types::flt&);
ml::types::vector operator-(const ml::types::vector&, const ml::types::vector&);

ml::types::matrix operator-(const ml::types::matrix&, const ml::types::flt&);
ml::types::matrix operator-(const ml::types::matrix&, const ml::types::matrix&);

/*
 *  minus-equals defintions
 */

ml::types::vector& operator-=(ml::types::vector&, const ml::types::flt&);
ml::types::vector& operator-=(ml::types::vector&, const ml::types::vector&);

ml::types::matrix& operator-=(ml::types::matrix&, const ml::types::flt&);
ml::types::matrix& operator-=(ml::types::matrix&, const ml::types::matrix&);

/*
 *  dot product defintions
 */

ml::types::flt operator*(const ml::types::vector&, const ml::types::vector&);
ml::types::vector operator*(const ml::types::vector&, const ml::types::flt&);

ml::types::matrix operator*(const ml::types::matrix&, const ml::types::flt&);
ml::types::vector operator*(const ml::types::matrix&, const ml::types::vector&);

/*
 *  elementwise (hadamarand) product defintions
 */

ml::types::vector operator&(const ml::types::vector&, const ml::types::vector&);
ml::types::vector operator&(const ml::types::vector&, const ml::types::flt&);

ml::types::matrix operator&(const ml::types::matrix&, const ml::types::flt&);
ml::types::matrix operator&(const ml::types::matrix&, const ml::types::matrix&);

/*
 *  times-equals defintions
 */

ml::types::vector& operator*=(ml::types::vector&, const ml::types::flt&);
ml::types::vector& operator&=(ml::types::vector&, const ml::types::vector&);

ml::types::matrix operator*=(ml::types::matrix&, const ml::types::flt&);
ml::types::matrix operator&=(ml::types::matrix&, const ml::types::flt&);
ml::types::matrix operator&=(ml::types::matrix&, const ml::types::matrix&);
