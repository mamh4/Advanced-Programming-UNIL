#include "Animal.h"
#pragma once
class Animal
{
private:
    int posX;
    int posY;
    int radius;

    bool sex;
    int speed;
    int age;
    int staminaLevel;
    int hungerLevel;
    float metabolicRate;
    int lustLevel;
    int visionRange;

public:
    Animal(int myPosX, int myPosY, int myRadius, bool mySex,
        int mySpeed, int myAge, int myStaminaLevel, int myHungerLevel,
        float myMetabolicRate, int myLustLevel, int myVisionRange) {
        posX = myPosX;
        posY = myPosY;
        radius = myRadius;
        sex = mySex;
        speed = mySpeed;
        age = myAge;
        staminaLevel = myStaminaLevel;
        hungerLevel = myHungerLevel;
        metabolicRate = myMetabolicRate;
        lustLevel = myLustLevel;
        visionRange = myVisionRange;
    }

    int getPosX() {
        return posX;
    }

    void setPosX(int posX) {
        this->posX = posX;
    }

    int getPosY() {
        return posY;
    }

    void setPosY(int posY) {
        this->posY = posY;
    }

    int getRadius() {
        return radius;
    }

    void setRadius(int radius) {
        this->radius = radius;
    }

    int getSpeed() {
        return speed;
    }

    void setSpeed() {
        this->speed = speed;
    }

    int getAge() {
        return age;
    }

    void setAge(int age) {
        this->age = age;
    }

    int getStaminaLevel() {
        return staminaLevel;
    }

    void setStaminaLevel(int staminaLevel) {
        this->staminaLevel = staminaLevel;
    }

    int getHungerLevel() {
        return hungerLevel;
    }

    void setHungerLevel(int hungerLevel) {
        this->hungerLevel = hungerLevel;
    }

    float getMetabolicRate() {
        return metabolicRate;
    }

    void setMetabolicRate(float metabolicRate) {
        this->metabolicRate = metabolicRate;
    }

    int getLustLevel() {
        return lustLevel;
    }

    void setLustLevel(int lustLevel) {
        this->lustLevel = lustLevel;
    }

    /* psudo code implementatin of the move function
    animal.step_size <- 4

    move <- function(){
      #call utility score function: A function that determines and returns a coordinate of the best viable option
      haven <- score_function()
      dx <- animal.posX-haven.posX
      dy <- animal.posY-haven.posY

      in_radius <- sqrt(dx^2+dy^2) <= haven.radius

      if(!in_radius){

        # Determine the direction of movement for each axis
        if (dx > 0) {
          x_dir <- min(dx,animal.step_size)
        } else if (dx < 0) {
          x_dir <- -min(dx,animal.step_size)
        }

        if (dy > 0) {
          y_dir <- min(dy,animal.step_size)
        } else if (dy < 0) {
          y_dir <- -min(dy,animal.step_size)
        }

       animal.set_position(animapl.posX+x_dir,animal.posY+y_dir)

      }


    }
        */

};

