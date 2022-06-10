#pragma once

#include <concepts>
#include <type_traits>

namespace ml::internal::meta {
    template <size_t... Is>
    struct sequence {};

    namespace detail {
        template <size_t N, size_t... Is>
        constexpr auto make_index_sequence_impl() {
            if constexpr (N == 0) return sequence<Is...>{};
            else return make_index_sequence_impl<N-1, N-1, Is...>();
        }

        template <size_t N, size_t V, size_t... Is>
        constexpr auto make_repeat_sequence_impl() {
            if constexpr (N == 0) return sequence<Is...>{};
            else return make_repeat_sequence_impl<N-1, V, V, Is...>();
        };

        template <size_t H, size_t L, size_t... Is>
        constexpr auto make_range_sequence_impl() {
            if constexpr (H == L) return sequence<Is...>{};
            else return make_range_sequence_impl<H-1, L, H-1, Is...>();
        };

        template <size_t S, size_t N, template <typename, typename> class P, typename T, typename Ta, typename... Ts, size_t... Is>
        constexpr auto make_satisfy_sequence_impl(sequence<Is...>) {
            if constexpr (P<T, Ta>::value) {
                if constexpr (N == 0) return sequence<Is..., S-(N+1)>{};
                else return make_satisfy_sequence_impl<S, N-1, P, T, Ts...>(sequence<Is..., S-(N+1)>{});
            } else {
                if constexpr (N == 0) return sequence<Is...>{};
                else return make_satisfy_sequence_impl<S, N-1, P, T, Ts...>(sequence<Is...>{});
            }
        }
    };

    template <size_t N, typename... Args>
    constexpr auto count_equals = sizeof...(Args) == N;

    template <template <typename, typename> class P, typename T, typename... Ts>
    using all_satisfy = std::conjunction<P<T, Ts>...>;

    template <template <typename, typename> class Pa, typename Ta, template <typename, typename> class Pb, typename Tb, typename... Ts>
    using all_either = std::conjunction<std::disjunction<Pa<Ta, Ts>, Pb<Tb, Ts>>...>;

    template <typename T, typename... Ts>
    using all_same = all_satisfy<std::is_same, T, Ts...>;

    template <typename T, typename... Args>
    constexpr auto count_same = ( ... + (std::same_as<T, Args> ? 1 : 0) );

    template <size_t N>
    using make_index_sequence = decltype(detail::make_index_sequence_impl<N>());

    template <size_t N>
    constexpr auto index_sequence = make_index_sequence<N>{};

    template <size_t N, size_t V>
    using make_repeat_sequence = decltype(detail::make_repeat_sequence_impl<N, V>());

    template <size_t N, size_t V>
    constexpr auto repeat_sequence = make_repeat_sequence<N, V>{};

    template <size_t L, size_t H>
    using make_range_sequence = decltype(detail::make_range_sequence_impl<H, L>());

    template <size_t N, size_t V>
    constexpr auto range_sequence = make_range_sequence<N, V>{};

    template <template <typename, typename> class P, typename T, typename... Ts>
    using make_satisfy_sequence = decltype(detail::make_satisfy_sequence_impl<sizeof...(Ts), sizeof...(Ts)-1, P, T, Ts...>(sequence {}));

    template <template <typename, typename> class P, typename T, typename... Ts>
    constexpr auto satisfy_sequence = make_satisfy_sequence<P, T, Ts...>{};
};
