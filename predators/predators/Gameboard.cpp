#include "Gameboard.h"
#include <SFML/Graphics.hpp>
#include "Predator.h"
#include "Prey.h"
#include "Flora.h"
#include <iostream>
#include <unordered_set>
#include <string>

int numberOfPrey = 0;
int numberOfPredators = 0;
int numberOfFlora = 0;

//TODO: Decide on intialisation in main class of two vectors Fauna and Flora and then we loop through all Faunas, then all Floras? I think so
//TODO: Implement update for Prey and Flora

int main()
{
    //test age of predator any prey make sure they inherit it and the value is 0


    std::vector<Organism*> organismVector;




    //Predator* myPredator = new Predator(500, 500, 5, 750, true, 1, 10, 1, 50, 400);
    //organismVector.push_back(myPredator);
    //Predator* myPredator2 = new Predator(475, 596, 5, 750, false, 1, 10, 1, 50, 800);
    //organismVector.push_back(myPredator2);

    Predator* myPredator3 = new Predator(500, 290, 5, 750, true, 1, 10, 1, 50, 800);
    organismVector.push_back(myPredator3);

    Prey* myPrey = new Prey(400, 460, 7, 900, true, 2, 10, 0.1, 50, 900, 1);
    organismVector.push_back(myPrey);

    Prey* myPrey2 = new Prey(100, 400, 7, 750, false, 2, 10, 0.1, 50, 900, 1);
    organismVector.push_back(myPrey2);

    Flora* myFlora = new Flora(500, 190, 10, 1000, 2);
    organismVector.push_back(myFlora);

    //Flora* myFlora2 = new Flora(900, 900, 10, 1000, 2);
    //organismVector.push_back(myFlora2);

    srand(time(NULL));
    /*
    //std::cout << organismVector.at(0)->getType() << std::endl;
    for (int i = 0; i < numberOfPredators; i++) {
        bool validRespawnPlace = false;
        float posX = 500;
        float posY = 500;
        float radius = 3;
        while (not validRespawnPlace){
            posX = rand() % windowWidth;
            posY = rand() % windowHeight;
            radius = static_cast<float>(rand() % 10 + 5);
            for (int j = 0; j <= i; j++) {
                float distanceSquare = pow(posX - organismVector.at(i)->getPosX(), 2) + pow(posY - organismVector.at(i)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(i)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
            }
        }
        float energy = rand() % 100 + 1;
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = rand() % 3 +1;
        int hungerLevel = rand() % 100 + 1;
        float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
        int lustLevel = rand() % 100 + 1;
        int visionRange = rand() % 100 + 1;
        Predator* myPredator = new Predator(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange);
        organismVector.push_back(myPredator);
    }
    
    for (int i = 0; i < numberOfPrey; i++) {
        bool validRespawnPlace = false;
        float posX = 500;
        float posY = 500;
        float radius = 3;
        while (not validRespawnPlace) {
            posX = rand() % windowWidth;
            posY = rand() % windowHeight;
            radius = static_cast<float>(rand() % 10 + 5);
            for (int j = 0; j <= i; j++) {
                float distanceSquare = pow(posX - organismVector.at(i)->getPosX(), 2) + pow(posY - organismVector.at(i)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(i)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
            }
        }
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
        bool validRespawnPlace = false;
        float posX = 500;
        float posY = 500;
        float radius = 3;
        while (not validRespawnPlace) {
            posX = rand() % windowWidth;
            posY = rand() % windowHeight;
            radius = static_cast<float>(rand() % 10 + 5);
            for (int j = 0; j <= i; j++) {
                float distanceSquare = pow(posX - organismVector.at(i)->getPosX(), 2) + pow(posY - organismVector.at(i)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(i)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
            }
        }
        float energy = rand() % 100 + 1;
        float growthRate = static_cast<float>(rand() * 100);
        Flora* myFlora = new Flora(posX, posY, radius, energy, growthRate);
        organismVector.push_back(myFlora);
    }
    */
    // Create a window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Prey vs Predator");

    //text.setOrigin(0, 0);
    
   
    //Predator myPredator(500, 500, 20, 100, true, 10, 5, 80, 1.5f, 50, 100);

    // Set the frame rate
    window.setFramerateLimit(60);

    // Set the movement speed of the pixel
    float moveSpeed = 1.0f;

    /* sf::Text populationDisplay;
     populationDisplay.setCharacterSize(24);
     populationDisplay.setPosition(500, 1000);
     populationDisplay.setFillColor(sf::Color::Red);
     populationDisplay.setString("Population size: ");

     std::string populationDisplayText ;
 */


    
    // start the game loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //for (Organism* organism : organismVector) {
           // organism->update(organismVector);//make update return the number of added fauna so that we can 
          //                                   //increment the iterator by that amount
        //}
        for (int i = 0; i < organismVector.size(); i++) {

            organismVector.at(i)->update(organismVector);
        }

        sf::Text text;
        sf::Font font;
        font.loadFromFile("aerial.ttf");
        if (!font.loadFromFile("aerial.ttf")) {
            std::cout << "font not loaded" << std::endl;
        }
        text.setFont(font);
        text.setString("Population size: " + std::to_string(organismVector.size()) + "\n" +
            "Predators: " + std::to_string(numberOfPredators) + "\n" + 
            "Prey: " + std::to_string(numberOfPrey) + "\n" +
            "Flora: " + std::to_string(numberOfFlora));
        // +std::to_string(organismVector.size()));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::Black);
        //text.setPosition(0, 0);
        

        // clear the window
        window.clear(sf::Color::White);

        // draw the circles
        for (Organism* organism : organismVector) {
            window.draw(organism->getShape());
            window.draw(text);
        }

        //std::cout << "population size : " << organismVector.size() << std::endl; 
        //std::cout << organismVector.at(1)->getEnergy() << std::endl;
       // populationDisplayText = "Total population: " + organismVector.size(); 

        //populationDisplay.setString(populationDisplayText);
        //window.draw(populationDisplay); 

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




