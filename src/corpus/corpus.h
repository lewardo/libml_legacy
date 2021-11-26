#pragma once

#include <cstdbool>
#include <vector>
#include <initializer_list>
#include <variant>

namespace Corpus {
    using vfloat = std::vector<float>;
    using mfloat = std::vector<vfloat>;

    using variant = std::variant<vfloat, mfloat>;

    class Base {
        public:
            virtual ~Base() = default;

            virtual variant operator [](const int& idx) = 0;

        protected:
            Base(std::string, bool);
            Base(std::initializer_list<variant>, bool);

            std::vector<variant> data;
    };

    namespace Unicor {
        class type : public Base {
            public:
                type(std::string);
                type(std::initializer_list<variant>);

                variant operator [](const int&) override;
        };
    };

    namespace Bicor {
        class type : public Base {
            public:
                type(std::string);
                type(std::initializer_list<variant>);

                variant operator [](const int&) override;
        };
    };
}
