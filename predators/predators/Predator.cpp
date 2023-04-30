#include "Predator.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "OrganicMaths.cpp"

Predator::Predator(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, int myAge, int myHungerLevel,
	float myMetabolicRate, int myLustLevel, float myVisionRange) : Fauna(myPosX, myPosY,myRadius, myEnergy, 
		mySex, mySpeed, myAge, myHungerLevel,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Red);
}

void Predator::update(std::vector<Organism*> organismVector) {
	std::cout << "I am a predator" << std::endl;
	
	float distSquare;
	float angleBetween;
	int bestDirection;
	float maxInteractionUtility;
	float currentUtility;
	float maxDirectionalUtility = 0;
	

	//Dis-intangle organism
	//Corresponds to the number of quadrants (360 degree slices) in the vision range
	const int directionalUtilitySize = 12;
	std::vector<float> directionalUtility(directionalUtilitySize,0);
	std::vector<Organism*> possibleCollisions;

	for (int i = 0; i < organismVector.size(); i++) {
		distSquare = distanceSquared(organismVector.at(i), this);
		if (distSquare < std::pow(Predator::getVisionRange() - organismVector.at(i)->getShape().getRadius(), 2)) {
			if (distSquare < std::pow(
				Predator::getShape().getRadius() + organismVector.at(i)->getShape().getRadius() + 2, 2)) {//range of interaction 2 pixels
				if (organismVector.at(i)->getType() == "Class Prey") {
					possibleCollisions.push_back(organismVector.at(i));
					currentUtility = computeUtility(distSquare, *organismVector.at(i));
					if (currentUtility > maxInteractionUtility) {
						maxInteractionUtility = currentUtility;
						bestDirection = i;
					}
				}
				else if (organismVector.at(i)->getType() == "Class Predator") {
					if (organismVector.at(i)->getSex() != Predator::getSex()) {
						possibleCollisions.push_back(organismVector.at(i));
						if (currentUtility > maxInteractionUtility) {
							maxInteractionUtility = currentUtility;
							bestDirection = i;
						}

					}
				}
			}
			else {
				angleBetween = angle(organismVector.at(i), this);
				currentUtility = computeUtility(distSquare, *organismVector.at(i));
				directionalUtility[angleSorting(angleBetween)] += currentUtility;
			}

		}
		for (int i = 0; i < directionalUtilitySize; i++) {
			for (int j = 0; j < possibleCollisions.size(); j++) {
				if(distSquare < std::pow(shape.getRadius() + j->getshape().getRadius(),2)){
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

float Predator::computeUtility(float distance, Organism organism) {
	return 3;
}

// NEED TO CHANGE HEADERS 
// energy radius Position Speed Sex age hungerlevel hungerSensitivity metabolicRate lustLevel 
//assuming visionRange is from 50 to 100  atan 
float Predator::computeUtility2(float distanceSquared, Organism* targetOrganism) {
    float distanceToInterraction;
    distanceToInterraction = sqrt(distanceSquared) - shape.getRadius() - targetOrganism->getRadius()
    float distancefactor;
    distancefactor= proximityEffectFactor(0, visionRange, 1, distanceToInterraction ) ; 
    If (targetOrganism->getType() == "prey"){
            float hungerFactor; 
            //1000 acts as placeholder for amount of energy at which indifference to food is total 
            hungerFactor = proximityEffectFactor(0, 1000, hungerSensitivity , energy ) ; 
        return hungerFactor*distancefactor ; 
        // effect of size or energy of target prey ? 
    }
    Else If ( (targetOrganism->getType() == "predator") and ( targetOrganism->getSex()!=  sex ) )  {
          float lustFactor; 
            //1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
            lustFactor = 1 - proximityEffectFactor(0, 1000, lustLevel , energy ) ; 
        // effect of size or energy of target mate ? 
        return lustFactor*distancefactor ; 
    }
    return 0.0; 
}