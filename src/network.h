#pragma once

#include <cstdlib>
#include <cstdbool>
#include <vector>

#include "neural.h"
#include "actfunc.h"
#include "lossfunc.h"
#include "params.h"

/* 
 * Network abstract class that will be inherited by all the network objects
 * 
 * defines pure virtual access functions, and a protected member to say whether it has been initialised
 * 
 */

template <typename inType, typename outType>
class Neural::Net {
    public:

        /*
         *  default destructor to complete subclasses' vtables
         *  set to default as there is nothing to deinit
         */

        virtual ~Net() {};


        /* 
         *  Pure virtual functions, that are common to all neural network classes
         *  regressing and predicting from data
         *      > regression returns cumulative error after training
         *      > predicting will return an error code, usually 0 for success and >0 for an error
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
