#pragma once

#include <vector>
#include <string>

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
         * Network abstract class that will be inherited by all the network objects
         *
         * defines pure virtual access functions, and a protected member to say whether it has been initialised
         *
         */

        template <typename iT, typename oT>
        class base_type {
            public:

                /*
                 *  default destructor to complete subclasses' vtables
                 *  set to default as there is nothing to deinit
                 */

                virtual ~base_type() = default;


                /*
                 *  Pure virtual functions, that are common to all neural network classes
                 *  regressing and predicting from data
                 *      > regression returns cumulative error after training
                 *      > predicting will return an error code, usually 0 for success and >0 for an error
                 */

                virtual flt propagate(const std::vector<iT>&, const std::vector<oT>&) = 0;
                virtual int calculate(const std::vector<iT>&, std::vector<oT>&) = 0;
                virtual int update() = 0;


                /*
                 *  Pure virtual functions that all the neural networks should have implemented
                 *  enables later saving and loading from drive
                 */

                virtual int load(const std::string) = 0;
                virtual int save(const std::string) = 0;

            protected:
                
                /* 
                 *  variable to tell whether it has been initialised 
                 */
                 
                bool _initialised = false;
                
        };
        
        
        /*
         *  function to train network on corpus
         */
        
        template <typename iT, typename oT>
        flt train(base_type<iT, oT>&);
        
        
        /*
         *  function to predict with network from corpus
         */
         
        template <typename iT, typename oT>    
        flt predict(base_type<iT, oT>&);
        
        
        /*
         *  function to train network on corpus
         */
        
        class mlp;

    }
    
    
    /*
     *  export detail symbols to outer namespace
     */
    
    using detail::base_type, detail::mlp;
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
     
    template <typename iT, typename oT>
    using network = networks::base_type<iT, oT>;
    
};