#pragma once

#include <ranges>
#include <concepts>
#include <tuple>
#include <fstream>
#include <typeinfo>

#include "types.h"

namespace ml::utils {
    using namespace ml::types;
    
    template <typename T, typename vT = T::value_type, typename dT = T::difference_type, typename iT = T::const_iterator> requires std::ranges::range<T>
    inline dT iterator_index(vT& element, T& container) {
        return static_cast<dT>( static_cast<iT>(&element) - container.begin() );
    };
    
    template <typename T>
    struct default_value {
        static constexpr typename std::decay_t<T> value = std::decay_t<T>{};
    };
    
    class reader {
        public:
            reader& operator>>(vector&) const;
            reader& operator>>(matrix&) const;
            
            std::type_info& typeof_next() const;
            
        private:
            std::ifstream _ifs;
    };
    
    class writer {
        public:
            writer& operator<<(const vector&) const;
            writer& operator<<(const matrix&) const;
                        
        private:
            std::ofstream _ofs;
    };
};
