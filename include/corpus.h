#pragma once

#include <cstddef>
#include <concepts>
#include <string>

#include "types.h"

namespace ml::corpora {

    /*
     *  detail namespace as to not import other namespaces to `namespace network` directly
     */

    namespace detail {

        /*
         *  using declarations
         */

        using namespace internal;
        using namespace internal::types;


        /*
         *  implementation abstract class that defines the ABI for corpus implementation classes, or can just use a free class that adheres to `concept generic_impl`
         */

        template <typename iT, typename oT>
        class base_impl {
            public:

                /*
                 *  pubilc using type alias
                 */

                using input_type = iT;
                using output_type = oT;

                using value_type = std::conditional<std::same_as<oT, empty_type>, iT, std::pair<iT, oT>>;


                base_impl();

                /*
                 *  virtual destructor to allow stack delete of descendants
                 */

                virtual ~base_impl() = default;


                /*
                 *  access function
                 */

                 virtual size_t corpus_size() = 0;
                 virtual value_type get_element(int) = 0;


            private:

                /*
                 *  reading wrapper
                 */

                // corpus_reader<value_type>& _r;

        };


        /*
         *  concept that checks whether an implementation is compatible
         */

        template <class Impl>
        concept generic_impl = std::derived_from<Impl, base_impl<typename Impl::input_type, typename Impl::output_type>> || requires (Impl impl, int i) {

            /*
             *  type requirements
             */

            typename Impl::input_type;
            typename Impl::output_type;
            typename Impl::value_type;


            /*
             *  function requirements
             */

            { impl.corpus_size() } -> std::same_as<size_t>;
            { impl.get_element(i) } -> std::same_as<typename Impl::value_type>;

        };


        /*
         * Corpus template class that is specialised by implementatinon reference
         */

        template <class Impl> requires generic_impl<Impl>
        class base_type {
            public:

                /*
                 *  perfect variadic forwarding constructor to initialise impl object rather than this
                 */

                template <typename... Args>
                base_type(Args&&... args)
                    : _impl(*new Impl(std::forward<Args>(args)...)) {};


                /*
                 *  defined destructor no save from memory leak
                 */

                ~base_type() {
                    delete& _impl;
                };


                /*
                 *  forwarding functions to implementation
                 */

                size_t corpus_size() {
                    return _impl.corpus_size();
                };

                typename Impl::value_type operator[](const int& i) {
                    return _impl.get_element(i);
                };

            private:

                /*
                 *  reference to internal implementation
                 */

                Impl& _impl;

        };

        template <typename iT>
        class set_impl : public base_impl<iT, empty_type> {
            public:
                set_impl();
        };

        template <typename iT, typename oT>
        class map_impl : public base_impl<iT, oT> {

        };


        template <typename iT>
        using set = base_type<set_impl<iT>>;

        template <typename iT, typename oT>
        using map = base_type<map_impl<iT, oT>>;
    }


    /*
     *  export detail symbols to outer namespace
     */

    using detail::set, detail::map;

}

namespace ml {

    /*
     *  type alias to use any corpus type with umbrella term
     */

    template <class Impl>
    using corpus = corpora::detail::base_type<Impl>;

};
