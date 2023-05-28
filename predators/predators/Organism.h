#pragma once
#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <iostream>

class Organism
{
private:
    float posX;
	float posY;
    float radius;

protected:
    float energy;
    sf::CircleShape shape;

public:
    Organism(float myPosX, float myPosY, float myRadius,float myEnergy);

    virtual ~Organism() {};

    float getPosX();

    void setPosX(float myPosX);

    float getPosY();

    void setPosY(float myPosY);

    float getRadius();

    void setRadius(float myRadius);

    float getEnergy();

    void setEnergy(float myEnergy);

    sf::CircleShape getShape();

    void setShape(sf::CircleShape shape);

    virtual std::string getType();

    virtual void update(std::vector<Organism*>& organismVector);

    virtual void die(std::vector<Organism*>& organismVector);

};

