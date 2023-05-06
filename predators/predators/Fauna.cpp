#include "Fauna.h"
#include <SFML/Graphics.hpp>
#include "OrganicMaths.h"
#include "Predator.h"
#include "Prey.h"
#include "Gameboard.h"
#include "GeneticIntervals.h"
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
        fertile = false;
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

   // void Fauna::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, float& maxDirectionalUtility, int maxDirectionalUtilityTarget, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget){
   // }
    void Fauna::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget){
    }

    //TODO implement this function
    void Fauna::dies(std::vector<Organism*>& organismVector){
        auto it = std::remove(organismVector.begin(), organismVector.end(), this);
        organismVector.erase(it, organismVector.end());
        delete this;

        numberOfPredators += 1;
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
    float energyCostOfMovement; 
    energyCostOfMovement = 0.1 ; 
    // as Class constant later on ? 
    //Fauna::getShape().setPosition(Fauna::getShape().getPosition().x + stepSize * cos((directionIndicator + 0.5) * M_PI * 2 / 12),
    //    Fauna::getShape().getPosition().y + stepSize * sin((directionIndicator + 0.5) * M_PI * 2 / 12)); 
    this->setPosX(this->getPosX() + stepSize * cos((directionIndicator + 0.5) * M_PI * 2 / angleSectionNumber));
    this->setPosY(this->getPosY() + stepSize * sin((directionIndicator + 0.5) * M_PI * 2 / angleSectionNumber));
    this->setEnergy( this->getEnergy() - energyCostOfMovement ); 
}

void Fauna::ageing() {
    age ++ ;
    this->setRadius(this->getRadius() + 0.001);
}



