#pragma once

#include <ranges>
#include <concepts>
#include <tuple>
#include <fstream>
#include <typeinfo>

#include "types.h"


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
         *  get index of element from iterator and container; ie overcomplicated version of a[x] - a[0] -> x
         */
        
        template <typename T, typename vT = T::value_type, typename dT = T::difference_type, typename iT = T::const_iterator> requires std::ranges::range<T>
        inline dT iterator_index(vT& element, T& container) {
            return static_cast<dT>( static_cast<iT>(&element) - container.begin() );
        };
        
        
        /*
         *  use decay type to find the default value of any type, eg default_value<int>::value = 0 on most compilers
         */
        
        template <typename T>
        struct default_value {
            static constexpr typename std::decay_t<T> value = std::decay_t<T> {};
        };
        
    };
    

    /*
     *  export detail symbols to outer namespace
     */
    
    using detail::iterator_index;
    using detail::default_value;
    
};
