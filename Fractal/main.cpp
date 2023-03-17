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
    Controller* controller = new Controller(model, viewer);
    InputManager* inputManager = new InputManager(controller, model);

    controller->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
    // Start Loop
    while (window.isOpen())
    {
        
        // Process Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            inputManager->Handle(event, window);
        }
        inputManager->Handle();

        if (controller->NeedToRedraw())
        {
           controller->Render(WINDOW_WIDTH, WINDOW_HEIGHT);
           
        }
        viewer->Draw();
    }

    return EXIT_SUCCESS;
}

