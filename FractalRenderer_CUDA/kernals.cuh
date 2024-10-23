#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cuComplex.h>

__global__ void mandlebrot(size_t w, size_t h, size_t it, double x_min, double y_min, double x_scale, double y_scale, double* data);