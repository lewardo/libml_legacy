#pragma once

#include <fstream>
#include <typeinfo>

#include "types.h"
#include "algeb.h"

namespace ml::internal {
    using namespace types;
    
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
}