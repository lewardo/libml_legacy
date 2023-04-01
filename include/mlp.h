#include <cstdint>
#include <string>
#include <initializer_list>

#include "types.h"
#include "actfunc.h"
#include "network.h"


namespace ml::networks {

    /*
     *  detail namespace as to not import other namespaces to `namespace network` directly
     */

    namespace detail {

        /*
         *  using declarations
         */

        using namespace internal::types;


        /*
         *  internal implementation of mlp
         */

        class mlp_impl {
            public:
                using input_type = vector;
                using output_type = vector;

                mlp_impl();
                ~mlp_impl() = default;

                float_type propagate_values(const input_type&, output_type&);
                int calculate_update(const input_type&, output_type&);
                int execute_update();

                int load_parameters(const std::string);
                int save_parameters(const std::string) const;
            
            private:

                bool _initialised = false;

        };


        /*
         *  using type aliases
         */

        using mlp = network<mlp_impl>;

    };


    /*
     *  export detail symbols to outer namespace
     */

    using detail::mlp;

}
