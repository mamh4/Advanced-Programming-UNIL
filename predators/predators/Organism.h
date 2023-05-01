#pragma once
#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <iostream>
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

    virtual std::string getType();

    virtual void update(std::vector<Organism*>& organismVector);

    virtual void dies(std::vector<Organism*>& organismVector);

};

