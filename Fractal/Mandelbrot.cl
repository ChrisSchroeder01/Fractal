#pragma OPENCL EXTENSION cl_amd_printf : enable

__kernel void mandelbrot(__global const double2* input, __global int width, __global int height, __global int* output, const int max_iterations)
{
    int gid_x = get_global_id(0);
    int gid_y = get_global_id(1);

    double2 c = input[gid_y * get_global_size(0) + gid_x];
    double2 z = (double2)(0.0, 0.0);
    
    printf("hello world");

    int iterations;
    for (iterations = 0; iterations < max_iterations && length(z) < 2.0; iterations++) {
        z = z * z + c;
    }

    output[gid_y * get_global_size(0) + gid_x] = 1;
}