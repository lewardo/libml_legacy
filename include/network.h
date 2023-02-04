#pragma once

#include <vector>
#include <concepts>
#include <string>
#include <memory>

#include "types.h"

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
         *  concept that checks whether an implementation is compatible
         */

        template <class Impl, typename iT = Impl::input_type, typename oT = Impl::output_type>
        concept generic_impl = requires (Impl impl, iT i, oT o, std::string s) {

            /*
             *  type requirements
             */

            typename Impl::input_type;
            typename Impl::output_type;


            /*
             *  function requirements
             */

            impl.propagate_values(i, o);
            impl.calculate_update(i, o);
            impl.execute_update();

            impl.load_parameters(s);
            impl.save_parameters(s);

        };


        /*
         * Network template class that is specialised by implementatinon reference
         */

        template <class Impl> requires generic_impl<Impl>
        class base_type {

            /*
             *  using type alias
             */

            using input_type = Impl::input_type;
            using output_type = Impl::output_type;


            public:

                /*
                 *  perfect variadic forwarding constructor to initialise impl object rather than this
                 */

                template <typename... Args>
                base_type(Args&&... args)
                    : _impl(std::make_unique<Impl>(std::forward<Args>(args)...)) {};


                /*
                 *  forwarding functions to propagation functions
                 */

                float_type propagate_values(const input_type& i, output_type& o) {
                    return _impl->propagate_values(i, o);
                };

                int calculate_update(const input_type& i, output_type& o) {
                    return _impl->calculate_update(i, o);
                };

                int execute_update() {
                    return _impl->execute_update();
                };


                /*
                 *  forwarding functions to parameter functions
                 */

                int load_parameters(const std::string& s) {
                    return _impl->load_parameters(s);
                };

                int save_parameters(const std::string& s) const {
                    return _impl->save_parameters(s);
                };

            private:

                /*
                 *  reference to internal implementation
                 */

                std::unique_ptr<Impl> _impl;

        };


        /*
         *  function to train network on corpus
         */

        template <class Impl> requires generic_impl<Impl>
        float_type train(base_type<Impl>&);


        /*
         *  function to predict with network from corpus
         */

        template <class Impl> requires generic_impl<Impl>
        float_type predict(base_type<Impl>&);

    }


    /*
     *  export detail symbols to outer namespace
     */

    using detail::train, detail::predict;

};


/*
 *  top-level namespace definitions for general use
 */

namespace ml {

    /*
     *  type alias to use any network type with umbrella term
     */

    template <class Impl>
    using network = networks::detail::base_type<Impl>;

};
