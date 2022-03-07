#pragma once

#include <vector>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <utility>

#include "types.h"

namespace mltypes {
    /*
     *  helper function to extract std::vector
     */
    template <typename T>
    std::vector<T>& std(const mltypes::vector<T>& v) {
        return c_cast(mltypes::vector<T>&, v).std();
    };

    template <typename T>
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
            vector(std::initializer_list<T> init, Args&&... args):
                _internal(init, std::forward<Args>(args)...) {}


            /*
             *  explicit std::vector constructor to allow automatic type casting
             */

            vector(const std::vector<T>& init):
                _internal(init) {};


            /*
             *  copy constructor
             */

            vector(const mltypes::vector<T>& init):
                _internal(init._internal) {};


            /*
             *  move constructor
             */

            vector(mltypes::vector<T>&& init):
                _internal(std::move(init._internal)) {};

            /*
             *  destructor
             */

             ~vector() = default;


            /*
             *  copy assignment operator
             */

            mltypes::vector<T>& operator=(const mltypes::vector<T>& other) {
                _internal = other._internal;
            };


            /*
             *  move assignment operator
             */

            mltypes::vector<T>& operator=(mltypes::vector<T>&& other) {
                _internal = std::move(other._internal);
            };



            /*
             *  casting operator to allow automatic type conversion
             */

            operator std::vector<T>() const {
                return _internal;
            };


            /*
             *  addition operations, returning new objects
             */

            mltypes::vector<T> operator+(const T& x) const {
                std::vector<T> merged, other(_internal.size(), x);  // output vector, summee though std::vector's repeat constructor

                std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ std::back_inserter(merged), std::plus<T>());

                return merged;
            };

            mltypes::vector<T> operator+(const std::vector<T>& other) const {
                std::vector<T> merged;

                std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ std::back_inserter(merged), std::plus<T>());

                return merged;
            };


            /*
             *  plus-equals operations, returns reference to self after incrementation (elementwise and scalar)
             */

            mltypes::vector<T>& operator+=(const T& x) {
                std::vector<T> other(_internal.size(), x);

                std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ _internal.begin(), std::plus<T>());

                return *this;
            };

            mltypes::vector<T>& operator+=(const std::vector<T>& other) {
                if(_internal.size() != other.size()) throw std::length_error("operator+= vector size mismatch");

                std::transform(_internal.begin(), _internal.end(),other.begin(), /* other.end(), */ _internal.begin(), std::plus<T>());

                return *this;
            };


            /*
             *  subtraction operations, bound to increment operations through template literal
             */

            template<typename Arg>
            auto operator-(Arg&& arg) -> decltype(operator+(std::forward<Arg>(arg)) * -1) const {
                return operator+(std::forward<Arg>(arg) * -1);
            }


            /*
             *  minus-equals operations, bound to increment operations through template literal
             */

            template<typename Arg>
            auto operator-=(Arg&& arg) -> decltype(operator+=(std::forward<Arg>(arg)) * -1) {
                return operator+=(std::forward<Arg>(arg) * -1);
            }


            /*
             *  multiplication operations: scalar product, dot product and hadamarand (elementwise) product respectively
             */

            T operator*(const std::vector<T>& other) const {
                std::vector<T> merged;

                if(_internal.size() != other.size()) throw std::length_error("operator* vector size mismatch");

                std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ std::back_inserter(merged), std::multiplies<T>());

                return std::accumulate(merged.begin(), merged.end(), 0.0f);
            };

            mltypes::vector<T> operator*(const T& x) const {
                std::vector<T> merged, other(_internal.size(), x);

                std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ std::back_inserter(merged), std::multiplies<T>());

                return merged;
            };

            mltypes::vector<T> operator&(const std::vector<T>& other) const {
                std::vector<T> merged;

                if(_internal.size() != other.size()) throw std::length_error("operator* vector size mismatch");

                std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ std::back_inserter(merged), std::multiplies<T>());

                return merged;
            };


            /*
             *  times-equals operations: scalar product and hadamarand (elementwise) product respectively
             */

             mltypes::vector<T>& operator*=(const T& x) {
                 std::vector<T> other(_internal.size(), x);

                 std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ _internal.begin(), std::multiplies<T>());

                 return *this;
             };

             mltypes::vector<T>& operator&=(const std::vector<T>& other) {
                 if(_internal.size() != other.size()) throw std::length_error("operator* vector size mismatch");

                 std::transform(_internal.begin(), _internal.end(), other.begin(), /* other.end(), */ _internal.begin(), std::multiplies<T>());

                 return *this;
             };


            /*
             *  array access operator
             */

            T operator[](const u32 idx) const {
                return _internal[idx];
            };


            /*
             *  static helper funtion to access internal std::vector, use mltypes::std(v) instead
             */

            std::vector<T>& std() const {
                return c_cast(std::vector<T>&, _internal);
            };

        private:
            /*
             *  internal vector
             */

            std::vector<T> _internal;
            u32 _dim;
    };
};
