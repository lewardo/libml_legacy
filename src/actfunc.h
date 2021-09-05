#pragma once


using actfunc_t = struct {
    float (*f_x)(float), (*df_dx)(float);
};

namespace actfunc {
    extern actfunc_t sigmoid,
                     tanh,
                     ReLU,
                     linear;
};