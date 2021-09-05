#include <cstdlib>
#include <cstdio>
#include <vector>

#include "network.h"
#include "typedefs.h"
#include "actfunc.h"
#include "lossfunc.h"

#include "mlp.h"


mlpNet::mlpNet(std::vector<size_t> npl, actfunc_t af) : Network() {
    size_t size = npl.size();

    for(size_t n = 0; n < size; ++n) {
        Layer next = Layer(npl[n], af);

        layers.push_back(next);
    }

    initialised = true;
};

mlpNet::mlpNet(mlp_param_t params): mlpNet(params.npl, params.af)  {
    // already initialised
};

mlpNet::~mlpNet() {
    
}

float mlpNet::regress(const mfloat &data, const mfloat &target, metadata_t params) {
    return utils::random();
};

int32_t mlpNet::predict(const mfloat &data, mfloat &output) {
    return 0;
};

int32_t mlpNet::load(const std::string src) {
    return 0;
};

int32_t mlpNet::save(const std::string src) {
    return 0;
};

int32_t mlpNet::push_back(uint32_t n, actfunc_t af) {
    return 0;
};

int32_t mlpNet::pop_back() {
    return 0;
};

int32_t mlpNet::insert(uint32_t idx, uint32_t n, actfunc_t af) {
    return 0;
};

int32_t mlpNet::erase(uint32_t idx) {
    return 0;
};   

float mlpNet::Layer::backtrack(Layer &prev, Weights &weights) {
    return 0;
};

float mlpNet::Layer::propagate(Layer &next, Weights &weights) {
    return 0;
};