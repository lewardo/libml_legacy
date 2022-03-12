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

template <typename it, typename ot>
class ml::net::network {
    public:

        /*
         *  default destructor to complete subclasses' vtables
         *  set to default as there is nothing to deinit
         */

        virtual ~network() = default;


        /*
         *  Pure virtual functions, that are common to all neural network classes
         *  regressing and predicting from data
         *      > regression returns cumulative error after training
         *      > predicting will return an error code, usually 0 for success and >0 for an error
         */

        virtual flt propagate(const std::vector<it> &data, const std::vector<ot> &target, metadata_t params) = 0;
        virtual int calculate(const std::vector<it> &data, std::vector<ot> &output) = 0;
        virtual int update(metadata_t params) = 0;


        /*
         *  Pure virtual functions that all the neural networks should have implemented
         *  enables later saving and loading from drive
         */

        virtual int load(const std::string src) = 0;
        virtual int save(const std::string src) = 0;

    protected:
        /* variable to tell whether it has been initialised */
        bool initialised = false;
};
