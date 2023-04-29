#include "Animal.h"
#include <SFML/Graphics.hpp>
#pragma once

    Animal::Animal(float myPosX, float myPosY, float myRadius, bool mySex,
        int mySpeed, int myAge, int myStaminaLevel, int myHungerLevel,
        float myMetabolicRate, int myLustLevel, int myVisionRange) {
        posX = myPosX;
        posY = myPosY;
        radius = myRadius;
        sex = mySex;
        speed = mySpeed;
        age = myAge;
        staminaLevel = myStaminaLevel;
        hungerSensitivity = myHungerLevel;
        metabolicRate = myMetabolicRate;
        lustLevel = myLustLevel;
        visionRange = myVisionRange;

        sf::CircleShape shape(2*radius);
        shape.setPosition(posX, posY);
    }

    float Animal::getPosX() {
        return Animal::posX;
    }

    void Animal::setPosX(float posX) {
        this->posX = posX;
    }

    float Animal::getPosY() {
        return Animal::posY;
    }

    void Animal::setPosY(float posY) {
        this->posY = posY;
    }

    sf::CircleShape Animal::getShape() {
		return Animal::shape;
	}

    float Animal::getRadius() {
        return Animal::radius;
    }

    void Animal::setRadius(float radius) {
        this->radius = radius;
    }

    int Animal::getSpeed() {
        return Animal::speed;
    }

    void Animal::setSpeed() {
        this->speed = speed;
    }

    int Animal::getAge() {
        return Animal::age;
    }

    void Animal::setAge(int age) {
        this->age = age;
    }

    int Animal::getStaminaLevel() {
        return Animal::staminaLevel;
    }

    void Animal::setStaminaLevel(int staminaLevel) {
        this->staminaLevel = staminaLevel;
    }

    int Animal::getHungerLevel() {
        return Animal::hungerSensitivity;
    }

    void Animal::setHungerLevel(int hungerLevel) {
        this->hungerSensitivity = hungerLevel;
    }

    float Animal::getMetabolicRate() {
        return Animal::metabolicRate;
    }

    void Animal::setMetabolicRate(float metabolicRate) {
        this->metabolicRate = metabolicRate;
    }

    int Animal::getLustLevel() {
        return lustLevel;
    }

    void Animal::setLustLevel(int lustLevel) {
        this->lustLevel = lustLevel;
    }

    void Animal::move(float x, float y) {
		Animal::setPosX(x);
        Animal::setPosY(y);
        Animal::shape.move(x, y);
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


