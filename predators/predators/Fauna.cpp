#include "Fauna.h"
#include <SFML/Graphics.hpp>
#include "OrganicMaths.h"
#include "Predator.h"
#include "Prey.h"
#include "organicStats.h"
#include "GeneticIntervals.h"
#include <string>
#include "Gameboard.h"
#pragma once


//Parent class of prey and predators
Fauna::Fauna(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
    int mySpeed, float myHungerSensitivity, float myMetabolicRate,
    float myLustLevel, float myVisionRange) : Organism(myPosX, myPosY, myRadius, myEnergy) {

    sex = mySex;
    speed = mySpeed;
    age = 0;
    numberOfOffspring = 0;
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

void Fauna::setNumberOfOffspring(int numberOfOffspring) {
    this->numberOfOffspring = numberOfOffspring;
}

int Fauna::getNumberOfOffspring() {
    return this->numberOfOffspring;
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


void Fauna::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget) {
}

//Takes the organism vector as parameter and removes itself from the vector
void Fauna::dies(std::vector<Organism*>& organismVector) {
    this->deathReport();
    if (Predator* myPredator = dynamic_cast<Predator*>(this)) {
        numberOfPredators -= 1;
        if (this->sex) {
            numberOfFemalePredator -= 1;
            if (this->fertile) {
                numberOfFertileFemalePredator -= 1;
            }
        }
        else {
            numberOfMalePredator -= 1;
            if (this->fertile) {
                numberOfFertileMalePredator -= 1;
            }
        }
    }
    else if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
        numberOfPrey -= 1;
        if (this->sex) {
            numberOfFemalePrey -= 1;
            if (this->fertile) {
                numberOfFertileFemalePrey -= 1;
            }
        }
        else {
            numberOfMalePrey -= 1;
            if (this->fertile) {
                numberOfFertileMalePrey -= 1;

            }
        }
    }
    auto it = std::remove(organismVector.begin(), organismVector.end(), this);
    organismVector.erase(it, organismVector.end());
    delete this;
}

void Fauna::move(int directionIndicator) {

    float energyCostOfMovement;
    energyCostOfMovement = std::min(0.1f, this->energy);

    this->setPosX(this->getPosX() + stepSize * cos((directionIndicator + 0.5) * M_PI * 2 / angleSectionNumber));
    this->setPosY(this->getPosY() + stepSize * sin((directionIndicator + 0.5) * M_PI * 2 / angleSectionNumber));
    this->setEnergy(this->getEnergy() - energyCostOfMovement);
}

void Fauna::ageing() {
    age++;

    if (Predator* myPredator = dynamic_cast<Predator*>(this)) {
        totalAgePredator += 1;
    }
    else if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
        totalAgePrey += 1;
    }
}


