#pragma once
#include <SFML/Graphics.hpp>
class Organism
{

protected:
    int energy;
    sf::CircleShape shape;

public:
    Organism(float myPosX, float myPosY, float myRadius,int myEnergy);

    int getEnergy();

    void setEnergy(int myEnergy);

    sf::CircleShape getShape();

    void setShape(sf::CircleShape shape);

};

