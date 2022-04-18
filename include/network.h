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
         *  implementation abstract class that defines the ABI for network implementation classes, or can just use a free class that adheres to `concept generic_impl`
         */

        template <typename iT, typename oT>
        class base_impl {
            public:
                
                /*
                 *  pubilc using type alias
                 */
                 
                using input_type = iT;
                using output_type = oT;
                

                /*
                 *  virtual destructor to allow stack delete of descendants
                 */
                 
                virtual ~base_impl() = default;
                
                
                /*
                 *  network functions
                 */
                
                virtual flt propagate_values(const input_type&, output_type&) = 0;
                virtual int calculate_update(const input_type&, output_type&) = 0;
                virtual int execute_update() = 0;
                
                
                /*
                 *  network saving and loading
                 */
        
                virtual int load_parameters(const std::string) = 0;
                virtual int save_parameters(const std::string) const = 0;
                
                
            protected:
                
                /*
                 *  private global variable that can be used for empty constructor+load process
                 */
                 
                bool _initialised = false;
                
        };
        
        
        /*
         *  concept that checks whether an implementation is compatible
         */
        
        template <class Impl>
        concept generic_impl = std::derived_from<Impl, base_impl<typename Impl::input_type, typename Impl::output_type>> || requires (Impl impl, Impl::input_type iT, Impl::output_type oT, std::string s) {
            
            /*
             *  type requirements
             */
             
            typename Impl::input_type;
            typename Impl::output_type;
            
            
            /*
             *  function requirements
             */
            
            { impl.propagate_values(iT, oT) } -> std::same_as<flt>;
            { impl.calculate_update(iT, oT) } -> std::same_as<int>;
            { impl.execute_update() } -> std::same_as<int>;
            
            { impl.load_parameters(s) } -> std::same_as<int>;
            { impl.save_parameters(s) } -> std::same_as<int>;
            
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
                    : _impl(*new Impl(std::forward<Args>(args)...)) {};
                
                ~base_type() {
                    delete& _impl;
                }


                /*
                 *  Pure virtual functions, that are common to all neural network classes
                 *  regressing and predicting from data
                 *      > regression returns cumulative error after training
                 *      > predicting will return an error code, usually 0 for success and >0 for an error
                 */

                flt propagate_values(const input_type& i, output_type& o) {
                    return _impl.propagate_values(i, o);
                };
                
                int calculate_update(const input_type& i, output_type& o) {
                    return _impl.calculate_update(i, o);
                };
                
                int execute_update() {
                    return _impl.execute_update();
                };


                /*
                 *  Pure virtual functions that all the neural networks should have implemented
                 *  enables later saving and loading from drive
                 */

                int load_parameters(const std::string& s) {
                    return _impl.load_parameters(s);
                };
                
                int save_parameters(const std::string& s) const {
                    return _impl.save_parameters(s);
                };

            private:                
                Impl& _impl;
                
        };
        
        
        /*
         *  function to train network on corpus
         */
        
        template <class Impl> requires generic_impl<Impl>
        flt train(base_type<Impl>&);
        
        
        /*
         *  function to predict with network from corpus
         */
         
        template <class Impl> requires generic_impl<Impl>
        flt predict(base_type<Impl>&);

    }
    
    
    /*
     *  export detail symbols to outer namespace
     */
    
    using detail::train, detail::predict;
    
};


/*
 *  top-level namespace definitions for general use
 *  
 */

namespace ml { 
    
    /*
     *  type alias to use any network type with umbrella term 
     */
     
    template <class Impl>
    using network = networks::detail::base_type<Impl>;
    
};