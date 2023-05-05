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
/*
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
*/
// NEED TO CHANGE HEADERS 
// energy radius Position Speed Sex age hungerlevel hungerSensitivity metabolicRate lustLevel 
//assuming visionRange is from 50 to 100  atan 

/*/
void Predator::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility,
	float& maxDirectionalUtility , int maxDirectionalUtilityTarget , std::vector<Organism*>& possibleCollisions, 
	float& maxInteractionUtility , Organism*& maxInteractionUtilityTarget ) {
/*/
void Predator::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility , std::vector<Organism*>& possibleCollisions, 
	float& maxInteractionUtility , Organism*& maxInteractionUtilityTarget ) {
    
	float currentUtility = 0 ; 
    float angleBetween = 0 ;
    int currentIntegerDirection =0 ; 

    float baseReproductionEnergyCost;
	baseReproductionEnergyCost = 250.0;

    float energyAbsorbtionSpeed;
	energyAbsorbtionSpeed = 10.0;

    angleBetween = angle( this, targetOrganism);
    currentIntegerDirection = angleSorting(angleBetween); 

    if (distanceSquared < std::pow(this->getRadius() + targetOrganism->getRadius() + rangeOfInteraction, 2)) {
        possibleCollisions.push_back(targetOrganism);
        if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {

            currentUtility = std::min( myPrey->getEnergy(), energyAbsorbtionSpeed); 
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			// CHECK 
			if ((this->getSex() != myPredator->getSex()) and this->getFertile() and myPredator->getFertile() and (myPredator->getEnergy() > baseReproductionEnergyCost)) {

                if (this->getEnergy() <= baseReproductionEnergyCost){
                    // ARBITRARY 250
                    currentUtility = - baseReproductionEnergyCost; 
                } 
                else{
                    // ARBITRARY 250
					currentUtility = baseReproductionEnergyCost;
                }
			}
		}
		else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
		}
        //currentUtility = computeUtility(0.0, organismVector.at(i));  NEEDS TO BE IMPLEMENTED 
        // Arbitrarily distance 0.0 to transmit that it is utility of an interaction
    if (currentUtility > maxInteractionUtility) { // HANDLE PREDATOR SEEN BY PREY EXCEPTION HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            maxInteractionUtility = currentUtility;
            maxInteractionUtilityTarget = targetOrganism;
        }
    }
	else {
		float distanceToInterraction;
		float distancefactor;


		distanceToInterraction = sqrt(distanceSquared) - this->getRadius() - targetOrganism->getRadius();//U used getRadius :p

		distancefactor = proximityEffectFactor(0, this->getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			float hungerFactor;
			//1000 acts as placeholder for amount of energy at which indifference to food is total 
			hungerFactor = proximityEffectFactor(0, 1000, this->getHungerSensitivity(), this->getEnergy());
			currentUtility =  std::min( myPrey->getEnergy(), energyAbsorbtionSpeed) * hungerFactor * distancefactor;
			// effect of size or energy of target prey ? 
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			if ((this->getSex() != myPredator->getSex()) and this->getFertile() and myPredator->getFertile() and (myPredator->getEnergy() > baseReproductionEnergyCost)) {
                if (not this->getEnergy() <= baseReproductionEnergyCost){
                    float lustFactor;
				    //1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
				    //lustFactor =  1 - proximityEffectFactor(0, 1000, Predator::getLustLevel(), Predator::getEnergy());
				    lustFactor = 1 - proximityEffectFactor(0, 1000, this->getLustLevel(), this->getEnergy());
				    // effect of size or energy of target mate ? 
				    currentUtility =  baseReproductionEnergyCost * lustFactor * distancefactor;
                } 

			}
		}
        else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
		}
    directionalUtility[currentIntegerDirection] += currentUtility;
//	if ( directionalUtility[currentIntegerDirection] > maxDirectionalUtility ) { 
//		maxDirectionalUtility = directionalUtility[currentIntegerDirection] ; 
//		maxDirectionalUtilityTarget = currentIntegerDirection ; 
//	 } 
    for (int l = 1; l <= (angleSectionNumber / 4); l++) {
                            int testInteger =0 ;
                            testInteger = directionalUtility.size() ; 
                            testInteger = (((currentIntegerDirection + l) % angleSectionNumber)) ; 
                            directionalUtility[((currentIntegerDirection + l) % angleSectionNumber)] +=  (currentUtility / (l + 1));
							//if ( directionalUtility[((currentIntegerDirection + l) % angleSectionNumber)] > maxDirectionalUtility ) { 
							//	maxDirectionalUtility = directionalUtility[((currentIntegerDirection + l) % angleSectionNumber)] ; 
							//	maxDirectionalUtilityTarget = ((currentIntegerDirection + l) % angleSectionNumber) ; 
	 						//} 
                            testInteger = (((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)) ; 
                            directionalUtility[((currentIntegerDirection - l + angleSectionNumber ) % angleSectionNumber)] +=   (currentUtility / (l + 1));
							//if ( directionalUtility[((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)] > maxDirectionalUtility ) { 
							//	maxDirectionalUtility = directionalUtility[((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)] ; 
							//	maxDirectionalUtilityTarget = ((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber) ; 
	 						//} 
                        }
	}
}

