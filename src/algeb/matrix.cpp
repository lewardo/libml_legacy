#include <cstdbool>
#include <cstdint>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <execution>

#include "types.h"
#include "algeb.h"
#include "utils.h"

using namespace ml::types;

namespace ml::types {
    enum vector_class: uint32_t {
        COL_VEC = 0,
        ROW_VEC,
    };

    template <typename ...Args>
    matrix repeat(const vector_class c, const uint32_t n, Args&&... args) {
        vector v(std::forward<Args>(args)...);
        matrix m(n, v);

        if(c == COL_VEC) return transpose(m);
        else return m;
    }

    template <typename ...Args>
    matrix repeat(const vector_class c, const uint32_t n, std::initializer_list<flt> init, Args&&... args) {
        vector v(std::forward<std::initializer_list<flt>> (init), std::forward<Args> (args)...);
        matrix m(n, v);

        if(c == COL_VEC) return transpose(m);
        else return m;
    }

    bool verify(const matrix& m) {
        const size_t size = m.front().size();
        
        return std::all_of(
            std::execution::par,
            m.begin() + 1, m.end(), 
            [&size](const vector& v) {
                return v.size();
            }
        );
    }

    matrix transpose(const matrix& term) {
        if(not verify(term)) throw std::invalid_argument("matrix shape invalid");
        
        matrix transposed(term.front().size(), vector(term.size()));
        
        std::for_each(
            std::execution::par, 
            term.begin(), term.end(),
            [&](const vector& row) {
                typename matrix::difference_type row_n = c_cast<typename matrix::const_iterator>( &row ) - term.begin();
                    
                std::for_each(
                    std::execution::par,
                    row.begin(), row.end(),
                    [&](const flt& val) {
                        transposed[c_cast<typename vector::const_iterator> (&val) - row.begin()][row_n] = val;
                    }
                );
            }
        );
        
        return transposed;
    };
}

matrix operator+(const matrix& lterm, const flt& rterm) {
    matrix res(lterm.size(), vector(lterm.front().size()));
    vector vec(lterm.front().size(), rterm);

    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        vec.begin(), 
        res.begin(), 
        [](const vector& row, const flt& val) -> vector {
            return row + val;
        }
    );

    return res;
};

matrix operator+(const matrix& lterm, const matrix& rterm) {
    if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator+ matrix size mismatch");

    matrix res(lterm.size(), vector(lterm.front().size()));
    
    std::transform(
        std::execution::par,
        lterm.begin(), lterm.end(),
        rterm.begin(), 
        res.begin(),
        [](const vector& lrow, const vector& rrow) -> std::vector<flt> {
            return lrow + rrow;
        }
    );

    return res;
};

matrix& operator+=(matrix& lterm, const flt& rterm) {
    matrix res(lterm.size(), vector(lterm.front().size()));
    vector vec(lterm.front().size(), rterm);

    std::transform(
        std::execution::par,
        lterm.begin(), lterm.end(),
        vec.begin(),
        res.begin(),
        [](const vector& row, const flt& val) -> vector {
            return row + val;
        }
    );

    lterm = std::move(res);

    return lterm;
};

matrix& operator+=(matrix& lterm, const matrix& rterm) {
    if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator+ matrix size mismatch");

    matrix res(lterm.size(), vector(lterm.front().size()));
    
    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        rterm.begin(), 
        res.begin(), 
        [](const vector& lrow, const vector& rrow) -> vector {
            return lrow + rrow;
        }
    );

    lterm = std::move(res);

    return lterm;
};

matrix operator-(const matrix& lterm, const flt& rterm) {
    matrix res(lterm.size(), vector(lterm.front().size()));
    vector vec(lterm.front().size(), rterm);

    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        vec.begin(), 
        res.begin(), 
        [](const vector& row, const flt& val) -> vector {
            return row - val;
        }
    );

    return res;
};

matrix operator-(const matrix& lterm, const matrix& rterm) {
    if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator+ matrix size mismatch");

    matrix res(lterm.size(), vector(lterm.front().size()));
    
    std::transform(
        std::execution::par,
        lterm.begin(), lterm.end(),
        rterm.begin(), 
        res.begin(),
        [](const vector& lrow, const vector& rrow) -> std::vector<flt> {
            return lrow - rrow;
        }
    );

    return res;
};

matrix& operator-=(matrix& lterm, const flt& rterm) {
    matrix res(lterm.size(), vector(lterm.front().size()));
    vector vec(lterm.front().size(), rterm);

    std::transform(
        std::execution::par,
        lterm.begin(), lterm.end(),
        vec.begin(),
        res.begin(),
        [](const vector& row, const flt& val) -> vector {
            return row - val;
        }
    );

    lterm = std::move(res);

    return lterm;
};

matrix& operator-=(matrix& lterm, const matrix& rterm) {
    if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator+ matrix size mismatch");

    matrix res(lterm.size(), vector(lterm.front().size()));
    
    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        rterm.begin(), 
        res.begin(), 
        [](const vector& lrow, const vector& rrow) -> vector {
            return lrow - rrow;
        }
    );

    lterm = std::move(res);

    return lterm;
};

matrix operator*(const matrix& lterm, const flt& rterm) {
    matrix res(lterm.size(), vector(lterm.front().size()));
    vector vec(lterm.front().size(), rterm);

    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        vec.begin(), 
        res.begin(), 
        [](const vector& row, const flt& val) -> vector {
            return row * val;
        }
    );

    return res;
};

vector operator*(const matrix& lterm, const vector& rterm) {
    matrix mat = ml::types::repeat(ROW_VEC, lterm.size(), rterm);
    vector res(lterm.size());

    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        mat.begin(), 
        res.begin(), 
        [](const vector& lrow, const vector& rrow) -> flt {
            return lrow * rrow;
        }
    );

    return res;
};

// matrix operator*(const matrix& lterm, const matrix& rterm) {
// 
// };

matrix operator&(const matrix& lterm, const flt& rterm) {
    return operator*(std::forward<const matrix&>(lterm), std::forward<const flt&>(rterm));
};

matrix operator&(const matrix& lterm, const matrix& rterm) {
    if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator& matrix size mismatch");

    matrix res(lterm.size());
    
    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        rterm.begin(), 
        res.begin(), 
        [](const vector& lrow, const vector& rrow) -> vector {
            return lrow & rrow;
        }
    );

    return res;
};

matrix operator*=(matrix& lterm, const flt& rterm) {
    matrix res(lterm.size(), vector(lterm.front().size()));
    vector vec(lterm.front().size(), rterm);

    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        vec.begin(), 
        res.begin(), 
        [](const vector& row, const flt& val) -> vector {
            return row * val;
        }
    );
    
    lterm = std::move(res);

    return lterm;
};

matrix operator&=(matrix& lterm, const flt& rterm) {
    return operator*=(std::forward<matrix&>(lterm), std::forward<const flt&>(rterm));
};

matrix operator&=(matrix& lterm, const matrix& rterm) {
    if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator& matrix size mismatch");

    matrix res(lterm.size());
    
    std::transform(
        std::execution::par, 
        lterm.begin(), lterm.end(), 
        rterm.begin(), 
        res.begin(), 
        [](const vector& lrow, const vector& rrow) -> vector {
            return lrow & rrow;
        }
    );
    
    lterm = std::move(res);

    return lterm;
};

// matrix& operator*=(const std::matrix<flt>& other);
