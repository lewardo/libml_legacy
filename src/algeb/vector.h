#pragma once

#include <vector>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <execution>
#include <utility>

#include "types.h"

class ml::types::vector {
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
        vector(std::initializer_list<flt> init, Args&&... args):
            _internal(std::forward<std::initializer_list<flt>> (init), std::forward<Args>(args)...) {}


        /*
         *  explicit std::vector constructor to allow automatic type casting
         */

        vector(const std::vector<flt>& init):
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
        
        vector& operator=(const std::vector<flt> &v) {
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
        
        vector& operator=(std::vector<flt>&& v) {
            _internal = std::move(_internal);

            return *this;
        };



        /*
         *  casting operator to allow automatic type conversion
         */

        operator std::vector<flt>() const {
            return _internal;
        };


        /*
         *  addition operations, returning new objects
         */

        vector operator+(const flt& x) const {
            std::vector<flt> merged(_internal.size()), other(_internal.size(), x);
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::plus<flt>());

            return merged;
        };

        vector operator+(const std::vector<flt>& other) const {
            if(_internal.size() != other.size()) throw std::length_error("operator+ vector size mismatch");
            
            std::vector<flt> merged(_internal.size());
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::plus<flt>());

            return merged;
        };


        /*
         *  plus-equals operations, returns reference to self after incrementation (elementwise and scalar)
         */

        vector& operator+=(const flt& x) {
            std::vector<flt> merged(_internal.size()), other(_internal.size(), x);
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::plus<flt>());
            
            _internal = std::move(merged);

            return *this;
        };

        vector& operator+=(const std::vector<flt>& other) {
            if(_internal.size() != other.size()) throw std::length_error("operator+= vector size mismatch");

            std::vector<flt> merged(_internal.size());
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::plus<flt>());
            
            _internal = std::move(merged);

            return *this;
        };


        /*
         *  subtraction operations, returning new objects
         */

        vector operator-(const flt& x) const {
            std::vector<flt> merged(_internal.size()), other(_internal.size(), x);
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::minus<flt>());

            return merged;
        };

        vector operator-(const std::vector<flt>& other) const {
            if(_internal.size() != other.size()) throw std::length_error("operator- vector size mismatch");
            
            std::vector<flt> merged(_internal.size());
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::minus<flt>());

            return merged;
        };


        /*
         *  minus-equals operations, returns reference to self after decrementation (elementwise and scalar)
         */

        vector& operator-=(const flt& x) {
            std::vector<flt> merged(_internal.size()), other(_internal.size(), x);
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::minus<flt>());
            
            _internal = std::move(merged);

            return *this;
        };

        vector& operator-=(const std::vector<flt>& other) {
            if(_internal.size() != other.size()) throw std::length_error("operator-= vector size mismatch");

            std::vector<flt> merged(_internal.size());
            std::transform(std::execution::par, _internal.begin(), _internal.end(),other.begin(), merged.begin(), std::minus<flt>());
            
            _internal = std::move(merged);
            
            return *this;
        };


        /*
         *  multiplication operations: scalar product, dot product and hadamarand (elementwise) product respectively
         */

        flt operator*(const std::vector<flt>& other) const {
            if(_internal.size() != other.size()) throw std::length_error("operator* vector size mismatch");
            
            return std::transform_reduce(std::execution::par, _internal.begin(), _internal.end(), other.begin(), 0.0f);
        };

        vector operator*(const flt& x) const {
            std::vector<flt> other(_internal.size(), x);

            return std::transform_reduce(std::execution::par, _internal.begin(), _internal.end(), other.begin(), 0.0f);
        };

        vector operator&(const std::vector<flt>& other) const {
            if(_internal.size() != other.size()) throw std::length_error("operator& vector size mismatch");

            std::vector<flt> merged(_internal.size());
            std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::multiplies<flt>());

            return merged;
        };


        /*
         *  times-equals operations: scalar product and hadamarand (elementwise) product respectively
         */

         vector& operator*=(const flt& x) {
             std::vector<flt> merged(_internal.size()), other(_internal.size(), x);
             std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::multiplies<flt>());
             
             _internal = std::move(merged);

             return *this;
         };

         vector& operator&=(const std::vector<flt>& other) {
             if(_internal.size() != other.size()) throw std::length_error("operator&= vector size mismatch");

             std::vector<flt> merged(_internal.size());
             std::transform(std::execution::par, _internal.begin(), _internal.end(), other.begin(), merged.begin(), std::multiplies<flt>());
             
             _internal = std::move(merged);

             return *this;
         };


        /*
         *  array access operator
         */

        flt operator[](const unsigned int idx) const {
            return _internal[idx];
        };


        /*
         *  static helper funtion to access internal std::vector, use ml::types::std(v) instead
         */

        std::vector<flt>& std() const {
            return c_cast<std::vector<flt>&> (_internal);
        };

    private:
        /*
         *  internal vector
         */

        std::vector<flt> _internal;
};

namespace ml::types {
    /*
     *  helper function to extract std::vector
     */
     
    [[maybe_unused]]
    static std::vector<flt>& std(const vector& v) {
        return c_cast<vector&> (v).std();
    };
}
