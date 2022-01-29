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

class Neural::mlp :public Neural::net<vf32, vf32> {
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

        f32 regress(const mf32 &data, const mf32 &target, metadata_t params) override;
        i32 predict(const mf32 &data, mf32 &output) override;


        /* 
         *  pure virtual Network function declarations, for loading and saving topology/wandb to external disk 
         */ 

        i32 load(const std::string src) override;
        i32 save(const std::string src) override;


        /* 
         * vector-like implementation of mlp, wherein a layer can be inserted after the rest or removed 
         * used for construction of structure as changing topology screws with parameters previously trained 
         */

        i32 push_back(u32 n, actfunc::type af);
        i32 pop_back();
        i32 insert(u32 idx, u32 n, actfunc::type af);
        i32 erase(u32 idx);
    
    private:

         /*  
          *  Biases object to contain a vector of biases specific to a layer, as a wrapper to a vector of floats
          *  used only locally within scope of mlp object therefore defined inside it as private
          */ 

        struct __attribute__((packed)) biases {
            vf32 b;

            biases(size_t n) :b(n, 0.0f) {
                std::generate(b.begin(), b.end(), []() {
                    return utils::random();
                });
            };

            f32 operator [](u32 &idx) {
                return b[idx];
            }
        };


        /*  
         *  Weights object to contain a matrix of weights specific to a pair of layers, as a wrapper to a matrix of floats
         *  used only locally within scope of mlp object therefore defined inside it as private
         */ 

        struct __attribute__((packed)) weights {
            mf32 w;

            weights(size_t x, size_t y) : w(x, vf32(y, 0.0f)) {
                for(size_t n = 0; n < x; ++n) {
                    std::generate(w[n].begin(), w[n].end(), []() {
                        return utils::random();
                    });
                }
            }

            vf32 operator [](uint32_t &idx) {
                return w[idx];
            }
        };


        /*  
         *  Neuron object with value and error variables
         *  used only locally within scope of mlp object therefore defined inside it as private
         */ 

        struct __attribute__((packed)) neurons {
            vf32 x, e;

            neurons(size_t n) : x(n, 0.0f), e(n, 0.0f) {
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

        struct layer {
            size_t size;
            neurons neurons;
            biases biases;
            actfunc::type activation;

            layer(size_t n, actfunc::type af) 
               :size(n), 
                neurons(n), 
                biases(n), 
                activation(af) {
                // all already initialised
            };

            f32 propagate(layer &next, weights &weights);
            f32 backtrack(layer &prev, weights &weights);
        };


        /*
         *  Vector of layers to define the mlp, all functions act ont his private object
         *  used only locally within scope of mlp object therefore defined inside it as private
         */

        std::vector<layer> _layers; 
        std::vector<weights> _weights;

    // mlp object
};