/*/
float Predator::computeUtility(float distanceSquared, Organism* targetOrganism) {
	if (distanceSquared == 0.0) {
		//TO DO GET UTILITY OF INTERACTION.

		return 5.0;
	}
	else {
		float distanceToInterraction;
		float distancefactor;

		distanceToInterraction = sqrt(distanceSquared) - this->getRadius() - targetOrganism->getRadius();//U used getRadius :p

		distancefactor = proximityEffectFactor(0, this->getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			float hungerFactor;
			//1000 acts as placeholder for amount of energy at which indifference to food is total 
			hungerFactor = proximityEffectFactor(0, 1000, this->getHungerSensitivity(), this->getEnergy());
			return hungerFactor * distancefactor;
			// effect of size or energy of target prey ? 
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			if (this->getSex() != myPredator->getSex()) {
				float lustFactor;
				//1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
				//lustFactor =  1 - proximityEffectFactor(0, 1000, Predator::getLustLevel(), Predator::getEnergy());
				lustFactor =2*( 0.5 - proximityEffectFactor(0, 1000, this->getLustLevel(), this->getEnergy()));
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

void Predator::interact(Organism* targetOrganism, std::vector<Organism*>& organismVector) {
	if(Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)){
		float energyAbsorbtionSpeed;
		energyAbsorbtionSpeed = 10.0;
		// CLASS CONST OR ATTRIBUTE ? Maximum amount of energy the predator can take from a prey in one interaction 
		float absorbedEnergy;
		absorbedEnergy = std::min(energyAbsorbtionSpeed, targetOrganism->getEnergy());
		targetOrganism->setEnergy(targetOrganism->getEnergy() - absorbedEnergy);
		this->setEnergy(this->getEnergy() + absorbedEnergy);
	}
	else if (Predator* myPred = dynamic_cast<Predator*>(targetOrganism)) {
			//NEW!! Age must be greater than 30 to reproduce
		std::cout << "Reproduction just happened " << std::endl; 
			float baseReproductionEnergyCost;
			baseReproductionEnergyCost = 250.0;
			float radius = 5;//static_cast<float>(rand() % 10 + 5);
			float energy = 100;//rand() % 100 + 1;
			bool sex = false;//rand() % 2 == 0 ? true : false;
			int speed = 3000;//rand() % 10 + 1;
			float hungerSensitivity = 1;//rand() % 100 + 1;
			float metabolicRate = 1;//static_cast<float>(rand() % 10 + 1) / 10.0f;
			int lustLevel = 50;//rand() % 100 + 1;
			int visionRange = 300; //rand() % 100 + 1;
			this->setEnergy(this->getEnergy() - baseReproductionEnergyCost);
			targetOrganism->setEnergy(targetOrganism->getEnergy() - baseReproductionEnergyCost);
			// CHECK EMPTY SPACE
			float childRadius = 5.0 ; 
			float posXBirthPlace = (this->getPosX() + targetOrganism->getPosX() )/ 2.0  ; // avg of parents position 
			float posYBirthPlace = (this->getPosY() + targetOrganism->getPosY() )/ 2.0  ; // avg of parents position 
			bool validBirthPlace = false; 
			float posXProspectiveBirthPlace = posXBirthPlace; 
			float posYProspectiveBirthPlace = posYBirthPlace; 
			bool creatureCollision ;
			bool wallCollision ; 

			const int limitNumberOfSteps = 20 ; 
			int numberOfSteps = 1;
			while ( (numberOfSteps <= limitNumberOfSteps ) and not validBirthPlace ) {
				int newAngleSectionNumber ; 
				int j = 0 ; 
				newAngleSectionNumber = static_cast<int> ((  M_PI * limitNumberOfSteps * stepSize / childRadius )); 
				while ( (j < newAngleSectionNumber ) and not validBirthPlace ) {
					std::cout << " testing angle " << numberOfSteps << "at angle " << j << "out of "<< newAngleSectionNumber << std::endl;
					// test location 
					posXProspectiveBirthPlace = posXBirthPlace + numberOfSteps *stepSize *cos(2*M_PI* j / newAngleSectionNumber) ;
					posYProspectiveBirthPlace = posYBirthPlace + numberOfSteps *stepSize *sin(2*M_PI* j / newAngleSectionNumber) ;
					creatureCollision = false; 
					wallCollision = false ; 
				
					if ( (posXProspectiveBirthPlace > 1000 ) or (posXProspectiveBirthPlace < 0 ) or (posYProspectiveBirthPlace > 1000 ) or (posYProspectiveBirthPlace < 0) ) {
						wallCollision = true ; 
					}
					int k = 0 ;
					while ( (k < organismVector.size() ) and not wallCollision and not creatureCollision ) {
						creatureCollision =  (std::pow(posXProspectiveBirthPlace - organismVector.at(k)->getPosX() , 2) + std::pow(posYProspectiveBirthPlace - organismVector.at(k)->getPosY() , 2) ) < std::pow(childRadius + organismVector.at(k)->getRadius(), 2) ;
						k++ ; 
						if (creatureCollision) { std::cout << "COLLISION WITH CREATURE " << std::endl ; } 
					}
					validBirthPlace =( (not creatureCollision ) and (not wallCollision)) ; 
					if (not validBirthPlace){
						std::cout << " there is a collision " << std::endl ; 
					}   
					j ++; 
				} 
				numberOfSteps++ ; 
			}
			
			Predator* offspring = new Predator(posXProspectiveBirthPlace, posYProspectiveBirthPlace,
				childRadius,energy, sex, speed, hungerSensitivity, metabolicRate, lustLevel, visionRange);//Above parameters cause program failure!
			organismVector.push_back(offspring);
	}
}