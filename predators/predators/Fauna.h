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
    float visionRange;
protected:
    static const int rangeOfInteraction = 2;
public:
    Fauna(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
        int mySpeed, int myAge, int myHungerLevel,
        float myMetabolicRate, int myLustLevel, float myVisionRange);

    int getSpeed();

    void setSpeed();

    int getAge();

    void setAge(int age);

    bool getSex();

    int getHungerLevel();

    void setHungerLevel(int hungerLevel);

    float getMetabolicRate();

    void setMetabolicRate(float metabolicRate);

    int getLustLevel();

    void setLustLevel(int lustLevel);

    float getVisionRange();

    virtual float computeUtility(float distance, Organism organism);

    void move(int direction);


};

