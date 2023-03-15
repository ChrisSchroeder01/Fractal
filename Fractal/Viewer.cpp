#include "Viewer.h"

Viewer::Viewer(Model* m)
{
	this->m = m;
}

void Viewer::Draw()
{
    // Clear the Window
    m->window->clear();

    m->window->draw(m->sprite);

    // Update the Window
    m->window->display();
}
