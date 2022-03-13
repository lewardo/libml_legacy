#pragma once

#include <cstdbool>
#include <vector>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <execution>
#include <utility>

#include "types.h"

namespace std {
    template<typename T>
    using matrix = vector<vector<T>>;
}

namespace ml::types {
    using direction_t = enum {
        DIR_VERT = 0,
        DIR_HORZ
    };


    class matrix {
        public:
            template <typename ...Args>
            matrix(Args&&... args):
                _internal(std::forward<Args>(args)...),
                _transposed(false) {}

            template <typename ...Args>
            matrix(std::initializer_list<flt> init, Args&&... args):
                _internal(init, std::forward<Args>(args)...),
                _transposed(false) {}

            matrix(const std::matrix<flt>& init):
                _internal(init),
                _transposed(false) {};

            matrix(const ml::types::matrix& init):
                _internal(init),
                _transposed(false) {};

            matrix(ml::types::matrix&& init):
                _internal(std::move(init._internal)),
                _transposed(init._transposed) {};

            ~matrix() = default;

            matrix& operator=(const matrix& other) {
                _internal = other._internal;
                _transposed = _transposed;
                
                return *this;
            };
            
            matrix& operator=(const std::matrix<flt>& m) {
                _internal = m;
                _transposed = false;
                
                return *this;
            };

            matrix& operator=(matrix&& other) {
                _internal = std::move(other._internal),
                _transposed = other._transposed;
                
                return *this;
            };
            
            matrix& operator=(std::matrix<flt>&& m) {
                _internal = std::move(m);
                _transposed = false;
                
                return *this;
            };

            operator std::matrix<flt>() const {
                return _internal;
            };

            matrix operator+(const flt& x) const {
                std::matrix<flt> merged(_internal.size());
                std::vector<flt> v(_internal[0].size(), x);
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), v.begin(), merged.begin(), [](const std::vector<flt>& row, const flt& val) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current += val);
                });
                
                return merged;
            };
            
            matrix operator+(const std::matrix<flt>& other) const {
                if(_internal.size() != other.size() || _internal[0].size() != other[0].size()) throw std::length_error("operator+ matrix size mismatch");

                std::matrix<flt> merged(_internal.size());
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current += other_row);
                });
                
                return merged;
            };

            matrix& operator+=(const flt& x) {
                std::matrix<flt> merged(_internal.size());
                std::vector<flt> v(_internal[0].size(), x);
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), v.begin(), merged.begin(), [](const std::vector<flt>& row, const flt& val) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current += val);
                });
                
                _internal = std::move(merged);
                
                return *this;
            };
            
            matrix& operator+=(const std::matrix<flt>& other) {
                if(_internal.size() != other.size() || _internal[0].size() != other[0].size()) throw std::length_error("operator+ matrix size mismatch");

                std::matrix<flt> merged(_internal.size());
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current += other_row);
                });
                
                _internal = std::move(merged);
                
                return *this;
            };

            matrix operator-(const flt& x) const {
                std::matrix<flt> merged(_internal.size());
                std::vector<flt> v(_internal[0].size(), x);
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), v.begin(), merged.begin(), [](const std::vector<flt>& row, const flt& val) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current -= val);
                });
                
                return merged;
            };
            
            matrix operator-(const std::matrix<flt>& other) const {
                if(_internal.size() != other.size() || _internal[0].size() != other[0].size()) throw std::length_error("operator+ matrix size mismatch");

                std::matrix<flt> merged(_internal.size());
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current -= other_row);
                });
                
                return merged;
            };

            matrix& operator-=(const flt& x) {
                std::matrix<flt> merged(_internal.size());
                std::vector<flt> v(_internal[0].size(), x);
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), v.begin(), merged.begin(), [](const std::vector<flt>& row, const flt& val) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current -= val);
                });
                
                _internal = std::move(merged);
                
                return *this;
            };
            
            matrix& operator-=(const std::matrix<flt>& other) {
                if(_internal.size() != other.size() || _internal[0].size() != other[0].size()) throw std::length_error("operator+ matrix size mismatch");

                std::matrix<flt> merged(_internal.size());
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current -= other_row);
                });
                
                _internal = std::move(merged);
                
                return *this;
            };

            matrix operator*(const flt& x) const {
                std::matrix<flt> merged(_internal.size());
                std::vector<flt> v(_internal[0].size(), x);
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), v.begin(), merged.begin(), [](const std::vector<flt>& row, const flt& val) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current *= val);
                });
                
                return merged;
            };
            
            vector operator*(const std::vector<flt>& v) const {
                std::matrix<flt> other = repeat(DIR_VERT, _internal.size(), v);
                std::vector<flt> merged(_internal.size());
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> flt {
                    vector current = std::move(row);
                    
                    return current * other_row;
                });
                
                return merged;
            };
            
            // matrix operator*(const std::matrix<flt>& other) const;

            matrix operator&(const flt& x) {
                return operator*(std::forward<const flt&> (x));
            };
            
            matrix operator&(const std::matrix<flt>& other) const {
                if(_internal.size() != other.size() || _internal[0].size() != other[0].size()) throw std::length_error("operator+ matrix size mismatch");

                std::matrix<flt> merged(_internal.size());
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current &= other_row);
                });
                
                return merged;
            };

            matrix& operator*=(const flt& x) {
                std::matrix<flt> merged(_internal.size());
                std::vector<flt> v(_internal[0].size(), x);
                
                std::transform(std::execution::par, _internal.begin(), _internal.end(), v.begin(), merged.begin(), [](const std::vector<flt>& row, const flt& val) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current *= val);
                });
                
                _internal = std::move(merged);
                
                return *this;
            };
            
            // matrix& operator*=(const std::matrix<flt>& other);
            
            matrix& operator&=(const flt& x) {
                return operator*=(std::forward<const flt&> (x));
            };
            
            matrix& operator&=(const std::matrix<flt>& other) {
                if(_internal.size() != other.size() || _internal[0].size() != other[0].size()) throw std::length_error("operator+ matrix size mismatch");

                std::matrix<flt> merged(_internal.size());
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), [](const std::vector<flt>& row, const std::vector<flt>& other_row) -> std::vector<flt> {
                    vector current = std::move(row);
                    
                    return types::std(current &= other_row);
                });
                
                _internal = std::move(merged);
                
                return *this;
            };

            matrix& operator~() {
                _transposed ^= true;
                
                return *this;
            };

            vector& operator[](const unsigned int idx) const {
                return c_cast<vector&> (_internal[idx]);
            };

            template <typename ...Args>
            static matrix repeat(const direction_t d, const unsigned int n, Args&&... args) {
                vector v(std::forward<Args>(args)...);
                matrix m(n, v);
                
                if(d == DIR_HORZ) m._transposed ^= true;
                
                return m;
            }
            
            template <typename ...Args>
            static matrix repeat(const direction_t d, const unsigned int n, std::initializer_list<flt> init, Args&&... args) {
                vector v(std::forward<std::initializer_list<flt>> (init), std::forward<Args> (args)...);
                matrix m(n, v);
                
                if(d == DIR_HORZ) m._transposed ^= true;
                
                return m;
            }

            std::matrix<flt>& std() const {
                return c_cast<std::matrix<flt>&> (_internal);
            }

        private:
            /*
             *  internal variables
             */
            
            std::matrix<flt> _internal;
            bool _transposed;
    };
};

namespace ml::types {
    /*
     *  helper function to extract std::matrix
     */
    
    [[maybe_unused]]
    std::matrix<flt>& std(const matrix& m) {
        return c_cast<matrix&> (m).std();
    };
};
