#pragma once

#include <ranges>
#include <algorithm>
#include <concepts>
#include <array>
#include <functional>
#include <tuple>
#include <fstream>
#include <typeinfo>

#include "types.h"
#include "meta.h"


#define ifnt(condition) if(!( condition ))


/*
 *  namespace utils
 */

namespace ml::internal::utils {

    /*
     *  detail namespace as to not import other namespaces to `namespace utils` directly
     */

    namespace detail {

        /*
         *  using declarations
         */

        using namespace types;


        /*
         *  get index of element from iterator and container; ie a generalised version of a[x] - a[0] -> x
         */

        template <typename T, typename vT = typename T::value_type, typename dT = typename T::difference_type, typename iT = typename T::const_iterator> requires std::ranges::range<T>
        inline dT iterator_index(vT& element, T& container) {
            return static_cast<dT>( std::distance(container.cbegin(), iT{&element}) );
        };


        /*
         *  use decay type to find the default value of any type, eg default_value<int>::value = 0, and stl-esque helper using declaration
         */

        template <typename T>
        struct default_value {
            static constexpr typename std::decay_t<T> value = std::decay_t<T> {};
        };

        template <typename T>
        using default_value_v = default_value<T>::value;


        /*
         *  function to return resized verions of a std::array, truncates if shorter and pads with T{}
         */

        // template<size_t Nt, size_t Ns, typename T, size_t... I> requires meta::equal<Nt, sizeof...(I)>::value
        // std::array<T, Nt> from_elements_impl(std::array<T, Ns> from, std::index_sequence<I...>) {
        //     return { from[I]... };
        // };

        template <size_t Nt, size_t Ns, typename T> requires std::is_default_constructible_v<T>
        constexpr std::array<T, Nt> resize_array(const std::array<T, Ns>& from) {
            return [&] <size_t... Is> (const std::array<T, Ns>& arr, std::index_sequence<Is...>) -> std::array<T, Nt> {
                return { arr[Is]... };
            } (from, std::make_index_sequence<std::min(Nt, Ns)>{});
        };

        template <size_t Lo, size_t Hi, size_t Ns, typename T, size_t Nt = Hi-Lo>
        constexpr auto sub_array(const std::array<T, Ns>& from) {
            return [&] <size_t... Is> (const std::array<T, Ns>& arr, meta::sequence<Is...>) -> std::array<T, Nt> {
                return { arr[Is]... };
            } (from, meta::make_range_sequence<Lo, Hi>{});
        };

        template <size_t N, typename T>
        std::array<T, N+1> append_array(const std::array<T, N>& from, const T& val) {
            std::array<T, N+1> tmp = resize_array<N+1>(from);
            return (tmp[N] = val, tmp);
        };

        template <size_t N, typename T>
        std::valarray<T> to_valarray(const std::array<T, N>& from) {
            return [&] <size_t... Is> (const std::array<T, N>& arr, meta::sequence<Is...>) -> std::valarray<T> {
                return { arr[Is]... };
            } (from, meta::make_range_sequence<0, N>{});
        }
    };


    /*
     *  export detail symbols to outer namespace
     */

    using detail::iterator_index;
    using detail::default_value, detail::default_value_v;
    using detail::resize_array, detail::sub_array, detail::append_array, detail::to_valarray;

};
