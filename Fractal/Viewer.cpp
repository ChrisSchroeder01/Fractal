#include "Viewer.h"

Viewer::Viewer(Model* m)
{
	this->m = m;
}

void Viewer::Draw()
{
    // Clear the Window
    m->window->clear();

    m->actionSprite.setPosition(0, 0);
    m->actionSprite.setScale(1, 1);
    m->actionSprite.setColor(m->tMask);

    m->window->draw(m->sprite);

    if (m->moving)
    {
        m->actionSprite.setPosition(-m->deltaPos);
        m->window->draw(m->actionSprite);
    }

    if (m->scrolling)
    {
        m->actionSprite.setPosition((-(int)(m->window->getSize().x) * m->zoomChange / (float)m->getZoom()) / 2, (-(int)(m->window->getSize().y) * m->zoomChange / (float)m->getZoom()) / 2);
        m->actionSprite.setScale(1.0 + m->zoomChange / (float)m->getZoom(), 1.0 + m->zoomChange / (float)m->getZoom());
        m->window->draw(m->actionSprite);
    }

    // Update the Window
    m->window->display();
}
