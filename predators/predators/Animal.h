#pragma once
#include <SFML/Graphics.hpp>
class Animal
{
private:
    float posX;
    float posY;
    float radius;

    bool sex;
    int speed;
    int age;
    int staminaLevel;
    int hungerSensitivity;
    float metabolicRate;
    int lustLevel;
    int visionRange;

    sf::CircleShape shape;

public:
    Animal(float myPosX, float myPosY, float myRadius, bool mySex,
        int mySpeed, int myAge, int myStaminaLevel, int myHungerLevel,
        float myMetabolicRate, int myLustLevel, int myVisionRange);

    float getPosX();

    void setPosX(float posX);

    float getPosY();

    void setPosY(float posY);

    float getRadius();

    sf::CircleShape getShape();

    void setRadius(float radius);

    int getSpeed();

    void setSpeed();

    int getAge();

    void setAge(int age);

    int getStaminaLevel();

    void setStaminaLevel(int staminaLevel);

    int getHungerLevel();

    void setHungerLevel(int hungerLevel);

    float getMetabolicRate();

    void setMetabolicRate(float metabolicRate);

    int getLustLevel();

    void setLustLevel(int lustLevel);

    void move(float x, float y);
};

