#pragma once

#include <vector>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <execution>
#include <utility>

#include "types.h"

namespace ml::types {
    class vector {
        public:
            /*
             *  variadic constructor to forward to std::vector
             */

            template <typename ...Args>
            vector(Args&&... args):
                _internal(std::forward<Args>(args)...) {}


            /*
             *  variadic constructor to forward to std::vector for std::initializer_list constructors
             */

            template <typename ...Args>
            vector(std::initializer_list<f32> init, Args&&... args):
                _internal(init, std::forward<Args>(args)...) {}


            /*
             *  explicit std::vector constructor to allow automatic type casting
             */

            vector(const std::vector<f32>& init):
                _internal(init) {};


            /*
             *  copy constructor
             */

            vector(const vector& init):
                _internal(init._internal) {};


            /*
             *  move constructor
             */

            vector(vector&& init):
                _internal(std::move(init._internal)) {};

            /*
             *  destructor
             */

             ~vector() = default;


            /*
             *  copy assignment operator
             */

            vector& operator=(const vector& other) {
                _internal = other._internal;

                return *this;
            };
            
            vector& operator=(const std::vector<f32>&v) {
                _internal = v;

                return *this;
            };


            /*
             *  move assignment operator
             */

            vector& operator=(vector&& other) {
                _internal = std::move(other._internal);

                return *this;
            };
            
            vector& operator=(std::vector<f32>&&v) {
                _internal = std::move(_internal);

                return *this;
            };



            /*
             *  casting operator to allow automatic type conversion
             */

            operator std::vector<f32>() const {
                return _internal;
            };


            /*
             *  addition operations, returning new objects
             */

            vector operator+(const f32& x) const {
                std::vector<f32> merged(_internal.size()), other(_internal.size(), x);
                std::transform(std::execution::par_unseq, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::plus<f32>());

                return merged;
            };

            vector operator+(const std::vector<f32>& other) const {
                if(_internal.size() != other.size()) throw std::length_error("operator+ vector size mismatch");
                
                std::vector<f32> merged(_internal.size());
                std::transform(std::execution::par_unseq, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::plus<f32>());

                return merged;
            };


            /*
             *  plus-equals operations, returns reference to self after incrementation (elementwise and scalar)
             */

            vector& operator+=(const f32& x) {
                std::vector<f32> other(_internal.size(), x);
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), _internal.begin(), std::plus<f32>());

                return *this;
            };

            vector& operator+=(const std::vector<f32>& other) {
                if(_internal.size() != other.size()) throw std::length_error("operator+= vector size mismatch");

                std::transform(std::execution::par, _internal.begin(), _internal.end(),other.begin(), _internal.begin(), std::plus<f32>());

                return *this;
            };


            /*
             *  subtraction operations, returning new objects
             */

            vector operator-(const f32& x) const {
                std::vector<f32> merged(_internal.size()), other(_internal.size(), x);
                std::transform(std::execution::par_unseq, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::minus<f32>());

                return merged;
            };

            vector operator-(const std::vector<f32>& other) const {
                if(_internal.size() != other.size()) throw std::length_error("operator- vector size mismatch");
                
                std::vector<f32> merged(_internal.size());
                std::transform(std::execution::par_unseq, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::minus<f32>());

                return merged;
            };


            /*
             *  minus-equals operations, returns reference to self after decrementation (elementwise and scalar)
             */

            vector& operator-=(const f32& x) {
                std::vector<f32> other(_internal.size(), x);
                std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), _internal.begin(), std::minus<f32>());

                return *this;
            };

            vector& operator-=(const std::vector<f32>& other) {
                if(_internal.size() != other.size()) throw std::length_error("operator-= vector size mismatch");

                std::transform(std::execution::par, _internal.begin(), _internal.end(),other.begin(), _internal.begin(), std::minus<f32>());

                return *this;
            };


            /*
             *  multiplication operations: scalar product, dot product and hadamarand (elementwise) product respectively
             */

            f32 operator*(const std::vector<f32>& other) const {
                if(_internal.size() != other.size()) throw std::length_error("operator* vector size mismatch");
                
                return std::transform_reduce(std::execution::par, _internal.begin(), _internal.end(), other.begin(), 0.0f);
            };

            vector operator*(const f32& x) const {
                std::vector<f32> other(_internal.size(), x);

                return std::transform_reduce(std::execution::par, _internal.begin(), _internal.end(), other.begin(), 0.0f);
            };

            vector operator&(const std::vector<f32>& other) const {
                if(_internal.size() != other.size()) throw std::length_error("operator& vector size mismatch");

                std::vector<f32> merged(_internal.size());
                std::transform(std::execution::par_unseq, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::multiplies<f32>());

                return merged;
            };


            /*
             *  times-equals operations: scalar product and hadamarand (elementwise) product respectively
             */

             vector& operator*=(const f32& x) {
                 std::vector<f32> other(_internal.size(), x);
                 std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), _internal.begin(), std::multiplies<f32>());

                 return *this;
             };

             vector& operator&=(const std::vector<f32>& other) {
                 if(_internal.size() != other.size()) throw std::length_error("operator&= vector size mismatch");

                 std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), _internal.begin(), std::multiplies<f32>());

                 return *this;
             };


            /*
             *  array access operator
             */

            f32 operator[](const u32 idx) const {
                return _internal[idx];
            };


            /*
             *  static helper funtion to access internal std::vector, use ml::types::std(v) instead
             */

            std::vector<f32>& std() const {
                return c_cast<std::vector<f32>&> (_internal);
            };

        private:
            /*
             *  internal vector
             */

            std::vector<f32> _internal;
    };
};

namespace ml::types {
    /*
     *  helper function to extract std::vector
     */
     
    [[maybe_unused]]
    static std::vector<f32>& std(const vector& v) {
        return c_cast<vector&> (v).std();
    };
}
