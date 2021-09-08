#pragma once

#include <cstdlib>
#include <cstdbool>
#include <vector>

#include "typedefs.h"
#include "actfunc.h"
#include "lossfunc.h"
#include "params.h"

/* 
 * Network abstract class that will be inherited by all the network objects
 * 
 * defines pure virtual access functions, and a protected member to say whether it has been initialised
 * must also have a parameter object, currently a void pointer to a structure 
 * 
 * TODO: change void pointer to an inheritance and struct-based parameter class, so that it is cmore cpp like and less ANSI C...
 */

template <typename inType, typename outType>
class Network {
    public:

        /*
         *  default destructor to complete subclasses' vtables
         *  set to default as there is nothing to deinit
         */

        virtual ~Network() {};


        /* 
         *  Pure virtual functions, that are common to all neural network classes
         *  regressing and predicting from data
         *      > regression returns cumulative error after training
         *      > predicting will return an error code, usually 0 for success
         */

        virtual float regress(const std::vector<inType> &data, const std::vector<outType> &target, metadata_t params) = 0;
        virtual int32_t predict(const std::vector<inType> &data, std::vector<outType> &output) = 0;


        /* 
         *  Pure virtual functions that all the neural networks should have implemented
         *  enables later saving and loading from drive
         */
        
        virtual int32_t load(const std::string src) = 0;
        virtual int32_t save(const std::string src) = 0;

    protected:
        /* variable to tell whether it has been initialised */
        bool initialised = false;
};
