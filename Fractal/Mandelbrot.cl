__kernel void Kernel(int width, int height, __global double* matriX, __global double* matriY, __global int* colors) {
    //int gid = get_global_id(0);

    int row = get_global_id(0);
    int col = get_global_id(1);

    int index = row * height + col;

    double x = matriX[index];
    double y = matriY[index];

    double real = x;
    double imag = y;

    int iterations = 0;
    while (iterations < 200 && real * real + imag * imag < 4)
    {
        double real_new = real * real - imag * imag + x;
        double imag_new = 2 * real * imag + y;

        real = real_new;
        imag = imag_new;

        iterations++;
    }

    if (iterations == 200) {
        iterations = 0;
    }

    colors[index] = iterations;
	
}