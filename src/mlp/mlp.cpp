#include <cstdlib>
#include <cstdio>
#include <vector>

#include "neural.h"
#include "network.h"
#include "actfunc.h"
#include "lossfunc.h"

#include "mlp.h"


Neural::mlp::mlp(std::vector<size_t> npl, actfunc::type af) : net() {
    size_t size = npl.size();

    for(size_t n = 0; n < size; ++n) {
        layer next = layer(npl[n], af);

        _layers.push_back(next);
    }

    initialised = true;
};

Neural::mlp::mlp(mlp_param_t params): mlp(params.npl, params.af)  {
    // already initialised
};

f32 Neural::mlp::regress(const mf32 &data, const mf32 &target, metadata_t params) {
    return utils::random();
};

i32 Neural::mlp::predict(const mf32 &data, mf32 &output) {
    return 0;
};

i32 Neural::mlp::load(const std::string src) {
    return 0;
};

i32 Neural::mlp::save(const std::string src) {
    return 0;
};

i32 Neural::mlp::push_back(u32 n, actfunc::type af) {
    return 0;
};

i32 Neural::mlp::pop_back() {
    return 0;
};

i32 Neural::mlp::insert(u32 idx, u32 n, actfunc::type af) {
    return 0;
};

i32 Neural::mlp::erase(u32 idx) {
    return 0;
};   

f32 Neural::mlp::layer::backtrack(layer &prev, weights &weights) {
    return 0;
};

f32 Neural::mlp::layer::propagate(layer &next, weights &weights) {
    return 0;
};