#pragma once

#include <cstdlib>
#include <cstdio>
#include <vector>

#include "neural.h"
#include "network.h"
#include "actfunc.h"
#include "lossfunc.h"
#include "params.h"
#include "utils.h"

class Neural::mlp : public Neural::Net<vfloat, vfloat> {
    public:

        /*
         *  Constructor with the mlp parameter object and optionally with the variables as arguments
         */

        mlp(std::vector<size_t> npl, actfunc::type af);
        mlp(mlp_param_t params);

        ~mlp() = default;


        /* 
         *  Pure virtual Network function declarations, for forward and backward propagations respectively
         *  TODO: integrate Corpus object to facilitate importing data from files and such
         */

        float regress(const mfloat &data, const mfloat &target, metadata_t params) override;
        int32_t predict(const mfloat &data, mfloat &output) override;


        /* 
         *  pure virtual Network function declarations, for loading and saving topology/wandb to external disk 
         */ 

        int32_t load(const std::string src) override;
        int32_t save(const std::string src) override;


        /* 
         * vector-like implementation of mlp, wherein a layer can be inserted after the rest or removed 
         * used for construction of structure as changing topology screws with parameters previously trained 
         */

        int32_t push_back(uint32_t n, actfunc::type af);
        int32_t pop_back();
        int32_t insert(uint32_t idx, uint32_t n, actfunc::type af);
        int32_t erase(uint32_t idx);
    
    private:

         /*  
          *  Biases object to contain a vector of biases specific to a layer, as a wrapper to a vector of floats
          *  used only locally within scope of mlp object therefore defined inside it as private
          */ 

        struct __attribute__((packed)) Biases {
            vfloat b;

            Biases(size_t n) :b(n, 0.0f) {
                std::generate(b.begin(), b.end(), []() {
                    return utils::random();
                });
            };

            float operator [](uint32_t &idx) {
                return b[idx];
            }
        };


        /*  
         *  Weights object to contain a matrix of weights specific to a pair of layers, as a wrapper to a matrix of floats
         *  used only locally within scope of mlp object therefore defined inside it as private
         */ 

        struct __attribute__((packed)) Weights {
            mfloat w;

            Weights(size_t x, size_t y) : w(x, vfloat(y, 0.0f)) {
                for(size_t n = 0; n < x; ++n) {
                    std::generate(w[n].begin(), w[n].end(), []() {
                        return utils::random();
                    });
                }
            }

            vfloat operator [](uint32_t &idx) {
                return w[idx];
            }
        };


        /*  
         *  Neuron object with value and error variables
         *  used only locally within scope of mlp object therefore defined inside it as private
         */ 

        struct __attribute__((packed)) Neurons {
            vfloat x, e;

            Neurons(size_t n) : x(n, 0.0f), e(n, 0.0f) {
                std::generate(x.begin(), x.end(), []() {
                    return utils::random();
                });

                std::generate(e.begin(), e.end(), []() {
                    return utils::random();
                });
            }
        };


        /*  
         *  Layer object used as wrapper for neuron object, to perform layer-wise backpropagation and forward-propagation
         *  used only locally within scope of mlp object therefore defined inside it as private
         */ 

        struct Layer {
            size_t size;
            Neurons neurons;
            Biases biases;
            actfunc::type activation;

            Layer(size_t n, actfunc::type af) 
               :size(n), 
                neurons(n), 
                biases(n), 
                activation(af) {
                // all already initialised
            };

            float propagate(Layer &next, Weights &weights);
            float backtrack(Layer &prev, Weights &weights);
        };


        /*
         *  Vector of layers to define the mlp, all functions act ont his private object
         *  used only locally within scope of mlp object therefore defined inside it as private
         */

        std::vector<Layer> layers; 
        std::vector<Weights> weights;

    // mlpNet object
};