#include <cstdint>
#include <string>
#include <initializer_list>

#include "types.h"
#include "actfunc.h"
#include "network.h"


using namespace ml::internal::types;

namespace ml::networks {
    
    namespace detail {
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
        
        using mlp = base_type<mlp_impl>;
    };

    /*
     *  mlp object
     */

    using detail::mlp;
    
}