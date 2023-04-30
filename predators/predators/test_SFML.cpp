#include "test_SFML.h"
#include <SFML/Graphics.hpp>
#include "Predator.h"
#include "Prey.h"
#include <iostream>



int main()
{
    const int numberOfAnimals = 10;

    std::vector<Fauna> fauna;

    for (int i = 0; i < numberOfAnimals; i++) {
        if(rand() < 0.25)
        float posX = static_cast<float>(rand() % 1000);
        float posY = static_cast<float>(rand() % 1000);
        float radius = static_cast<float>(rand() % 10 + 5);
        int energy = rand() % 100 + 1;
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = rand() % 10 + 1;
        int age = rand() % 100 + 1;
        int staminaLevel = rand() % 100 + 1;
        int hungerLevel = rand() % 100 + 1;
        float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
        int lustLevel = rand() % 100 + 1;
        int visionRange = rand() % 100 + 1;
        Fauna myFauna(posX, posY, radius, energy,sex, speed, age, hungerLevel, metabolicRate, lustLevel, visionRange);
        fauna.push_back(myFauna);

    }


    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Prey vs Predator");
   
    //Predator myPredator(500, 500, 20, 100, true, 10, 5, 80, 1.5f, 50, 100);

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
        for (int i = 0; i < numberOfAnimals; i++) {

            myPredator.move(0, -1);

            // Move the circle up
            //myPredator.move(0, -1);

            // Clear the window
            window.clear(sf::Color::White);

            // Draw the circle
            window.draw(myPredator.getShape());

            // Display the window
            window.display();
        }
    }

    return 0;
}
   





