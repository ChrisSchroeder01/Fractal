#pragma once
#include <CL/cl.hpp>
#include <iostream>
#include <fstream>

class OpenCL_Kernel
{
private:
	cl::Context context;
	cl::CommandQueue queue;
	cl::Kernel kernel;
public:
	OpenCL_Kernel();

	void Kernel(double* matriX, double* matriY, int width, int height, int** colors);
};

