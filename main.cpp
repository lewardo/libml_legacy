#include <cstdio>
#include <vector>

#include "libml.h"

int32_t main(int32_t argc, const char * argv[]) {
    mlpNet * mlp = new mlpNet({ 2, 3, 1 }, actfunc::tanh);

    return 0;
}