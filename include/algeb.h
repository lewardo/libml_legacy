#pragma once

#include <initializer_list>
#include <execution>
#include <stdexcept>

#include "types.h"
#include "utils.h"

namespace ml::internal::types {
    
    /*
     *  detail namespace as to not import other namespaces to `namespace types` directly
     */

    namespace detail {
        
        /*
         *  using declarations
         */
         
        using namespace utils;
        
        
        /*
         *  enum to define direction of repetition depending on vector type
         */

        enum vector_class {
            COL_VEC = 0,
            ROW_VEC,
        };
        
        
        /*
         *  repeat helper to construct matrix from repeated vector
         */
        
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
                            row.resize(n, v[ml::internal::utils::iterator_index(row, m)]);
                        }
                    );
                    
                    return m;
                }
            }
        }
        
        
        /*
         *  repeat helper to construct matrix from repeated vector, with initialiser list constructor
         */

        template <typename ...Args>
        matrix repeat(const vector_class c, const uint32_t n, std::initializer_list<flt> init, Args&&... args) {
            vector v(std::forward<std::initializer_list<flt>>(init), std::forward<Args>(args)...);
            
            return repeat(c, n, v);
        }
        
        
        /*
         *  return transpose of matrix (not in-place)
         */
        
        matrix transpose_of(const matrix&);
        
        
        /*
         *  check whether matrix is rectangular (all rows same length)
         */
         
        bool verify_matrix(const matrix&);
        
    }
    
    
    /*
     *  export detail symbols to outer namespace
     */
     
    using detail::vector_class;
    using detail::ROW_VEC, detail::COL_VEC;
    using detail::repeat;
    using detail::transpose_of, detail::verify_matrix;
    
    
    /*
     *  function style operator+ overload defintions
     */

    vector operator+(const vector&, const flt&);
    vector operator+(const vector&, const vector&);

    matrix operator+(const matrix&, const flt&);
    matrix operator+(const matrix&, const matrix&);


    /*
     *  function style operator+= overload defintions
     */

    vector& operator+=(vector&, const flt&);
    vector& operator+=(vector&, const vector&);

    matrix& operator+=(matrix&, const flt&);
    matrix& operator+=(matrix&, const matrix&);


    /*
     *  function style operator- overload defintions
     */

    vector operator-(const vector&, const flt&);
    vector operator-(const vector&, const vector&);

    matrix operator-(const matrix&, const flt&);
    matrix operator-(const matrix&, const matrix&);


    /*
     *  function style operator-= overload defintions
     */

    vector& operator-=(vector&, const flt&);
    vector& operator-=(vector&, const vector&);

    matrix& operator-=(matrix&, const flt&);
    matrix& operator-=(matrix&, const matrix&);


    /*
     *  function style operator* overload defintions (dot product)
     */

    flt operator*(const vector&, const vector&);
    vector operator*(const vector&, const flt&);

    matrix operator*(const matrix&, const flt&);
    vector operator*(const matrix&, const vector&);
    matrix operator*(const matrix&, const matrix&);


    /*
     *  function style operator& overload defintions (hadamarand product)
     */

    vector operator&(const vector&, const flt&);
    vector operator&(const vector&, const vector&);

    matrix operator&(const matrix&, const flt&);
    matrix operator&(const matrix&, const matrix&);


    /*
     *  function style operator{*,&}= overload defintions (times-equals, dot and hadamarand respectively)
     */

    vector& operator*=(vector&, const flt&);
    vector& operator&=(vector&, const vector&);

    matrix& operator*=(matrix&, const flt&);
    matrix& operator*=(matrix&, const matrix&);
    matrix& operator&=(matrix&, const flt&);
    matrix& operator&=(matrix&, const matrix&);
    
};
