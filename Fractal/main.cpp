#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Model.h"
#include "Viewer.h"
#include "Controller.h"
#include "InputManager.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fractal Window");
    
    // Create Backend Structure
    Model* model = new Model(&window);
    Viewer* viewer = new Viewer(model);
    Controller* controller = new Controller(model);
    InputManager* inputManager = new InputManager(controller);

    controller->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
    // Start Loop
    while (window.isOpen())
    {
        
        // Process Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            inputManager->Handle(event);
        }

        if (controller->NeedToRedraw())
        {
           controller->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
        }

        viewer->Draw();

    }

    
    /*

    bool scrolling = false;
    sf::Clock lastScrolled;
    int changeZoomBy = 0;

    // Create Backend Structure
    Model* m = new Model(WINDOW_WIDTH, WINDOW_HEIGHT);
    Controller* c = new Controller(m);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fractal Window");

    // Start the game loop
    while (window.isOpen())
    {
        if (c->NeedToRedraw())
        {
            c->LoadImage(frame);
            /*
            // Create Threads
            std::thread first(&Controller::calculateArea, c, 0, (WINDOW_HEIGHT / 4) * 0, WINDOW_WIDTH, (WINDOW_HEIGHT / 4));
            std::thread second(&Controller::calculateArea, c, 0, (WINDOW_HEIGHT / 4) * 1, WINDOW_WIDTH, (WINDOW_HEIGHT / 4));
            std::thread third(&Controller::calculateArea, c, 0, (WINDOW_HEIGHT / 4) * 2, WINDOW_WIDTH, (WINDOW_HEIGHT / 4));
            std::thread forth(&Controller::calculateArea, c, 0, (WINDOW_HEIGHT / 4) * 3, WINDOW_WIDTH, (WINDOW_HEIGHT / 4));

            // Synchronize Threads
            first.join();
            second.join();
            third.join();
            forth.join();
            
            c->calc(1280, 720);

            c->SaveImage(frame);
        }

        // Process Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close Window Exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Mouse Wheel Moved
            if (event.type == sf::Event::MouseWheelMoved)
            {
                scrolling = true;
                lastScrolled.restart();
                changeZoomBy += event.mouseWheel.delta;
            }

            // Mouse Button Pressed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == 0)
                {
                    moving = true;
                    oldPos = sf::Vector2f(sf::Mouse::getPosition(window));
                }
            }

            // Mouse Button Released
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == 0)
                {
                    std::cout << "Change xy by - x: " << deltaPos.x << " y: " << deltaPos.y << std::endl;
                    m->changeXYBy(deltaPos.x, deltaPos.y);
                    moving = false;
                }
            }

            // Mouse Moved
            if (event.type == sf::Event::MouseMoved) {
                if (!moving)
                    break;
                newPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                deltaPos = oldPos - newPos;
            }
        }
        // Clear screen
        window.clear();

        actionSprite.setPosition(0, 0);
        actionSprite.setScale(1, 1);
        actionSprite.setColor(tMask);

        window.draw(sprite);
        if (moving)
        {
            actionSprite.setPosition(-deltaPos);
            window.draw(actionSprite);
        }

        if (scrolling)
        {
            actionSprite.setPosition((-WINDOW_WIDTH * changeZoomBy / (float)m->getZoom()) / 2, (-WINDOW_HEIGHT * changeZoomBy / (float)m->getZoom()) / 2);
            actionSprite.setScale(1.0 + changeZoomBy / (float)m->getZoom(), 1.0 + changeZoomBy / (float)m->getZoom());
            window.draw(actionSprite);
        }

        if (scrolling && lastScrolled.getElapsedTime().asSeconds() > 0.5)
        {
            scrolling = false;
            c->Zoom(changeZoomBy);

            std::cout << "Zoom: " << changeZoomBy << std::endl;

            changeZoomBy = 0;
        }

        // Update the window
        window.display();
    }

    */
    return EXIT_SUCCESS;
}

