#include "Predator.h"
#include "Prey.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "OrganicMaths.h"

Predator::Predator(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, float myHungerSensitivity,
	float myMetabolicRate, float myLustLevel, float myVisionRange) : Fauna(myPosX, myPosY,myRadius, myEnergy, 
		mySex, mySpeed, myHungerSensitivity,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Red);
}

void Predator::update(std::vector<Organism*>& organismVector) {
	// std::cout << "I am a predator" << std::endl;

	Predator::ageing();

	for (int k = 0;k<Predator::getSpeed();k++){
	
	float distSquare;
	float angleBetween;
	int bestDirection;
	float maxInteractionUtility = 0;
	float currentUtility;
	float maxDirectionalUtility = 0;

	//Dis-intangle organism
	//Corresponds to the number of quadrants (360 degree slices) in the vision range
	const int directionalUtilitySize = 12;
	std::vector<float> directionalUtility(directionalUtilitySize,0);
	std::vector<Organism*> possibleCollisions;

	for (int i = 0; i < organismVector.size(); i++) {
		distSquare = distanceSquared(organismVector.at(i), this);
		if (distSquare < std::pow(Predator::getVisionRange() - organismVector.at(i)->getRadius(), 2)) {
			if (distSquare < std::pow(Predator::getRadius() + organismVector.at(i)->getRadius() + 2, 2)) {//range of interaction 2 pixels
				possibleCollisions.push_back(organismVector.at(i));
				if (Prey* myPrey = dynamic_cast<Prey*>(organismVector.at(i))) {
					currentUtility = computeUtility(distSquare, myPrey);
					if (currentUtility > maxInteractionUtility) {
						maxInteractionUtility = currentUtility;
						bestDirection = i;
					}
				}
				else if (Predator* myPredator = dynamic_cast<Predator*>(organismVector.at(i))) {
					if (myPredator->getSex() != Predator::getSex()) {
						if (currentUtility > maxInteractionUtility) {
							maxInteractionUtility = currentUtility;
							bestDirection = i;
						}

					}
				}
			}
			else {
				angleBetween = angle(organismVector.at(i), this);
				currentUtility = computeUtility(distSquare, organismVector.at(i));
				directionalUtility[angleSorting(angleBetween)] += currentUtility;
			}

		}
		for (int i = 0; i < directionalUtilitySize; i++) {
			for (int j = 0; j < possibleCollisions.size(); j++) {
				if(distSquare < std::pow(shape.getRadius() + possibleCollisions.at(j)->getRadius(),2)){
					directionalUtility[i] = -10000;//avoid collision
				}
			}
		}
		//Determine Maximum Utility and index
		for (int i = 0; i < directionalUtilitySize; i++) {
			if (directionalUtility[i] > maxDirectionalUtility) {
				maxDirectionalUtility = directionalUtility[i];
				bestDirection = i;
			}
		}

		if (maxDirectionalUtility > maxInteractionUtility) {
			//move towards best direction
			Fauna::move(bestDirection);
		}
		else {
			//move towards best interaction
		}
	}
	}
}

//float Predator::computeUtility(float distance, Organism organism) {
//	return 3;
//}

// NEED TO CHANGE HEADERS 
// energy radius Position Speed Sex age hungerlevel hungerSensitivity metabolicRate lustLevel 
//assuming visionRange is from 50 to 100  atan 
float Predator::computeUtility(float distanceSquared, Organism* targetOrganism) {
	if (distanceSquared == 0.0) {
		//get utility of interaction
	}
	else {
		float distanceToInterraction;
		float distancefactor;

		distanceToInterraction = sqrt(distanceSquared) - Predator::getRadius() - targetOrganism->getRadius();//U used getRadius :p

		distancefactor = proximityEffectFactor(0, Predator::getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			float hungerFactor;
			//1000 acts as placeholder for amount of energy at which indifference to food is total 
			hungerFactor = proximityEffectFactor(0, 1000, Predator::getHungerSensitivity(), Predator::getEnergy());
			return hungerFactor * distancefactor;
			// effect of size or energy of target prey ? 
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			if (myPredator->getSex() != Predator::getSex()) {
				float lustFactor;
				//1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
				lustFactor = 1 - proximityEffectFactor(0, 1000, Predator::getLustLevel(), Predator::getEnergy());
				// effect of size or energy of target mate ? 
				return lustFactor * distancefactor;
			}
		}
		//return 0.0;
	}
	//MAYBE a stragtegy for predators to go near FLora and wait for prey to come near them ?
	/*float Predator::computeUtility(float distanceSquared, Flora* targetOrganism) {
		float distanceToInterraction;
		float distancefactor;
		distanceToInterraction = sqrt(distanceSquared) - Predator::getShape().getRadius() - targetOrganism->getShape().getRadius();//U used getRadius :p

		distancefactor = proximityEffectFactor(0, Predator::getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

		return distancefactor ;
	}
	*/
}

void Predator::interact(Organism* targetOrganism, std::vector<Organism*>& organismVector) {
	if(Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)){
		float energyAbsorbtionSpeed;
		energyAbsorbtionSpeed = 10.0;
		// CLASS CONST OR ATTRIBUTE ? Maximum amount of energy the predator can take from a prey in one interaction 
		float absorbedEnergy;
		absorbedEnergy = std::min(energyAbsorbtionSpeed, targetOrganism->getEnergy());
		targetOrganism->setEnergy(targetOrganism->getEnergy() - absorbedEnergy);
		Predator::setEnergy(Predator::getEnergy() + absorbedEnergy);
	}
	else{
		Predator* myPred = dynamic_cast<Predator*>(targetOrganism);
		float posX = static_cast<float>(rand() % 1000);
		float posY = static_cast<float>(rand() % 1000);
		float radius = static_cast<float>(rand() % 10 + 5);
		float energy = rand() % 100 + 1;
		bool sex = rand() % 2 == 0 ? true : false;
		int speed = rand() % 10 + 1;
		int hungerLevel = rand() % 100 + 1;
		float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
		int lustLevel = rand() % 100 + 1;
		int visionRange = rand() % 100 + 1;
		// CHECK EMPTY SPACE 
		Predator* offspring = new Predator(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange);
		organismVector.push_back(offspring);
	}
}