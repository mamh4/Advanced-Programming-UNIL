#include "Fauna.h"
#include <SFML/Graphics.hpp>
#include "OrganicMaths.h"
#include "Predator.h"
#include "Prey.h"


#pragma once

    Fauna::Fauna(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
        int mySpeed, float myHungerSensitivity, float myMetabolicRate,
            float myLustLevel, float myVisionRange) : Organism(myPosX, myPosY, myRadius, myEnergy) {

        sex = mySex;
        speed = mySpeed;
        // Possibly replaced with date of birth (turn of birth ) then access age as the difference between current turn and turn of birth 
        age = 0;
        hungerSensitivity = myHungerSensitivity;
        metabolicRate = myMetabolicRate;
        lustLevel = myLustLevel;
        visionRange = myVisionRange;
    }

    int Fauna::getSpeed() {
        return this->speed;
    }

    void Fauna::setSpeed() {
        this->speed = speed;
    }

    int Fauna::getAge() {
        return this->age;
    }

    void Fauna::setAge(int age) {
        this->age = age;
    }

    bool Fauna::getSex() {
        return this->sex;
    }

    float Fauna::getHungerSensitivity() {
        return this->hungerSensitivity;
    }

    void Fauna::setHungerSensitivity(float hungerSensitivity) {
        this->hungerSensitivity = hungerSensitivity;
    }

    float Fauna::getVisionRange() {
		return this->visionRange;
	}


    float Fauna::getMetabolicRate() {
        return this->metabolicRate;
    }

    void Fauna::setMetabolicRate(float metabolicRate) {
        this->metabolicRate = metabolicRate;
    }

    float Fauna::getLustLevel() {
        return this->lustLevel;
    }

    void Fauna::setLustLevel(float lustLevel) {
        this->lustLevel = lustLevel;
    }

    void Fauna::interact(Organism* organism, std::vector<Organism*>& organismVector) {
    }

    float Fauna::computeUtility(float distance, Organism* organism) {
        return 0;
    }

    //TODO implement this function
    void Fauna::dies(std::vector<Organism*>& organismVector){

        auto it = std::remove(organismVector.begin(), organismVector.end(), this);
        organismVector.erase(it, organismVector.end());
        delete this;
    }

    //void Fauna::update(std::vector<Organism*> organismVector) {
	//}

    /* psudo code implementatin of the move function animal.step_size <- 4

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
    
    //std::cout << "my speed is " << Fauna::getSpeed() << "my coordinates are: " << Fauna::getPosX() << " "<< Fauna::getPosY << std::endl;
    std::cout << "my position is " << Fauna::getPosX() << " " << Fauna::getPosY() << std::endl;
    float energyCostOfMovement; 
    energyCostOfMovement = 5.0 ; 
    // as Class constant later on ? 
    //Fauna::getShape().setPosition(Fauna::getShape().getPosition().x + stepSize * cos((directionIndicator + 0.5) * M_PI * 2 / 12),
    //    Fauna::getShape().getPosition().y + stepSize * sin((directionIndicator + 0.5) * M_PI * 2 / 12));
    this->setPosX(this->getPosX() + stepSize * cos((directionIndicator + 0.5) * M_PI * 2 / 12));
    this->setPosY(this->getPosY() + stepSize * sin((directionIndicator + 0.5) * M_PI * 2 / 12));
    this->setEnergy( this->getEnergy() - energyCostOfMovement ); 
}

void Fauna::ageing() {
    age ++ ;
    Fauna::setRadius(Fauna::getRadius() + 1);
}

void Fauna::update(std::vector<Organism*>& organismVector) {
    Fauna::ageing(); // CHANGE TO DATE OF BIRTH 
    Fauna::setEnergy(Fauna::getEnergy() - Fauna::getMetabolicRate());
    // with arbitrary 100 seconds (6000 frames ) max lifespan, arbitrary function with certain death at 6000 
    //Maybe separate function
    if ((1.0 * (rand() % 100) < (100 * std::pow(((1 + Fauna::getAge()) / 6000), 10)) or (Fauna::getEnergy() <= 0))) {
        Fauna::dies(organismVector);
    }

    for (int k = 1; k <= Fauna::getSpeed(); k++) { // BEGINING OF TURN LOOP 

        float distSquare;
        float angleBetween;

        float currentUtility;

        float maxDirectionalUtility = 0;
        float maxInteractionUtility = 0;

        Organism* maxInteractionUtilityTarget = nullptr;
        int maxDirectionalUtilityTarget = 0;

        std::vector<float> directionalUtility(angleSectionNumber, 0.0);
        std::vector<Organism*> possibleCollisions;

        for (int i = 0; i < organismVector.size(); i++) {
            //TRY organismVector.at(i)->getRadius() print maybe
            distSquare = distanceSquared(organismVector.at(i), this);//organismvector at get radius is read as an uninitialised organism
            if ((distSquare > 0.001) and (distSquare < std::pow(this->getVisionRange() - organismVector.at(i)->getRadius(), 2))) {

                if (distSquare < std::pow(this->getRadius() + organismVector.at(i)->getRadius() + rangeOfInteraction, 2)) {
                    //                   possibleCollisions.push_back(OrganismVector.at(i));
                    currentUtility = computeUtility(0.0, organismVector.at(i));
                    // Arbitrarily distance 0.0 to transmit that it is utility of an interaction
                    // NEED TO BE PASSED ARE RIGHT POINTER OR INTERPRETED ONCE IN COMPUTE UTILITY 
                    if (currentUtility > maxInteractionUtility) {
                        maxInteractionUtility = currentUtility;
                        maxInteractionUtilityTarget = organismVector.at(i);
                    }
                    //angleBetween = angle(OrganismVector.at(i), this);
                    //if ( pow(Fauna::getShape().getPosition().x - OrganismVector.at(i)->getShape().getPosition().x + stepSize*cos(2*M_PI* (angleSorting(angleBetween)+ 0.5) / directionalUtilitySize ),2  ) 
                    //+  pow(Fauna::getShape().getPosition().y - OrganismVector.at(i)->getShape().getPosition().y + stepSize*sin(2*M_PI* (angleSorting(angleBetween)+ 0.5) / directionalUtilitySize ),2  )  
                     //< pow((Fauna::getShape().getRadius() + OrganismVector.at(i)->getShape().getRadius()),2) ) {
                    //    directionalUtility[angleSorting(angleBetween)] -= 1000 ; 
                    //    //arbitrary malus 
                    //}
                }
                else {
                   // currentUtility = computeUtility(distSquare, organismVector.at(i));
                   // angleBetween = angle(organismVector.at(i), this);
                    //directionalUtility[angleSorting(angleBetween)] += currentUtility;
                    //Prototype for directional gradient of utility increase / MAYBE CHANGE DECREASE RATE ?   
                    //for (int l = 1; l <= (angleSectionNumber / 4); l++) {
                     //   directionalUtility[((angleSorting(angleBetween) + l) % 12)] += (currentUtility / (l + 1));
                      //  directionalUtility[((angleSorting(angleBetween) - l) % 12)] += (currentUtility / (l + 1));
                    //}
                }
            }
        }
        for (int i = 0; i < possibleCollisions.size(); i++) {
            for (int j = 0; j < directionalUtility.size(); j++) {
                // ELIMINATION 
                if (std::pow(this->getPosX() - possibleCollisions.at(i)->getPosX() + stepSize * cos(2 * M_PI * (j + 0.5) / directionalUtility.size()), 2)
                    + std::pow(this->getPosY() - possibleCollisions.at(i)->getPosX() + stepSize * sin(2 * M_PI * (j + 0.5) / directionalUtility.size()), 2)
                    < std::pow((this->getRadius() + possibleCollisions.at(i)->getRadius()), 2)) {
                    angleBetween = angle(possibleCollisions.at(i), this);//was missing
                    directionalUtility[angleSorting(angleBetween)] -= 1000;
                }
            }
        }

        if (maxDirectionalUtility > maxInteractionUtility) {
            this->move(maxDirectionalUtilityTarget);
        }
        else {
            this->interact(maxInteractionUtilityTarget, organismVector);
        }
    }
}////VERY IMPORTANT: interact is not being called from the predator class 
//Issue 1) Is compute utility correct to the class?????
//Issue 2) Check if the correct inherited method is being called, possibly I would need to create a predator instance and call
// the compute utility method and interact method from there
	



