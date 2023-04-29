#include "test_SFML.h"
#include <SFML/Graphics.hpp>
#include "Predator.h"
#include <iostream>

int main()
{

    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Prey vs Predator");

    Predator myPredator(500, 500, 10, true, 5, 3, 10, 5, 0.2, 10, 50);

    // Set the frame rate to 60 frames per second
    window.setFramerateLimit(60);

    // Set the movement speed of the pixel
    float moveSpeed = 1.0f;

    while (window.isOpen())
    {
        // Check for events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Move the circle up
        myPredator.move(0, -1);

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the circle
        window.draw(myPredator.getShape());

        // Display the window
        window.display();
    }

    return 0;
}
   