void Fauna::update(std::vector<Organism*>& organismVector) {
    this->ageing(); // CHANGE TO DATE OF BIRTH 
    this->setEnergy(this->getEnergy() - this->getMetabolicRate());
    // with arbitrary 100 seconds (6000 frames ) max lifespan, arbitrary function with certain death at 6000 
    //Maybe separate function
    //a:delete the pointer
    //Predator* offspring = new Predator(79.0, 515.0, 10.0, 1, false, 60, 10, 1, 0, 600);//Above parameters cause program failure!

    //std::cout << "I am a " << this->getSex() << "My current energy level is " << this->getEnergy() << std::endl; 
    if ((1.0 * (rand() % 100) < (100 * std::pow(((1 + this->getAge()) / 6000), 10)) or (this->getEnergy() <= 0))) {
      this->dies(organismVector);
      
    }
    else {
        int minFertilityAge = 50;
        int maxFertilityAge = 100;
        if ((1.0 * (rand() % 100) < std::max(0.0, (100 * std::pow(((this->getAge() - minFertilityAge) / (maxFertilityAge - minFertilityAge)), 10)))) and not this->getFertile()) {
            this->setFertile(true);
            std::cout << "Fertility Unlocked " << std::endl;
        }
        for (int k = 0; k <= this->getSpeed(); k++) { // BEGINING OF TURN LOOP 

            float distSquare;
            float angleBetween = 0.0;

            float maxDirectionalUtility = 0;
            //float maxInteractionUtility = -1000.0;
            float maxInteractionUtility = 0.0;

            Organism* maxInteractionUtilityTarget = nullptr;
            int maxDirectionalUtilityTarget = 0;




            std::vector<float> directionalUtility(angleSectionNumber, 0.0);
            std::vector<Organism*> possibleCollisions;

            for (int i = 0; i < organismVector.size(); i++) {
                //TRY organismVector.at(i)->getRadius() print maybe
                distSquare = distanceSquared(organismVector.at(i), this);//organismvector at get radius is read as an uninitialised organism
                if ((distSquare > 0.0001) and (distSquare < std::pow(this->getVisionRange() - organismVector.at(i)->getRadius(), 2))) {
                    //   this->computeUtility(distSquare, organismVector.at(i), directionalUtility, maxDirectionalUtility , maxDirectionalUtilityTarget , possibleCollisions, maxInteractionUtility , maxInteractionUtilityTarget ); 
                    this->computeUtility(distSquare, organismVector.at(i), directionalUtility, possibleCollisions, maxInteractionUtility, maxInteractionUtilityTarget);
                }
            }
            //check
            //if (possibleCollisions.size() == 2) {
                //std::cout << "stop here!";
            //}
            for (int i = 0; i < possibleCollisions.size(); i++) {
                for (int j = 0; j < directionalUtility.size(); j++) {
                    // ELIMINATION
                    float newPosX = this->getPosX() + stepSize * cos(2 * M_PI * (j + 0.5) / directionalUtility.size());
                    float newPosY = this->getPosY() + stepSize * sin(2 * M_PI * (j + 0.5) / directionalUtility.size());
                    if (std::pow(newPosX - possibleCollisions.at(i)->getPosX(), 2) + pow(newPosY - possibleCollisions.at(i)->getPosY(), 2) <
                        std::pow((this->getRadius() + possibleCollisions.at(i)->getRadius()), 2)) {

                        /* if (std::pow(this->getPosX() - possibleCollisions.at(i)->getPosX() + stepSize * cos(2 * M_PI * (j + 0.5) / directionalUtility.size()), 2)
                        + std::pow(this->getPosY() - possibleCollisions.at(i)->getPosX() + stepSize * sin(2 * M_PI * (j + 0.5) / directionalUtility.size()), 2)
                        < std::pow((this->getRadius() + possibleCollisions.at(i)->getRadius()), 2)) {
                        //angleBetween = angle(possibleCollisions.at(i), this);//was missing
                        directionalUtility[angleSorting(angleBetween)] = -10000;
                        */
                        directionalUtility.at(j) = -1000.0;
                    }
                }
            }
            //remain in grid
            for (int i = 0; i < directionalUtility.size(); i++) {
                if ((this->getPosX() + stepSize * cos(2 * M_PI * (i + 0.5) / directionalUtility.size()) > windowWidth - this->getRadius()) or
                    (this->getPosX() + stepSize * cos(2 * M_PI * (i + 0.5) / directionalUtility.size()) < 0 + this->getRadius()) or
                    (this->getPosY() + stepSize * sin(2 * M_PI * (i + 0.5) / directionalUtility.size()) > windowHeight - this->getRadius()) or
                    (this->getPosY() + stepSize * sin(2 * M_PI * (i + 0.5) / directionalUtility.size()) < 0 + this->getRadius())) {
                    directionalUtility.at(i) = -10000.0;
                }
            }

            //std::cout << " my directional utility is: ";
            //for (int i = 0; i < directionalUtility.size(); i++) {
             //   std::cout << directionalUtility.at(i) << "     ";
            //}
            //std::cout << " " << std::endl;

            maxDirectionalUtility = directionalUtility.at(0);
            maxDirectionalUtilityTarget = 0;
            bool noDirectionalUtility = true;
            for (int i = 0; i < directionalUtility.size(); i++) {
                if (directionalUtility.at(i) != 0.0) {
                    noDirectionalUtility = false;
                }
                if (maxDirectionalUtility < directionalUtility.at(i)) {
                    maxDirectionalUtility = directionalUtility.at(i);
                    maxDirectionalUtilityTarget = i;
                }
            }

            if (maxDirectionalUtility >= maxInteractionUtility) {
                if (not noDirectionalUtility) {
                    this->move(maxDirectionalUtilityTarget);
                }
            }
            else {
                //std::cout << "Interaction" << std::endl;
                //if (maxInteractionUtilityTarget != nullptr) {
                this->interact(maxInteractionUtilityTarget, organismVector);
                //} 
            }
        }
    }

}////VERY IMPORTANT: interact is not being called from the predator class 
//Issue 1) Is compute utility correct to the class?????
//Issue 2) Check if the correct inherited method is being called, possibly I would need to create a predator instance and call
// the compute utility method and interact method from there
	


/*/
void Fauna::update(std::vector<Organism*>& organismVector) {
    this->ageing(); // CHANGE TO DATE OF BIRTH 
    this->setEnergy(this->getEnergy() - this->getMetabolicRate());
    // with arbitrary 100 seconds (6000 frames ) max lifespan, arbitrary function with certain death at 6000 
    //Maybe separate function
    //a:delete the pointer
    //Predator* offspring = new Predator(79.0, 515.0, 10.0, 1, false, 60, 10, 1, 0, 600);//Above parameters cause program failure!
    
    if ((1.0 * (rand() % 100) < (100 * std::pow(((1 + this->getAge()) / 6000), 10)) or (this->getEnergy() <= 0))) {
        this->dies(organismVector);
    }
    
    for (int k = 0; k <= this->getSpeed(); k++) { // BEGINING OF TURN LOOP 

        float distSquare;
        float angleBetween;

        float currentUtility;

        float maxDirectionalUtility = 0;
        float maxInteractionUtility = 0;

        Organism* maxInteractionUtilityTarget = nullptr;
        int maxDirectionalUtilityTarget = 0;

        int currentIntegerDirection =0 ; 

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
                    currentUtility = computeUtility(distSquare, organismVector.at(i));
                    angleBetween = angle(organismVector.at(i), this);
                    currentIntegerDirection = angleSorting(angleBetween); 
                    directionalUtility[currentIntegerDirection] += currentUtility;
                    //Prototype for directional gradient of utility increase / MAYBE CHANGE DECREASE RATE ?   
                    for (int l = 1; l <= (angleSectionNumber / 4); l++) {
                        int testInteger =0 ;
                        testInteger = directionalUtility.size() ; 
                        testInteger = (((currentIntegerDirection + l) % angleSectionNumber)) ; 
                        directionalUtility[((currentIntegerDirection + l) % angleSectionNumber)] +=  (currentUtility / (l + 1));
                        testInteger = (((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)) ; 
                        directionalUtility[((currentIntegerDirection - l + angleSectionNumber ) % angleSectionNumber)] +=   (currentUtility / (l + 1));
                    }
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
            //std::cout << "Interaction" << std::endl;
            //this->interact(maxInteractionUtilityTarget, organismVector);
        }
    }

}////VERY IMPORTANT: interact is not being called from the predator class 
//Issue 1) Is compute utility correct to the class?????
//Issue 2) Check if the correct inherited method is being called, possibly I would need to create a predator instance and call
// the compute utility method and interact method from there
	/*/

