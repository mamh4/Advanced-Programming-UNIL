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

//Takes the organism vector as parameter and removes itself from the vector i.e. death
void Fauna::die(std::vector<Organism*>& organismVector) {
    this->generateDeathReport();
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

void Fauna::mature() {
    age++;
    this->setRadius(this->getRadius() + (1/this->age * 0.01));

    if (Predator* myPredator = dynamic_cast<Predator*>(this)) {
        totalAgePredator += 1;
    }
    else if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
        totalAgePrey += 1;
    }
}

//First the organism ages by 1. The energy is reduced by the metabolic rate. If the energy is less than 0, the organism die.
//If the organism is fertile, it has a chance to reproduce.
//There is probability of 1% per year of life that the organism dies.
//The probability of death increases with age.
//The fauna then iterates through the organism vector, identifies the set of possible actions and assigns utility to each action.
//The action with the highest utility is then executed.
//If the action is interaction the fauna will not move and will pursue the interaction.
//If the action is to move , the fauna will move in the direction with the highest utility.
//Color changes based on energy.

void Fauna::update(std::vector<Organism*>& organismVector) {
    this->mature(); 
    this->setEnergy(this->getEnergy() - std::min(this->getMetabolicRate(), this->getEnergy()));


    //organism dies if energy is less than 0. In addition, The probability of dying due to old age increases as age increases. Could use De'Moivre's Law in the future.
    if ((1.0 * (rand() % 100) < (100 * std::pow(((1 + this->getAge()) / 6000), 10)) or (this->getEnergy() <= 0))) {
        this->die(organismVector);

    }
    else {
        int minFertilityAge = 50;
        int maxFertilityAge = 100;
        //fertility check, only between age 50 and 100 and becomes increasingly difficult as they age.
        if ((1.0 * (rand() % 100) < std::max(0.0, (100 * std::pow(((this->getAge() - minFertilityAge) / (maxFertilityAge - minFertilityAge)), 10)))) and 
            not this->getFertile()) {
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
        //Fauna take as many turns as their speed allows.
        for (int k = 0; k <= this->getSpeed(); k++) { // BEGINING OF TURN LOOP 

            float distSquare;
            float angleBetween = 0.0;

            float maxDirectionalUtility = 0;
            float maxInteractionUtility = 0.0;

            Organism* maxInteractionUtilityTarget = nullptr;
            int maxDirectionalUtilityDirection = 0;

            std::vector<float> directionalUtility(angleSectionNumber, 0.0);
            std::vector<bool> directionalSelector(angleSectionNumber, true);
            std::vector<Organism*> possibleCollisions;

            for (int i = 0; i < organismVector.size(); i++) {
                distSquare = distanceSquared(organismVector.at(i), this);
                if ((distSquare > 0.0001) and (distSquare < std::pow(this->getVisionRange() - organismVector.at(i)->getRadius(), 2))) {
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
                        directionalSelector.at(j) = false;
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
                    directionalSelector.at(i) = false;
                }
            }
            maxDirectionalUtility = 0.0;
            bool noDirectionalUtility = true;
            bool validDirectionFound = false;

            directionalUtility;
            possibleCollisions;
            directionalSelector;

            //Handle boundary conditions: 1) All directions generate the same utility
            //If the directional utility of any direction is not equal to the first then this boundary case does not occur.
            for (int i = 0; i < directionalUtility.size(); i++) {
                if (directionalUtility.at(i) != directionalUtility[1]) {
                    noDirectionalUtility = false;
                    break;
                }
            }

            //Evaluate the maximum valid directional utility
            for (int i = 0; i < directionalUtility.size(); i++) {
                if (maxDirectionalUtility <= directionalUtility.at(i) and directionalSelector.at(i)) {
                    maxDirectionalUtility = directionalUtility.at(i);
                    maxDirectionalUtilityDirection = i;
                }
            }
            //std::cout << "Max Directional Utility " << maxDirectionalUtility << " ,Max Interaction utillity " << maxInteractionUtility << std::endl;
                //boundary condition: all directions generate the same utility

            //If this is the case, move in a random viable direction.
            if (noDirectionalUtility) {
                //viable directions vector
                std::vector<int>* viableDirections = new std::vector<int>();
                for (int i = 0; i < directionalUtility.size(); i++) {
                    if (directionalSelector.at(i)) {
                        viableDirections->push_back(i);
                    }
                }
                if (!viableDirections->empty()) {
                    int randomViableDirectionByIndex = rand() % viableDirections->size();
                    //this->move(viableDirections->at(randomViableDirectionByIndex)); DISABLED FOR NOW
                    //std::cout << "Move Randomly, all are the same" << std::endl;
                }
            }
            else if (maxDirectionalUtility >= maxInteractionUtility) {
                this->move(maxDirectionalUtilityDirection);
                //std::cout << "Direction Wins: " << maxDirectionalUtilityDirection <<std::endl;
            }
            else if (maxDirectionalUtility < maxInteractionUtility) {
                this->interact(maxInteractionUtilityTarget, organismVector);
               // std::cout << "Interaction Wins" << std::endl;
            }
            else {
                //std::cout << "SOMETHING IS WRONG WITH UTILITY" << std::endl;
            }
        }
            

            /*



            for (int i = 0; i < directionalUtility.size(); i++) {
                if (directionalUtility.at(i) > 0.0) {
                    noDirectionalUtility = false;
                }
                if (not validDirectionFound and directionalSelector.at(i)){
                    validDirectionFound = true ; 
                    if (maxDirectionalUtility <= directionalUtility.at(i)) {
                        maxDirectionalUtility = directionalUtility.at(i) ;
                    }
                }
            }
            if (validDirectionFound){
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

           if (maxDirectionalUtility >= maxInteractionUtility) { // O by default, eliminates negative utility interactions 
               if (noDirectionalUtility and validDirectionFound) {
                   //RANDOM PICK OF DIRECTION IF NO CLEAR MAXIMUM
                   int numberOfValidMaxUtilityDirections = 0;
                   for (int i = 0; i < directionalSelector.size(); i++) {
                       if (directionalSelector.at(i)) {
                           numberOfValidMaxUtilityDirections++;
                       }
                   }
                   int decsionalCounter = 0;
                   int decisionalRand = 0;
                   decisionalRand = (rand() % numberOfValidMaxUtilityDirections);
                   for (int i = 0; i < directionalSelector.size(); i++) {
                       if (directionalSelector.at(i)) {
                           if (decsionalCounter == decisionalRand) {
                               this->move(i);
                               decsionalCounter++;
                           }
                           else {
                               decsionalCounter++;
                           }
                       }
                       else {
                       }
                   }
               }
               else if (noDirectionalUtility and validDirectionFound) {
                   this->move(maxDirectionalUtility);
               }
            }
            else {
                this->interact(maxInteractionUtilityTarget, organismVector);
            */
            
            
    

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
// Takes the genetic traits of the parents and returns the genetic traits of the offspring


//Collects the statistics of dead organisms to view in the death report
void Fauna::generateDeathReport() {
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
						summaryStatistics[i].traitSummaryStatisticVector[j].sumOfAgesAtDeath[classIndex] += this->getAge() / frameRate; 
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