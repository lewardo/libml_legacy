#include <cstdlib>
#include <cstdio>
#include <vector>

#include "neural.h"
#include "network.h"
#include "actfunc.h"
#include "lossfunc.h"

#include "mlp.h"


Neural::mlp::mlp(std::vector<size_t> npl, actfunc::type af) : Net() {
    size_t size = npl.size();

    for(size_t n = 0; n < size; ++n) {
        Layer next = Layer(npl[n], af);

        layers.push_back(next);
    }

    initialised = true;
};

Neural::mlp::mlp(mlp_param_t params): mlp(params.npl, params.af)  {
    // already initialised
};

float Neural::mlp::regress(const mfloat &data, const mfloat &target, metadata_t params) {
    return utils::random();
};

int32_t Neural::mlp::predict(const mfloat &data, mfloat &output) {
    return 0;
};

int32_t Neural::mlp::load(const std::string src) {
    return 0;
};

int32_t Neural::mlp::save(const std::string src) {
    return 0;
};

int32_t Neural::mlp::push_back(uint32_t n, actfunc::type af) {
    return 0;
};

int32_t Neural::mlp::pop_back() {
    return 0;
};

int32_t Neural::mlp::insert(uint32_t idx, uint32_t n, actfunc::type af) {
    return 0;
};

int32_t Neural::mlp::erase(uint32_t idx) {
    return 0;
};   

float Neural::mlp::Layer::backtrack(Layer &prev, Weights &weights) {
    return 0;
};

float Neural::mlp::Layer::propagate(Layer &next, Weights &weights) {
    return 0;
};