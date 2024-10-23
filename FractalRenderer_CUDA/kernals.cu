#include "kernals.cuh"

__global__ void mandlebrot(size_t w, size_t h, size_t it, double x_min, double y_min, double x_scale, double y_scale, double* data) {
	int idx = blockDim.x * blockIdx.x + threadIdx.x;

	size_t y = idx / w;
	size_t x = idx % w;

    if (y < h) {
        double fx = x_min + ((double)x * x_scale);
        double fy = y_min + ((double)y * y_scale);

        cuDoubleComplex c = make_cuDoubleComplex(fx, fy);
        cuDoubleComplex z = make_cuDoubleComplex(0.0, 0.0);

        for (size_t i = 0; i < it; i++) {
            z = cuCfma(z, z, c);

            if (cuCabs(z) > 2.0) {
                data[idx] = 1.0 - (1.0 / (((double)i / 50.00) + 1.0));
                return;
            }
        }

        data[idx] = 1.0;

       /* size_t i = 0;
        for (; i < it; i++) {
            z = cuCfma(z, z, c);

            if (cuCabs(z) > 2.0) {
                break;
            }
        }

        if (i < it) {
            double smooth_color = i + 1.0 - log(log(cuCabs(z))) / log(2.0);
            data[idx] = smooth_color / it;
        }
        else {
            data[idx] = 0.0;
        }*/

    }
}