/*/
struct GeneticInterval { 
    float SpeedRange [4] ; 
    float HungerSensitivityRange [4] ; 
    float MetabolicRateRange[4];
    float LustLevelRange[4];
    float VisionRangeRange[4];
    float PredatorAversionRange[4];
};
/*/
/*
float geneticsEngine(float parent1Trait , float parent2Trait, string traitName, sting faunaType){

    isPrey = (faunaType == "Prey");
    if (traitName == "Speed" ){
        if (isPrey){
            traitRange = 
        }
        else{

        }
    }
        if (traitName == "Speed" ){
        
    }
    return 0.0 ; 
}

*/


float geneticEngine (std::string speciesName, std::string traitName, float parent1TraitValue, float parent2TraitValue) {
    float offspringTraitValue = 0.0 ; 

    bool speciesFound = false ; 
    bool traitFound = false ; 

    std::vector<float> geneticTraitInterval; 

    int geneticRand = 0 ; 

    float parentsTraitValues [2] = {parent1TraitValue, parent2TraitValue}; 
    
    int i = 0 ; 
    while  (i < geneticDatabase.size() and not speciesFound) {
        if (geneticDatabase[i].speciesName == speciesName){
            speciesFound = true ; 
            int j = 0 ; 
            while (j < geneticDatabase[i].geneticTraitIntervals.size() and not traitFound) {
                if (geneticDatabase[i].geneticTraitIntervals[j].traitName == traitName) {
                    traitFound = true ; 
                    geneticTraitInterval = geneticDatabase[i].geneticTraitIntervals[j].traitRange; // = geneticDatabase[i].geneticTraitIntervals[j].traitRange ; 
                }
                j++ ;
            }
        }
        i++ ; 
    }

    if (traitFound and speciesFound){
        int alleleCounter = 0 ; 
        for(float parentTraitValue : parentsTraitValues){
            if (parentTraitValue >= geneticTraitInterval[0] and parentTraitValue < geneticTraitInterval[1] ){
                
            }
            else if (parentTraitValue >= geneticTraitInterval[1] and parentTraitValue < geneticTraitInterval[2]) {
                geneticRand = rand() % 2 ; 
                if (geneticRand == 1 ) {
                    alleleCounter ++ ; 
                }
            }
            else if (parentTraitValue >= geneticTraitInterval[2] and parentTraitValue < geneticTraitInterval[3]) {
                alleleCounter ++ ; 
            }
        }
        geneticRand = (rand() % 100); 
        std::cout << "alleleCounter is equal to " << alleleCounter << "corresponding to an interval between " << geneticTraitInterval[alleleCounter] << " and " << geneticTraitInterval[alleleCounter + 1] << "and random increment is " << geneticRand << " percent " <<  std::endl; 
        //offspringTraitValue = geneticTraitInterval[alleleCounter] + (geneticTraitInterval[alleleCounter + 1] - geneticTraitInterval[alleleCounter]) * geneticRand / 100.0;
        offspringTraitValue = geneticTraitInterval[alleleCounter] + (geneticTraitInterval[alleleCounter + 1] - geneticTraitInterval[alleleCounter]) * (0.5 + 0.5*std::pow(-1 + 2* geneticRand / 100.0,5 ));

        //FOR NOW UNIFORMLY, but can change distribution if fun, concentrated arround middle of the interval ? Making each of the 3 categories more distinct 
    }

    return offspringTraitValue ; 
}