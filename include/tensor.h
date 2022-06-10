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
                using extent_type   = std::valarray<size_t>;
                using arg_type      = std::array<size_t, N>;

                static constexpr auto rank = N;

                tensor_extent(arg_type dims)
                :   tensor_extent(dims, tr_dims(dims)) {};

                tensor_extent(arg_type dims, arg_type strd)
                :   tensor_extent(utils::to_valarray(dims), utils::to_valarray(strd)) {};

                tensor_extent(extent_type dims, extent_type strd)
                :   _dimensions(dims),
                    _strides(strd),
                    _size(dims[0] * strd[0]) {};

                size_t dims(size_t i) const { return _dimensions[i]; };
                size_t strd(size_t i) const { return    _strides[i]; };

                const extent_type dimensions() const { return _dimensions; };
                const extent_type    strides() const { return    _strides; };

                size_t size() const { return _size; };

                // please forgive me~
                template <typename... Args> requires meta::all_satisfy<std::is_convertible, size_t, Args...>::value && meta::count_equals<N, Args...>
                decltype(auto) calculate_offset(Args... args) {
                    // compartimentalised and localised version of a deferring function, templated lambda that accetps index sequence and tuple of forwarded arguments, capturing `this` by reference
                    // asserts that all the arguments are in bound then returns elementwise multiplication with strides over summation fold expression
                    // calls lambda while forwarding args as tuple, and with index sequence of length args
                    return [this] <typename... Ts, template <typename...> class Tup, size_t... I> (const Tup<Ts...>& tup, meta::sequence<I...>) {
                        assert("index out of bounds" && (((size_t) std::get<I>(tup) < _dimensions[I]) && ...));
                        return ( ... + (std::get<I>(tup) * _strides[I]) );
                    } (std::forward_as_tuple(args...), meta::index_sequence<N>);
                };

                static constexpr arg_type tr_dims(arg_type dims) {
                    arg_type strd;

                    strd[N-1] = 1;

                    for (size_t n = N-1; n > 0; --n)
                        strd[n-1] = dims[n] * strd[n];

                    return strd;
                };

            private:
                const extent_type _dimensions;
                const extent_type _strides;
                const size_t _size;
        };

        template <typename T, size_t N>
        class tensor_slice {
            public:
                using extent_type       = tensor_extent<N>;
                using slice_type        = std::gslice;
                using container_type    = std::add_lvalue_reference_t<std::valarray<T>>;

                static constexpr auto rank = extent_type::rank;

                template <typename, size_t>
                friend class tensor;

                tensor_slice(container_type c, slice_type s)
                :   _ref(c),
                    _slice(s) {};

                operator tensor<T, N>() const { return tensor<T, N>(this); };
                operator container_type() const { return _ref; };

                #define ML_TENSOR_DEFINE_MEMBER_OPERATOR(op) template <typename... Args> decltype(auto) operator op(Args&&... args) const { return _ref[_slice].operator op(std::forward<Args&&>(args)...); }
                    FOR_EACH(ML_TENSOR_DEFINE_MEMBER_OPERATOR, =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=);
                #undef  ML_TENSOR_DEFINE_MEMBER_OPERATOR

            private:
                const container_type _ref;
                const slice_type _slice;

        };

        template <typename T>
        class tensor_slice<T, 0> {
            public:
                using extent_type       = tensor_extent<0>;
                using container_type    = std::add_lvalue_reference_t<T>;

                static constexpr auto rank = extent_type::rank;

                tensor_slice(container_type init)
                :   _ref(init) {};

                operator tensor<T, 0>() const { return tensor<T, 0>(_ref); };
                operator container_type() const { return _ref; };

                #define ML_TENSOR_DEFINE_MEMBER_OPERATOR(op) void operator op(T arg) const { _ref op arg; }
                    FOR_EACH(ML_TENSOR_DEFINE_MEMBER_OPERATOR, =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=);
                #undef ML_TENSOR_DEFINE_MEMBER_OPERATOR

            private:
                const container_type _ref;
        };

        template <typename T, size_t N> requires valid_valarray<T>
        class tensor {
            public:
                using container_type    = std::valarray<T>;
                using extent_type       = tensor_extent<N>;

                static constexpr auto rank = extent_type::rank;

                tensor(const tensor_slice<T, N>& slice)
                :   _extent(slice._slice.size(), slice._slice.stride()),
                    _container(slice._ref[slice._slice]) {};

                template <typename... Args> requires std::constructible_from<T, Args...>
                tensor(const std::array<size_t, N> dim, Args&&... args)
                :   tensor(dim, T(std::forward<Args&&>(args)...)) {};

                tensor(const std::array<size_t, N> dim, T init)
                :   _extent(dim),
                    _container(init, _extent.size()) {};

                operator container_type() { return _container; };

                #define ML_TENSOR_DEFINE_MEMBER_OPERATOR(op) template <typename... Args> decltype(auto) operator op(Args&&... args) { return _container.operator op(std::forward<Args&&>(args)...); }
                #define ML_TENSOR_DEFINE_UNARY_OPERATOR(op) decltype(auto) operator op() { _container.operator op(); }
                    FOR_EACH(ML_TENSOR_DEFINE_MEMBER_OPERATOR, =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=);
                    FOR_EACH(ML_TENSOR_DEFINE_UNARY_OPERATOR, +, -, ~, !);
                #undef  ML_TENSOR_DEFINE_MEMBER_OPERATOR

                template <typename... Args, size_t S = meta::count_same<slice_t, Args...>>
                requires meta::all_either<std::is_same, slice_t, std::is_convertible, index_t, Args...>::value && meta::count_equals<N, Args...>
                tensor_slice<T, S> operator ()(Args&&... args) {
                    if constexpr (S == 0)
                        return tensor_slice<T, 0>(_container[_extent.calculate_offset(args...)]);
                    else {
                        size_t offset = _extent.calculate_offset((size_t) args...);

                        std::valarray<size_t> dims = utils::extract_indicies(_extent.dimensions(), meta::satisfy_sequence<std::is_same, slice_t, Args...>);
                        std::valarray<size_t> strd = utils::extract_indicies(_extent.strides(),    meta::satisfy_sequence<std::is_same, slice_t, Args...>);

                        return tensor_slice<T, S>(_container, std::gslice(offset, dims, strd));
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
                explicit operator value_type&() { return _value; };

                consteval size_t size() const { return 1; };
                value_type& value() { return _value; };

            private:
                value_type _value = utils::default_value<value_type>::value;
        };
    };
};
