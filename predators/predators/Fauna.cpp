#include "Fauna.h"
#include <SFML/Graphics.hpp>
#pragma once

    Fauna::Fauna(float myPosX, float myPosY, float myRadius, int myEnergy,bool mySex,
        int mySpeed, int myAge, int myHungerLevel, float myMetabolicRate,
            int myLustLevel, int myVisionRange) : Organism(myPosX, myPosY, myRadius, myEnergy) {

        energy = myEnergy;
        sex = mySex;
        speed = mySpeed;
        age = myAge;
        hungerSensitivity = myHungerLevel;
        metabolicRate = myMetabolicRate;
        lustLevel = myLustLevel;
        visionRange = myVisionRange;
    }

    int Fauna::getSpeed() {
        return Fauna::speed;
    }

    void Fauna::setSpeed() {
        this->speed = speed;
    }

    int Fauna::getAge() {
        return Fauna::age;
    }

    void Fauna::setAge(int age) {
        this->age = age;
    }

    int Fauna::getHungerLevel() {
        return Fauna::hungerSensitivity;
    }

    void Fauna::setHungerLevel(int hungerLevel) {
        this->hungerSensitivity = hungerLevel;
    }

    float Fauna::getMetabolicRate() {
        return Fauna::metabolicRate;
    }

    void Fauna::setMetabolicRate(float metabolicRate) {
        this->metabolicRate = metabolicRate;
    }

    int Fauna::getLustLevel() {
        return lustLevel;
    }

    void Fauna::setLustLevel(int lustLevel) {
        this->lustLevel = lustLevel;
    }

    void Fauna::move(float x, float y) {
        Fauna::shape.move(x, y);
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


