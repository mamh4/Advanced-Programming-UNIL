#include "test_SFML.h"
#include <SFML/Graphics.hpp>
int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Pixel Simulation");

    // Create a black pixel
    sf::RectangleShape pixel(sf::Vector2f(10, 10));
    pixel.setFillColor(sf::Color::Black);

    // Set the position of the pixel to the center of the screen
    pixel.setPosition(window.getSize().x / 2 - pixel.getSize().x / 2, window.getSize().y / 2 - pixel.getSize().y / 2);

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

        // Move the pixel up
        pixel.move(0, -1);

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the pixel
        window.draw(pixel);

        // Display the window
        window.display();
    }

    return 0;
}