void Fauna::update(std::vector<Organism*>& organismVector) {
    this->ageing(); 
    this->setEnergy(this->getEnergy() - std::min(this->getMetabolicRate(), this->getEnergy()));


    float childRadius = 3.0;
    float adultRadius = 6.0; 
    int maxAge = 12000; 

    if ((1.0 * (rand() % 100) < (100 * std::pow(((1 + this->getAge()) / 6000), 10)) or (this->getEnergy() <= 0))) {
        this->dies(organismVector);

    }
    else {
        int minFertilityAge = 50;
        int maxFertilityAge = 100;
        if ((1.0 * (rand() % 100) < std::max(0.0, (100 * std::pow(((this->getAge() - minFertilityAge) / (maxFertilityAge - minFertilityAge)), 10)))) and not this->getFertile()) {
            this->setFertile(true);

            if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
                if (this->getSex()) {
                    numberOfFertileFemalePrey += 1;
                }
                else {
                    numberOfFertileMalePrey += 1;
                }
            }
            else if (Predator* myPredator = dynamic_cast<Predator*>(this)) {
                if (this->getSex()) {
                    numberOfFertileFemalePredator += 1;
                }
                else {
                    numberOfFertileMalePredator += 1;
                }
              
			}

        }
        for (int k = 0; k <= this->getSpeed(); k++) { // BEGINING OF TURN LOOP 

            int boostingMomentTracker = 0 ; 
            std::string boostingReport = "Boosting report: "; 

            float distSquare;
            float angleBetween = 0.0;

            float maxDirectionalUtility = 0;
            //float maxInteractionUtility = -1000.0;
            float maxInteractionUtility = 0.0;

            Organism* maxInteractionUtilityTarget = nullptr;
            int maxDirectionalUtilityTarget = 0;

            std::vector<float> directionalUtility(angleSectionNumber, 0.0);
            std::vector<bool> directionalSelector(angleSectionNumber, true);
            std::vector<Organism*> possibleCollisions;

            for (int i = 0; i < organismVector.size(); i++) {
                //TRY organismVector.at(i)->getRadius() print maybe
                distSquare = distanceSquared(organismVector.at(i), this);//organismvector at get radius is read as an uninitialised organism
                if ((distSquare > 0.0001) and (distSquare < std::pow(this->getVisionRange() - organismVector.at(i)->getRadius(), 2))) {
                    //   this->computeUtility(distSquare, organismVector.at(i), directionalUtility, maxDirectionalUtility , maxDirectionalUtilityTarget , possibleCollisions, maxInteractionUtility , maxInteractionUtilityTarget ); 
                    this->computeUtility(distSquare, organismVector.at(i), directionalUtility, possibleCollisions, maxInteractionUtility, maxInteractionUtilityTarget);
                }
            }

            for (int i = 0; i < possibleCollisions.size(); i++) {
                for (int j = 0; j < directionalUtility.size(); j++) {
                    // ELIMINATION
                    float newPosX = this->getPosX() + stepSize * cos(2 * M_PI * (j + 0.5) / directionalUtility.size());
                    float newPosY = this->getPosY() + stepSize * sin(2 * M_PI * (j + 0.5) / directionalUtility.size());
                    if (std::pow(newPosX - possibleCollisions.at(i)->getPosX(), 2) + pow(newPosY - possibleCollisions.at(i)->getPosY(), 2) <
                        std::pow((this->getRadius() + possibleCollisions.at(i)->getRadius()), 2)) {
                        directionalSelector.at(j) = false ; 
                    }
                }
            }
            //remain in grid
            for (int i = 0; i < directionalUtility.size(); i++) {
                if ((this->getPosX() + stepSize * cos(2 * M_PI * (i + 0.5) / directionalUtility.size()) > windowWidth - this->getRadius()) or
                    (this->getPosX() + stepSize * cos(2 * M_PI * (i + 0.5) / directionalUtility.size()) < 0 + this->getRadius()) or
                    (this->getPosY() + stepSize * sin(2 * M_PI * (i + 0.5) / directionalUtility.size()) > windowHeight - this->getRadius()) or
                    (this->getPosY() + stepSize * sin(2 * M_PI * (i + 0.5) / directionalUtility.size()) < 0 + this->getRadius())) {
                    //directionalUtility.at(i) = -10000.0;
                   directionalSelector.at(i) = false ; 
                }
            }
            
            
            maxDirectionalUtility = 0.0 ; 
            bool noDirectionalUtility = true;
            bool validDirectionFound = false ; 
            for (int i = 0; i < directionalUtility.size(); i++) {
                if (directionalUtility.at(i) != 0.0) {
                    noDirectionalUtility = false; // CHECK VALIDITY OR NOT ? 
                }
                if (not validDirectionFound and directionalSelector.at(i)){
                    validDirectionFound = true ; 
                    maxDirectionalUtility = directionalUtility.at(i) ; 
                }
            }
            if (validDirectionFound){ // MAYBE ADD VALUES WITH COMPARABLE UTILITIES TO THE LIST ? INSTEAD OF JUST THE EQUAL ONES ? STANDARD DEVIATION KIND OF 
                for (int i = 0; i < directionalUtility.size(); i++) {
                    if (directionalUtility.at(i) != 0.0) {
                        noDirectionalUtility = false;
                    }
                    if (maxDirectionalUtility < directionalUtility.at(i) and directionalSelector.at(i)) { 
                        maxDirectionalUtility = directionalUtility.at(i);

                        for (int j = 0 ; j < i ; j ++ ){
                            directionalSelector.at(j) = false; 
                        }
                    }
                    else if (maxDirectionalUtility == directionalUtility.at(i) and directionalSelector.at(i)) {
                    }
                    else if (maxDirectionalUtility > directionalUtility.at(i) and directionalSelector.at(i)) {
                        directionalSelector.at(i) = false; 
                    }
                }
            }

           if ((maxDirectionalUtility >= maxInteractionUtility)) { // O by default, eliminates negative utility interactions 
                if (not noDirectionalUtility and validDirectionFound) {
                    //RANDOM PICK OF DIRECTION
                    int numberOfValidMaxUtilityDirections  = 0 ;
                    boostingReport = boostingReport +  "I am looking for my next move " ; 
                    for (int i = 0; i < directionalSelector.size(); i++) {
                        if (directionalSelector.at(i)){
                            numberOfValidMaxUtilityDirections ++ ; 
                        }
                    }
                    boostingReport = boostingReport +  " - the number of valid directions with max utility is : " + std::to_string( numberOfValidMaxUtilityDirections)  ; 
                    int decsionalCounter = 0 ;                     
                    int decisionalRand = 0 ; 
                    decisionalRand = (rand() % numberOfValidMaxUtilityDirections) ; 
                    boostingReport = boostingReport +  " - the random number is : " +  std::to_string(decisionalRand) ; 
                    for (int i = 0; i < directionalSelector.size(); i++){
                        if (directionalSelector.at(i)){
                            boostingReport = boostingReport + "   - the direction " +  std::to_string(i) + "is valid -  "; 
                            if (decsionalCounter == decisionalRand){
                                this->move(i);
                                decsionalCounter ++ ; 
                                boostingMomentTracker ++ ; 
                                boostingReport = boostingReport +  "   - counter is equal to. " +  std::to_string(decsionalCounter)  + "  matching the random number " +   std::to_string(decisionalRand) + "   I am moving towards   "  + std::to_string(  i ) +  "  -  " ; 
                            }
                            else {
                                decsionalCounter ++ ; 
                                boostingReport = boostingReport + "  -  counter is equal to.  " +  std::to_string( (decsionalCounter -1)  ) + "   NOT matching the random number.  " +  std::to_string( decisionalRand ) +  "   I am NOT moving towards    "  + std::to_string( i  ) +  "  -  " ; 
                            }
                        }
                        else{
                            boostingReport = boostingReport + "   - the direction "  + std::to_string( i ) + "is NOT valid -  ";
                        }
                    } 
                }
            }
            else {
                this->interact(maxInteractionUtilityTarget, organismVector);
            }

    }

    float maxEnergy = 200.0; 
    sf::CircleShape newShape;
    newShape = this->getShape(); 
    int newColorCode ;
    float approximateColorCode ; 
    if (this->getEnergy() <= 0 ){
        approximateColorCode = 100.0 ; 
    }
    else if (this->getEnergy()  <=  maxEnergy * this->getRadius() ) {
        approximateColorCode = 150.0 - (this->getEnergy()*150.0/(maxEnergy * this->getRadius())) ; 
    }
    else {
        approximateColorCode = 0.0 ; 
    }
    newColorCode = static_cast<int> (approximateColorCode ); 
    newColorCode = newColorCode % 256 ; 
    uint8_t actualColorCode ; 
    actualColorCode = newColorCode ; 

    if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
        newShape.setFillColor(sf::Color::Color( actualColorCode , actualColorCode, 255 , 255 )); 

    }
    else if (Predator* myPredator = dynamic_cast<Predator*>(this)) {
        newShape.setFillColor(sf::Color::Color( 255 ,actualColorCode , actualColorCode , 255 )); 

    }
    newShape.setOutlineThickness (1.0) ; 
    if (this->getSex()) {
         newShape.setOutlineColor(sf::Color::Color(255, 255, 255, 150)) ; 
    }
    else {
         newShape.setOutlineColor(sf::Color::Color(0, 0, 0, 0)) ; 
    }

    this->setShape(newShape);
    }
}

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
        offspringTraitValue = geneticTraitInterval[alleleCounter] + (geneticTraitInterval[alleleCounter + 1] - 
            geneticTraitInterval[alleleCounter]) * (0.5 + 0.5*std::pow((-1 + 2* geneticRand / 100.0) ,5 ));
    }

    return offspringTraitValue ; 
}


