#pragma once
#include <CL/cl.hpp>
#include <iostream>
#include <fstream>

class OpenCL_Kernel
{
private:

public:
	OpenCL_Kernel();

	void Kernel(double*** matrix, int width, int height, int** colors);
	void HelloWorldTest();
};

