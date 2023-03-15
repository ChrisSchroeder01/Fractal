#pragma once
#include "Model.h"

class Viewer
{
private:
	Model* m;

public:

	Viewer(Model* m);

	void Draw();
};

