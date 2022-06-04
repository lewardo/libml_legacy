#pragma once

#include <concepts>
#include <type_traits>

namespace ml::internal::meta {
    template <size_t... Ns>
    struct sequence {};

    namespace detail {
        template <typename T, typename U>
        static constexpr auto are_same = 0;

        template <typename T>
        static constexpr auto are_same<T, T> = 1;


        template <size_t N, size_t V, size_t... Is>
        constexpr auto make_repeat_sequence_impl() {
            if constexpr (N == 0) return sequence<Is...>();
            else return make_repeat_sequence_impl<N-1, V, V, Is...>();
        };

        template <size_t H, size_t L, size_t... Is>
        constexpr auto make_range_sequence_impl() {
            if constexpr (H == L) return sequence<Is...>();
            else return make_range_sequence_impl<H-1, L, H-1, Is...>();
        };
    };

    template <size_t A, size_t B>
    struct equal {
        static constexpr auto value = A == B;
    };

    template <size_t A, size_t B>
    struct greater {
        static constexpr auto value = A > B;
    };

    template <template <typename, typename> class P, typename T, typename... Ts>
    using all_satisfy = std::conjunction<P<T, Ts>...>;

    template <template <typename, typename> class Pa, typename Ta, template <typename, typename> class Pb, typename Tb, typename... Ts>
    using all_either = std::conjunction<std::disjunction<Pa<Ta, Ts>, Pb<Tb, Ts>>...>;

    template <typename T, typename... Ts>
    using all_same = all_satisfy<std::is_same, T, Ts...>;

    template <typename T, typename... Args>
    struct count_same {
        static constexpr auto value = (( detail::are_same<T, Args> + ... ));
    };

    template <size_t N, size_t V>
    using make_repeat_sequence = decltype(detail::make_repeat_sequence_impl<N, V>());

    template <size_t L, size_t H>
    using make_range_sequence = decltype(detail::make_range_sequence_impl<H, L>());
};
