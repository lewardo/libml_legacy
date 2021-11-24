#include <cstdio>

#include "libml.h"

int32_t main(int32_t argc, const char * argv[]) {
    printf("%f\n", lossfunc::accumulate({ 0, 0, 0.5, 1 }, { 1, 0, 1, 1 }, lossfunc::MeanSquared.f_x));
 
    return 0;
}
