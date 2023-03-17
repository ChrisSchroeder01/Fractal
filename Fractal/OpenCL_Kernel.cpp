#include "OpenCL_Kernel.h"

OpenCL_Kernel::OpenCL_Kernel()
{

    // Read the kernel source from a file
    std::ifstream file("Mandelbrot.cl");
    std::string kernel_source(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));

    // Get available OpenCL platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // List Platforms
    std::cout << "Number of OpenCL platforms: " << platforms.size() << std::endl;

    for (int i = 0; i < platforms.size(); ++i) {
        std::cout << "\tPlatform " << i << ": " << platforms[i].getInfo<CL_PLATFORM_NAME>() << std::endl;
    }

    // Get the first available OpenCL device
    std::vector<cl::Device> devices;
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);
    cl::Device device = devices[0];

    std::cout << std::endl;
    std::cout << "Selected Platform 0" << std::endl;
    std::cout << std::endl;

    // List Devices
    std::cout << "Number of Devices on Platform 0: " << devices.size() << std::endl;
    for (int i = 0; i < devices.size(); ++i) {
        std::cout << "\tDevice " << i << ": " << devices[i].getInfo<CL_DEVICE_NAME>() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "You are Using: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;

    cl_device_type type = device.getInfo<CL_DEVICE_TYPE>();

    switch (type) {
    case CL_DEVICE_TYPE_CPU:
        std::cout << "\tDevice type: CPU" << std::endl;
        break;
    case CL_DEVICE_TYPE_GPU:
        std::cout << "\tDevice type: GPU" << std::endl;
        break;
    case CL_DEVICE_TYPE_ACCELERATOR:
        std::cout << "\tDevice type: Accelerator" << std::endl;
        break;
    default:
        std::cout << "\tDevice type: Unknown" << std::endl;
        break;
    }

    std::cout << std::endl;

    // Create a context and command queue for the device

    this->context = cl::Context({ device });
    this->queue = cl::CommandQueue({ this->context, device });


    // Create an OpenCL program from the kernel source
    cl::Program::Sources sources(1, std::make_pair(kernel_source.c_str(), kernel_source.length()));
    cl::Program program(context, sources);

    // Build the program for the device
    program.build({ device });

    // Create an OpenCL kernel from the program
    this->kernel = cl::Kernel(program, "Kernel");

}

void OpenCL_Kernel::Kernel(double* matriX, double* matriY, int width, int height, int** colors)
{

    cl::Buffer buffer_matriX(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double) * width * height, matriX);
    cl::Buffer buffer_matriY(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double) * width * height, matriY);
    cl::Buffer buffer_colors(context, CL_MEM_WRITE_ONLY, sizeof(int) * width * height);

    kernel.setArg(2, buffer_matriX);
    kernel.setArg(3, buffer_matriY);
    kernel.setArg(4, buffer_colors);

    kernel.setArg(0, width);
    kernel.setArg(1, height);
    

    // Define the global and local work sizes
    cl::NDRange globalSize(width,height);
    cl::NDRange localSize(1);

    // Enqueue the kernel to the command queue
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, globalSize, cl::NullRange);

    // Wait for the kernel to finish executing
    queue.finish();

    // Read Output Buffer
    int* output_arr = new int[width * height];
    queue.enqueueReadBuffer(buffer_colors, CL_TRUE, 0, sizeof(int) * width * height, output_arr);

    for (int i = 0; i < width*height; i++)
    {
        int x = i % width;
        int y = i / width;
        colors[y][x] = output_arr[i];
    }

    delete output_arr;
}
