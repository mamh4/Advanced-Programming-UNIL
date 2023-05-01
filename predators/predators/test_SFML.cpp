#include "test_SFML.h"
#include <SFML/Graphics.hpp>
#include "Predator.h"
#include "Prey.h"
#include "Flora.h"
#include <iostream>



//TODO: Decide on intialisation in main class of two vectors Fauna and Flora and then we loop through all Faunas, then all Floras? I think so
//TODO: Implement update for Prey and Flora

int main()
{
    //test age of predator any prey make sure they inherit it and the value is 0
    const int numberOfPrey = 1;
    const int numberOfPredators = 1;
    const int numberOfFlora = 1;

    std::vector<Organism*> organismVector;


    //Predator(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
     //   int mySpeed, float myHungerSensitivity,
     //  float myMetabolicRate, float myLustLevel, float myVisionRange);

    //Predator* myPredator = new Predator(500, 500, 20, 100, true, 10, 5, 1.5f, 50, 100);
    //organismVector.push_back(myPredator);

    //std::cout << organismVector.at(0)->getType() << std::endl;

    for (int i = 0; i < numberOfPredators; i++) {
        float posX = static_cast<float>(rand() % 1000);
        float posY = static_cast<float>(rand() % 1000);
        float radius = static_cast<float>(rand() % 10 + 5);
        float energy = rand() % 100 + 1;
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = rand() % 10 + 1;
        int hungerLevel = rand() % 100 + 1;
        float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
        int lustLevel = rand() % 100 + 1;
        int visionRange = rand() % 100 + 1;
        Predator* myPredator = new Predator(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange);
        organismVector.push_back(myPredator);
    }

    for (int i = 0; i < numberOfPrey; i++) {
        float posX = static_cast<float>(rand() % 1000);
        float posY = static_cast<float>(rand() % 1000);
        float radius = static_cast<float>(rand() % 10 + 5);
        float energy = rand() % 100 + 1;
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = rand() % 10 + 1;
        int hungerLevel = rand() % 100 + 1;
        float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
        int lustLevel = rand() % 100 + 1;
        int visionRange = rand() % 100 + 1;
        float predatorAversion = static_cast<float>(rand() * 100);
        Prey* myPrey = new Prey(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange, predatorAversion);
        organismVector.push_back(myPrey);
    }

    for (int i = 0; i < numberOfFlora; i++) {
        float posX = static_cast<float>(rand() % 1000);
        float posY = static_cast<float>(rand() % 1000);
        float radius = static_cast<float>(rand() % 10 + 5);
        float energy = rand() % 100 + 1;
        float growthRate = static_cast<float>(rand() * 100);
        Flora* myFlora = new Flora(posX, posY, radius, energy, growthRate);
        organismVector.push_back(myFlora);
    }
    // Create a window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Prey vs Predator");

    //Predator myPredator(500, 500, 20, 100, true, 10, 5, 80, 1.5f, 50, 100);

    // Set the frame rate
    window.setFramerateLimit(30);

    // Set the movement speed of the pixel
    float moveSpeed = 1.0f;

    // start the game loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // move the circles up
        for (Organism* circle : organismVector) {
            sf::Vector2f position = circle->getShape().getPosition();
            circle->setPosX(position.x);
            circle->setPosY(position.y-5);
        }

        // clear the window
        window.clear(sf::Color::White);

        // draw the circles
        for (Organism* circle : organismVector) {
            window.draw(circle->getShape());
        }

        // display the window
        window.display();
    }
}
/*

    //----------------

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
        for (int i = 0; i < organismVector.size(); i++) {
            //NEED TO CHECK TYPE FIRST
            organismVector.at(i)->getShape().setPosition(organismVector.at(i)->getShape().getPosition().x, organismVector.at(i)->getShape().getPosition().y);

            // Move the circle up
            organismVector.at(i)->getShape().move(0, -5);

            // Clear the window
            window.clear(sf::Color::White);

            // Draw the circle
            window.draw(organismVector.at(i)->getShape());

            // Display the window
            window.display();
        }
    }

    return 0;
}
   
   */




