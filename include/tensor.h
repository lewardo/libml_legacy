#pragma once

#include <iostream>
#include <cstddef>
#include <cassert>
#include <type_traits>
#include <functional>
#include <concepts>
#include <iterator>
#include <ranges>
#include <vector>
#include <valarray>
#include <tuple>

#include "types.h"
#include "utils.h"
#include "meta.h"
#include "pproc.h"

ml_namespace(internal, types) {

    namespace detail {

        using namespace utils;
        using namespace meta;

        template <typename T>
        concept valid_valarray = requires {
            typename std::valarray<T>::value_type;
        };

        template <typename T, size_t N>
        class tensor_slice;

        template <typename T, size_t N> requires valid_valarray<T>
        class tensor;


        template <size_t N>
        class tensor_extent {
            public:
                using ext_type      = std::array<size_t, N>;
                using strd_type     = std::array<size_t, N+1>;

                static constexpr auto rank = N;

                tensor_extent(ext_type dim)
                :   tensor_extent(dim, tr_dims(dim)) {};

                tensor_extent(ext_type dim, strd_type strd)
                :   _dimensions(dim),
                    _strides(strd) {};

                size_t dims(size_t i) const { return _dimensions[i  ]; };
                size_t strd(size_t i) const { return    _strides[i+1]; };

                ext_type dimensions() { return _dimensions; };
                ext_type strides() { return utils::sub_array<1, N+1>(_strides); };

                size_t size() const { return _strides[0]; };

                // please forgive me~
                template <typename... Args> requires meta::all_satisfy<std::is_convertible, size_t, Args...>::value && meta::equal<sizeof...(Args), N>::value
                decltype(auto) calculate_offset(Args... args) {
                    // compartimentalised and localised version of a deferring function, templated lambda that accetps index sequence and tuple of forwarded arguments, capturing `this` by reference
                    // asserts that all the arguments are in bound then returns elementwise multiplication with strides over summation fold expression
                    // calls lambda while forwarding args as tuple, and with index sequence of length args
                    return [this] <typename... Ts, template <typename...> class Tup, size_t... I> (const Tup<Ts...>& tup, std::index_sequence<I...>) {
                        assert("index out of bounds" && (((size_t) std::get<I>(tup) < _dimensions[I]) && ...));
                        return ((std::get<I>(tup) * _strides[I+1]) + ...);
                    } (std::tuple<Args...>(args...), std::make_index_sequence<N>{});
                };

                static constexpr strd_type tr_dims(const ext_type& dims) {
                    // lambdaified helper template function, to instantiate a parameter pack of N 1s (Is...) to initialise the stride array to ones programatically
                    return [&] <size_t... Is>(meta::sequence<Is...>) {
                        strd_type strd = { Is... };   // { 1, 1, 1, 1... }

                        for (size_t n = N; n > 0; --n)
                            strd[n-1] = dims[n-1] * strd[n];

                        return strd;
                    } (meta::make_repeat_sequence<N+1, 1>{});
                };

            private:
                const ext_type _dimensions;
                const strd_type _strides;
        };

        template <typename T, size_t N>
        class tensor_slice {
            public:
                using extent_type       = tensor_extent<N>;
                using slice_type        = std::gslice_array<T>;

                static constexpr auto rank = extent_type::rank;

                tensor_slice(slice_type s, extent_type e)
                :   _slice(s),
                    _extent(e) {};

                template <typename, size_t>
                friend class tensor;

                decltype(auto) operator =(auto&& arg) {
                    std::cout << "ree\n";
                    return _slice.operator=(std::forward<decltype(arg)>(arg));
                };

                #define ML_TENSOR_DEFINE_MEMBER_OPERATOR(op) template <typename... Args> void operator op(Args&&... args) const { _slice.operator op(std::forward<Args&&>(args)...); }
                    FOR_EACH(ML_TENSOR_DEFINE_MEMBER_OPERATOR, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=);
                #undef ML_TENSOR_DEFINE_MEMBER_OPERATOR

            private:
                slice_type _slice;
                extent_type _extent;

        };

        template <typename T>
        class tensor_slice<T, 0> {
            public:
                using extent_type       = tensor_extent<0>;
                using value_type        = std::add_lvalue_reference_t<T>;

                static constexpr auto rank = extent_type::rank;

                tensor_slice(value_type& init)
                :   _ref(init) {};

                operator tensor<T, 0>() { return tensor<T, 0>(_ref); };
                operator T&() { return _ref; };

                decltype(auto) operator =(T t) {
                    return _ref = t;
                }

                #define ML_TENSOR_DEFINE_MEMBER_OPERATOR(op) void operator op(T& arg) const { _ref op arg; }
                    FOR_EACH(ML_TENSOR_DEFINE_MEMBER_OPERATOR, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=);
                #undef ML_TENSOR_DEFINE_MEMBER_OPERATOR

            private:
                value_type _ref;
        };

        template <typename T, size_t N> requires valid_valarray<T>
        class tensor {
            public:
                using container_type    = std::valarray<T>;
                using extent_type       = tensor_extent<N>;

                static constexpr auto rank = extent_type::rank;

                tensor(const tensor_slice<T, N>& slice)
                :   _extent(slice._extent),
                    _container(slice._slice) {};

                template <typename... Args> requires std::constructible_from<T, Args...>
                tensor(const std::array<size_t, N> dim, Args&&... args)
                :   tensor(dim, T(std::forward<Args&&>(args)...)) {};

                tensor(const std::array<size_t, N> dim, T init)
                :   _extent(dim),
                    _container(init, _extent.size()) {};

                template <typename... Args, size_t S = meta::count_same<slice_t, Args...>::value> requires std::conjunction<meta::all_either<std::is_same, slice_t, std::is_same, index_t, Args...>, meta::equal<sizeof...(Args), N>>::value
                tensor_slice<T, S> operator ()(Args&&... args) {
                    if constexpr (meta::equal<S, 0>::value)
                        return tensor_slice<T, 0>(_container[_extent.calculate_offset(args...)]);
                    else if constexpr (meta::equal<S, N>::value)
                        return tensor_slice<T, N>(_container[std::gslice(0, utils::to_valarray(_extent.dimensions()), utils::to_valarray(_extent.strides()))], _extent);
                    else {
                        return tensor_slice<T, S>();
                    }
                };

                decltype(auto) begin() { return std::begin(_container); };
                decltype(auto)   end() { return std::  end(_container); };

            private:
                extent_type _extent;
                container_type _container;

        };

        template <typename T> requires valid_valarray<T>
        class tensor<T, 0> {
            public:
                using extent_type       = tensor_extent<0>;
                using value_type        = T;

                static constexpr auto rank = extent_type::rank;

                tensor(value_type init)
                :   _value(init) {};

                operator value_type() { return _value; };

                constexpr size_t size() const { return 1; };
                value_type& value() { return _value; };

            private:
                value_type _value = utils::default_value<value_type>::value;
        };
    };
};
