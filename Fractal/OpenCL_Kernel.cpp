#include "OpenCL_Kernel.h"

OpenCL_Kernel::OpenCL_Kernel()
{
}

void OpenCL_Kernel::Kernel(double*** matrix, int width, int height, int** colors)
{
	std::cout << "i:iiiiiii" << std::endl;


    // Step 1: Get a list of OpenCL platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Step 2: Get the first available GPU device
    cl::Device device;
    for (auto& platform : platforms) {
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
        if (!devices.empty()) {
            device = devices.front();
            break;
        }
    }

    // Step 3: Create an OpenCL context and command queue
    cl::Context context({ device });
    cl::CommandQueue queue(context, device);

    // Step 4: Create an OpenCL program from the kernel source
    std::ifstream file("helloWorld.cl");
    std::string source(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));
    cl::Program::Sources sources(1, std::make_pair(source.c_str(), source.length()));
    cl::Program program(context, sources);
    program.build({ device });

    // Step 5: Create an OpenCL kernel from the program
    cl::Kernel kernel(program, "hello_world");

    // Step 6: Create OpenCL memory buffers for the input and output data
    cl::Buffer input(context, CL_MEM_READ_ONLY, sizeof(double) * width * height * 2);
    cl::Buffer inputx(context, CL_MEM_READ_ONLY, sizeof(double) * width * height);
    cl::Buffer inputy(context, CL_MEM_READ_ONLY, sizeof(double) * width * height);
    cl::Buffer output(context, CL_MEM_WRITE_ONLY, sizeof(int) * width * height);

    // Step 7: Set the kernel arguments
    kernel.setArg(0, input);
    kernel.setArg(1, width);
    kernel.setArg(2, height);
    kernel.setArg(3, output);
    kernel.setArg(4, 200);

    // Step 8: Write the input data to the input buffer
    double* input_data = new double[width * height * 2];
    //double* input_x = new double[width * height];
    //double* input_y = new double[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int i = y * width + x;
            input_data[i * 2] = matrix[y][x][0];
            input_data[i * 2 + 1] = matrix[y][x][1];
            //input_x[i] = matrix[y][x][0];
            //input_y[i] = matrix[y][x][1];
        }
    }
    queue.enqueueWriteBuffer(input, CL_TRUE, 0, sizeof(double) * width * height * 2, input_data);
    //queue.enqueueWriteBuffer(inputx, CL_TRUE, 0, sizeof(double) * width * height, input_x);
    //queue.enqueueWriteBuffer(inputy, CL_TRUE, 0, sizeof(double) * width * height, input_y);

    // Step 9: Enqueue the kernel for execution

    cl::NDRange global(width, height);
    cl::NDRange local(16, 16);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NDRange(1));
    
    queue.finish();

    // Step 10: Read the output buffer
    int* output_data = new int[width * height];
    queue.enqueueReadBuffer(output, CL_TRUE, 0, sizeof(int) * width * height, output_data);

    std::cout << "Kernel executed successfully" << std::endl;
    for (int i = 0; i < width * height; i++)
    {
        std::cout << "i: " << i << " data: " << output_data[i] << std::endl;
    }
}

void OpenCL_Kernel::HelloWorldTest()
{
    // Read the kernel source from a file
    std::ifstream file("helloWorld.cl");
    std::string kernel_source(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));

    // Get available OpenCL platforms
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    // Get the first available OpenCL device
    std::vector<cl::Device> devices;
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);
    cl::Device device = devices[0];

    // Create a context and command queue for the device
    cl::Context context({ device });
    cl::CommandQueue queue(context, device);

    // Create an OpenCL program from the kernel source
    cl::Program::Sources sources(1, std::make_pair(kernel_source.c_str(), kernel_source.length()));
    cl::Program program(context, sources);

    // Build the program for the device
    program.build({ device });

    // Create an OpenCL kernel from the program
    cl::Kernel kernel(program, "hello_world");

    // Enqueue the kernel to the command queue
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1), cl::NDRange(1));

    // Wait for the kernel to finish executing
    queue.finish();

    std::cout << "Kernel executed successfully" << std::endl;

}
