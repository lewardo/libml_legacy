#pragma once

#include <initializer_list>
#include <execution>
#include <stdexcept>

#include "types.h"
#include "utils.h"

namespace ml::types {
    enum vector_class {
        COL_VEC = 0,
        ROW_VEC,
    };
    
    template <typename ...Args>
    matrix repeat(const vector_class c, const uint32_t n, Args&&... args) {
        switch(c) {
            default: throw std::invalid_argument("vector class invalid");
            
            case ROW_VEC: {
                vector v(std::forward<Args>(args)...);
                return matrix(n, v);
            }
            
            case COL_VEC: {                
                vector v(std::forward<Args>(args)...);
                matrix m(v.size());
                
                std::for_each(
                    std::execution::par_unseq,
                    m.begin(), m.end(),
                    [&](vector& row) {                        
                        row.resize(n, v[ml::utils::iterator_index(row, m)]);
                    }
                );
                
                return m;
            }
        }
    }

    template <typename ...Args>
    matrix repeat(const vector_class c, const uint32_t n, std::initializer_list<flt> init, Args&&... args) {
        switch(c) {
            default: throw std::invalid_argument("vector class invalid");
            
            case ROW_VEC: {
                vector v(std::forward<std::initializer_list<flt>>(init), std::forward<Args>(args)...);
                return matrix(n, v);
            }
            
            case COL_VEC: {                
                vector v(std::forward<std::initializer_list<flt>>(init), std::forward<Args>(args)...);
                matrix m(v.size());
                
                std::for_each(
                    std::execution::par_unseq,
                    m.begin(), m.end(),
                    [&](vector& row) {                        
                        row.resize(n, v[ml::utils::iterator_index(row, m)]);
                    }
                );
                
                return m;
            }
        }
    }
    
    matrix transpose_of(const matrix&);
    bool verify_matrix(const matrix&);

    /*
     *  addition defintions
     */

    vector operator+(const vector&, const flt&);
    vector operator+(const vector&, const vector&);

    matrix operator+(const matrix&, const flt&);
    matrix operator+(const matrix&, const matrix&);

    /*
     *  plus-equals defintions
     */

    vector& operator+=(vector&, const flt&);
    vector& operator+=(vector&, const vector&);

    matrix& operator+=(matrix&, const flt&);
    matrix& operator+=(matrix&, const matrix&);


    /*
     *  subtraction defintions
     */

    vector operator-(const vector&, const flt&);
    vector operator-(const vector&, const vector&);

    matrix operator-(const matrix&, const flt&);
    matrix operator-(const matrix&, const matrix&);

    /*
     *  minus-equals defintions
     */

    vector& operator-=(vector&, const flt&);
    vector& operator-=(vector&, const vector&);

    matrix& operator-=(matrix&, const flt&);
    matrix& operator-=(matrix&, const matrix&);

    /*
     *  dot product defintions
     */

    flt operator*(const vector&, const vector&);
    vector operator*(const vector&, const flt&);

    matrix operator*(const matrix&, const flt&);
    vector operator*(const matrix&, const vector&);
    matrix operator*(const matrix&, const matrix&);

    /*
     *  elementwise (hadamarand) product defintions
     */

    vector operator&(const vector&, const flt&);
    vector operator&(const vector&, const vector&);

    matrix operator&(const matrix&, const flt&);
    matrix operator&(const matrix&, const matrix&);

    /*
     *  times-equals defintions
     */

    vector& operator*=(vector&, const flt&);
    vector& operator&=(vector&, const vector&);

    matrix& operator*=(matrix&, const flt&);
    matrix& operator*=(matrix&, const matrix&);
    matrix& operator&=(matrix&, const flt&);
    matrix& operator&=(matrix&, const matrix&);
};
