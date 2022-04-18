#include <cstdint>
#include <string>
#include <initializer_list>

#include "types.h"
#include "actfunc.h"
#include "network.h"


using namespace ml::internal::types;

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

        class mlp_impl : public base_impl<vector, vector> {
            public:
                mlp_impl();
                ~mlp_impl() = default;

                flt propagate_values(const input_type&, output_type&) final;
                int calculate_update(const input_type&, output_type&) final;
                int execute_update() final;

                int load_parameters(const std::string) final;
                int save_parameters(const std::string) const final;

        };


        /*
         *  using type aliases
         */

        using mlp = base_type<mlp_impl>;

    };


    /*
     *  export detail symbols to outer namespace
     */

    using detail::mlp;

}
