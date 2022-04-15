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

using namespace ml::utils;

namespace ml::types {
    bool verify_matrix(const matrix& m) {
        const size_t size = m.front().size();
        
        return std::all_of(
            std::execution::par_unseq,
            m.begin() + 1, m.end(), 
            [&size](const vector& v) -> decltype(v.size()) {
                return v.size();
            }
        );
    }
    
    matrix transpose_of(const matrix& term) {
        if(not verify_matrix(term)) throw std::invalid_argument("matrix shape invalid");
        
        matrix transposed(term.front().size(), vector(term.size()));
        
        std::for_each(
            std::execution::par_unseq, 
            term.begin(), term.end(),
            [&](const vector& row) {
                auto row_n = iterator_index(row, term);
                    
                std::for_each(
                    std::execution::par_unseq,
                    row.begin(), row.end(),
                    [&](const flt& val) {
                        transposed[iterator_index(val, row)][row_n] = val;
                    }
                );
            }
        );
        
        return transposed;
    };

    matrix operator+(const matrix& lterm, const flt& rterm) {
        matrix res(lterm.size(), vector(lterm.front().size()));
        vector vec(lterm.front().size(), rterm);

        std::transform(
            std::execution::par_unseq, 
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
            std::execution::par_unseq,
            lterm.begin(), lterm.end(),
            rterm.begin(), 
            res.begin(),
            [](const vector& lrow, const vector& rrow) -> vector {
                return lrow + rrow;
            }
        );

        return res;
    };

    matrix& operator+=(matrix& lterm, const flt& rterm) {
        matrix res(lterm.size(), vector(lterm.front().size()));
        vector vec(lterm.front().size(), rterm);

        std::transform(
            std::execution::par_unseq,
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
            std::execution::par_unseq, 
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
            std::execution::par_unseq, 
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
            std::execution::par_unseq,
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
            std::execution::par_unseq,
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
            std::execution::par_unseq, 
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
            std::execution::par_unseq, 
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
        if(lterm.front().size() != rterm.size()) throw std::length_error("matrix vector multipliciation size mismatch");
        
        matrix mat = ml::types::repeat(ROW_VEC, lterm.size(), rterm);
        vector res(lterm.size());

        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            mat.begin(), 
            res.begin(), 
            [](const vector& lrow, const vector& rrow) -> flt {
                return lrow * rrow;
            }
        );

        return res;
    };

    matrix operator*(const matrix& lterm, const matrix& rterm) {
        if(lterm.front().size() != rterm.size()) throw std::invalid_argument("matrix operator* size mismatch");
        if(not verify_matrix(lterm) || not verify_matrix(rterm)) throw std::invalid_argument("matrix not rectangular");
        
        matrix res(rterm.front().size()), t_rterm = transpose_of(rterm);
        
        std::transform(
            std::execution::par_unseq,
            t_rterm.begin(), t_rterm.end(),
            res.begin(),
            [&lterm](const vector& row) -> vector {
                return lterm * row;
            }
        );
        
        return transpose_of(res);
    };

    matrix operator&(const matrix& lterm, const flt& rterm) {
        return lterm * rterm;
    };

    matrix operator&(const matrix& lterm, const matrix& rterm) {
        if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator& matrix size mismatch");

        matrix res(lterm.size());
        
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            [](const vector& lrow, const vector& rrow) -> vector {
                return lrow & rrow;
            }
        );

        return res;
    };

    matrix& operator*=(matrix& lterm, const flt& rterm) {
        matrix res(lterm.size(), vector(lterm.front().size()));
        vector vec(lterm.front().size(), rterm);

        std::transform(
            std::execution::par_unseq, 
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

    matrix& operator&=(matrix& lterm, const flt& rterm) {
        return lterm *= rterm;
    };

    matrix& operator&=(matrix& lterm, const matrix& rterm) {
        if(lterm.size() != rterm.size() || lterm.front().size() != rterm.front().size()) throw std::length_error("operator& matrix size mismatch");

        matrix res(lterm.size());
        
        std::transform(
            std::execution::par_unseq, 
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
    
    matrix& operator*=(matrix& lterm, const matrix& rterm) {
        if(not verify_matrix(lterm) || not verify_matrix(rterm)) throw std::invalid_argument("matrix not rectangular");
        if(lterm.front().size() != rterm.size()) throw std::invalid_argument("matrix operator* size mismatch");
        if(rterm.front().size() != rterm.size()) throw std::invalid_argument("rterm of matrix *= must be a square matrix");
        
        matrix res(rterm.front().size()), t_rterm = transpose_of(rterm);
        
        std::transform(
            std::execution::par_unseq, 
            t_rterm.begin(), t_rterm.end(),
            res.begin(),
            [&lterm](const vector& row) -> vector {
                return lterm * row;
            }
        );
        
        lterm = std::move(transpose_of(res));
        
        return lterm;
    };
}
