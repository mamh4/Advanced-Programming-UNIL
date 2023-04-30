#pragma once
#include <SFML/Graphics.hpp>
class Organism
{

protected:
    float energy;
    sf::CircleShape shape;

public:
    Organism(float myPosX, float myPosY, float myRadius,float myEnergy);

    ~Organism() {};

    float getEnergy();

    void setEnergy(float myEnergy);

    sf::CircleShape getShape();

    void setShape(sf::CircleShape shape);

};

