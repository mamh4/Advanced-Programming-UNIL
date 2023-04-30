#include "Fauna.h"
#include <SFML/Graphics.hpp>
#pragma once

    Fauna::Fauna(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
        int mySpeed, int myAge, int myHungerLevel, float myMetabolicRate,
            int myLustLevel, float myVisionRange) : Organism(myPosX, myPosY, myRadius, myEnergy) {

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

    bool Fauna::getSex() {
        return Fauna::sex;
    }

    int Fauna::getHungerLevel() {
        return Fauna::hungerSensitivity;
    }

    void Fauna::setHungerLevel(int hungerLevel) {
        this->hungerSensitivity = hungerLevel;
    }

    float Fauna::getVisionRange() {
		return Fauna::visionRange;
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

    float Fauna::computeUtility(float distance, Organism organism) {
        return 0;
    }

    //void Fauna::update(std::vector<Organism*> organismVector) {
	//}

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



// 12 assumed to be the number of sections 
// pass step size as class constant 
void Fauna::move(int directionIndicator){
    float stepSize ;
    stepSize = 1.0 ; 
    shape.setPosition(shape.getPosition().x + stepSize* cos( (directionIndicator + 0.5) * M_PI * 2 / 12 ) , shape.getPosition().y + stepSize *  sin( (directionIndicator + 0.5) * M_PI * 2 / 12 ));
}