void Fauna::deathReport() {
	std::string currentSpecies; 
	std::vector<std::string> traitNameList ; 
	std::vector<float> traitValueList ; 
	if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
		currentSpecies = "Prey"; 
		traitNameList = {"Speed", "Hunger Sensitivity", "Metabolic Rate", "Lust Level", "Vision Range", "Predator Aversion"}; 
		traitValueList =  {1.0f*myPrey->getSpeed(), myPrey->getHungerSensitivity(), myPrey->getMetabolicRate(), 
            myPrey->getLustLevel(), myPrey->getVisionRange(), myPrey->getPredatorAversion()}; 
	}
	if (Predator* myPredator = dynamic_cast<Predator*>(this)) {
		currentSpecies = "Predator"; 
		traitNameList = {"Speed", "Hunger Sensitivity", "Metabolic Rate", "Lust Level", "Vision Range"}; 
		traitValueList =  {1.0f*myPredator->getSpeed(), myPredator->getHungerSensitivity(), myPredator->getMetabolicRate(), 
            myPredator->getLustLevel(), myPredator->getVisionRange()}; 
	}
	std::string currentTrait; 
	float currentValue ; 
	int classIndex = 0; 
	for (int k = 0; k < traitNameList.size() ; k++){
		int i = 0 ; 
		bool speciesFound = false ; 
		currentTrait = traitNameList[k] ; 
		currentValue = traitValueList[k] ; 
		while  (i < geneticDatabase.size() and not speciesFound) {
			if (geneticDatabase[i].speciesName == currentSpecies){ 
				speciesFound = true ; 
				int j = 0 ; 
                bool traitFound = false; 
				while (j < geneticDatabase[i].geneticTraitIntervals.size() and not traitFound) {
					if (geneticDatabase[i].geneticTraitIntervals[j].traitName == currentTrait) {
						traitFound = true ; 
						// TEST FOR CLASSINDEX HERE :) 
						if (currentValue >= 1.0f*geneticDatabase[i].geneticTraitIntervals[j].traitRange[0] and 
                            currentValue < 1.0f*geneticDatabase[i].geneticTraitIntervals[j].traitRange[1] ){
							classIndex = 0 ; 
						}
						else if (currentValue >= 1.0f*geneticDatabase[i].geneticTraitIntervals[j].traitRange[1] and 
                            currentValue < 1.0f*geneticDatabase[i].geneticTraitIntervals[j].traitRange[2]) {
							classIndex = 1 ; 
						}
						else if (currentValue >= 1.0f*geneticDatabase[i].geneticTraitIntervals[j].traitRange[2] and 
                            currentValue < 1.0f*geneticDatabase[i].geneticTraitIntervals[j].traitRange[3]) {
							classIndex = 2 ;
						}
					}
					j++ ;
				}
			}
			i++ ; 
		}
		if (classIndex == 0 or classIndex == 1 or classIndex == 2){
			i=0 ; 
			speciesFound = false ; 
			while (i < summaryStatistics.size() and not speciesFound) {
				if (summaryStatistics[i].speciesName == currentSpecies){
					speciesFound = true ; 
					int j = 0 ; 
					bool traitFound = false; 
					while (j < summaryStatistics[i].traitSummaryStatisticVector.size() and not traitFound) {
						if (summaryStatistics[i].traitSummaryStatisticVector[j].traitName == currentTrait) {
						traitFound = true ; 
						summaryStatistics[i].traitSummaryStatisticVector[j].population[classIndex] += 1.0 ; 
						summaryStatistics[i].traitSummaryStatisticVector[j].sumOfAgesAtDeath[classIndex] += this->getAge() ; 
						summaryStatistics[i].traitSummaryStatisticVector[j].sumOfOffsprings[classIndex] += this->getNumberOfOffspring() ; 
						}
					j++ ;
					}
				}
				i++; 
			}
		}
	}
}