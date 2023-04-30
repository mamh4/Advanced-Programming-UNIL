#pragma once
#include "Organism.h"
#include <SFML/Graphics.hpp>
class Fauna : public Organism
{
private:
    bool sex;
    int speed;
    int age;
    int hungerSensitivity;
    float metabolicRate;
    int lustLevel;
    int visionRange;

public:
    Fauna(float myPosX, float myPosY, float myRadius, int myEnergy,bool mySex,
        int mySpeed, int myAge, int myHungerLevel,
        float myMetabolicRate, int myLustLevel, int myVisionRange);

    int getSpeed();

    void setSpeed();

    int getAge();

    void setAge(int age);

    int getHungerLevel();

    void setHungerLevel(int hungerLevel);

    float getMetabolicRate();

    void setMetabolicRate(float metabolicRate);

    int getLustLevel();

    void setLustLevel(int lustLevel);

    void move(float x, float y);

};

