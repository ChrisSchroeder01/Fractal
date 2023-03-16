
#include "Controller.h"
#include <complex>
#include <iostream>


int mandelbrotColor(double x, double y)
{
	std::complex<double> z(0, 0);
	std::complex<double> c(x, y);

	int iterations = 0;
	while (iterations < 200 && std::abs(z) < 2.0) {
		z = z * z + c;
		iterations++;
	}
	if (iterations == 200) {
		return 0; // point is in Mandelbrot set, color is black
	}
	else {
		return iterations;
	}
}

void kernelXY(double* matriX, double* matriY, int width, int height, int** colors) {
	
	int* output = new int[width * height];
	for (int i = 0; i < width * height; i++)
	{

		if (i==309092)
		{
			std::cout << "break";
		}

		output[i] = mandelbrotColor(matriX[i], matriY[i]);
	}

	for (int i = 0; i < width * height; i++)
	{
		int x = i % width;
		int y = i / width;
		colors[y][x] = output[i];
	}
}


void kernelMat(double*** matrix, int width, int height , int** colors) {
	for (int y = 0; y < height; y++)
	{	
		for (int x = 0; x < width; x++)
		{
			colors[y][x] = mandelbrotColor(matrix[y][x][0], matrix[y][x][1]);
		}
	}
}




Controller::Controller(Model* m)
{
	this->m = m;
	this->kernel = new OpenCL_Kernel();
}

void Controller::LoadImg(sf::Texture& screen)
{
	// Get Texture Image
	this->image = screen.copyToImage();
}

void Controller::SaveImg(sf::Texture& screen)
{
	// Set Texture Image
	screen.loadFromImage(this->image);
}

bool Controller::NeedToRedraw()
{
	// Test If Recalculation is Nessesary
	int width = image.getSize().x;
	int height = image.getSize().y;

	if (//m->lastwidth == width &&
		//m->lastheight == height &&
		m->lastzoom == m->getZoom() &&
		m->lastxOffset == m->getXOffset() &&
		m->lastyOffset == m->getYOffset()) {
		return false;
	}

	//m->lastwidth = width;
	//m->lastheight = height;
	m->lastxOffset = m->getXOffset();
	m->lastyOffset = m->getYOffset();
	m->lastzoom = m->getZoom();
	return true;
}

void Controller::Zoom(int amount)
{
	m->changeZoomBy(amount);
}

void Controller::ChangeOffset(int x, int y)
{
	m->changeOffsetBy(x, y);
}

void Controller::Render(int width, int height)
{
	this->LoadImg(m->frame);

	double* matriX = new double[width * height];
	double* matriY = new double[width * height];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			double dx = ((double)x - m->getXOffset()) / m->getZoom();
			double dy = ((double)y - m->getYOffset()) / m->getZoom();

			int i = y * width + x;
			matriX[i] = dx;
			matriY[i] = dy;
		}
	}

	int** colors = new int*[height];
	for (int y = 0; y < height; y++)
	{
		colors[y] = new int[width];
	}

	//kernelXY(matriX, matriY, width, height, colors);
	//kernelMat(matrix, width, height, colors);
	this->kernel->Kernel(matriX,matriY, width, height, colors);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float f = colors[y][x] / 200.0f;
			int r, g, b;

			if (f < 0.25) {
				r = (f * 4 * 255);
				g = 0;
				b = 0;
			}
			else if (f < 0.5) {
				r = 255;
				g = (f - 0.25) * 4 * 255;
				b = 0;
			}
			else if (f < 0.75) {
				r = (0.75 - f) * 4 * 255;
				g = 255;
				b = (f - 0.5) * 4 * 255;
			}
			else {
				r = 0;
				g = (1 - f) * 4 * 255;
				b = 255;
			}

			sf::Color color(r, g, b, 255);
			// Set pixel to color
			this->image.setPixel(x, y, color);
		}
	}

	delete[] matriX;
	delete[] matriY;
	delete[] colors;

	SaveImg(m->frame);
}

void Controller::Exit()
{
	this->m->window->close();
}

