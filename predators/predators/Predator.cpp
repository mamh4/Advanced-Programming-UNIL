#include "Predator.h"
#include "Prey.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "OrganicMaths.h"
#include "Gameboard.h"
#include "OrganicStats.h"

Predator::Predator(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, float myHungerSensitivity,
	float myMetabolicRate, float myLustLevel, float myVisionRange) : Fauna(myPosX, myPosY,myRadius, myEnergy, 
		mySex, mySpeed, myHungerSensitivity,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Red);
	numberOfPredators += 1;


	if (mySex) {
		numberOfFemalePredator += 1;
	}
	else {
		numberOfMalePredator += 1;
	}

}

//Is invoked by the update method of the Fauna class. Computes the utility of interacting with an organism and stores it in the directionalUtility vector.
//computes the utility of interacting with the organism with the highest utility and stores it in maxInteractionUtility.
//Also stores the organism in the possibleCollisions vector if it is within the interaction range.
//The utility is spread out onto the half circle. i.e if the predator gains + utility to move 90 degrees but the action is blocked due to collision it can circle it.
void Predator::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility , std::vector<Organism*>& possibleCollisions, 
	float& maxInteractionUtility , Organism*& maxInteractionUtilityTarget ) {

	float currentUtility = 0 ; 
    float angleBetween = 0 ;
    int currentIntegerDirection =0 ; 

    angleBetween = angle( this, targetOrganism);
    currentIntegerDirection = angleSorting(angleBetween); 

	float satietyEffectFactor; 
	satietyEffectFactor = proximityEffectFactor(0.0, satietyThreshold, this->getEnergy()); 

    if (distanceSquared < std::pow(this->getRadius() + targetOrganism->getRadius() + rangeOfInteraction, 2)) {
        possibleCollisions.push_back(targetOrganism);
        if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {

			currentUtility =  10.0* std::min( myPrey->getEnergy(), energyAbsorbtionRate)  * (1 + this->getHungerSensitivity() ) * satietyEffectFactor;
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {			
			if ((this->getSex() != myPredator->getSex()) and this->getFertile() and myPredator->getFertile() and (myPredator->getEnergy() > 1.5*baseReproductionCost)) {

				if (this->getEnergy() <= 1.5*baseReproductionCost) {
					currentUtility = maxInteractionUtility - 1000.0 ;
				}
				else {
					currentUtility = (1+getLustLevel()) * 25.0 * (1- satietyEffectFactor);
				}
			}
		}

		if (currentUtility > maxInteractionUtility) {
			maxInteractionUtility = currentUtility;
			maxInteractionUtilityTarget = targetOrganism;
		}
    }
	else {
		float distanceToInterraction;
		float distancefactor;


		distanceToInterraction = sqrt(distanceSquared) - this->getRadius() - targetOrganism->getRadius();

		distancefactor = distancefactor = proximityEffectFactor(0, this->getVisionRange(), distanceToInterraction);

		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			currentUtility =  std::min( myPrey->getEnergy(), energyAbsorbtionRate)  * distancefactor * (1 + this->getHungerSensitivity() ) * satietyEffectFactor;
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			if ((this->getSex() != myPredator->getSex()) and this->getFertile() and myPredator->getFertile() and (myPredator->getEnergy() > 1.5*baseReproductionCost)) {
                if (not this->getEnergy() <= 1.5*baseReproductionCost){
				    currentUtility = (1+getLustLevel()) * 25.0 * (1- satietyEffectFactor) * distancefactor;
                } 

			}
		}

    directionalUtility[currentIntegerDirection] += currentUtility;

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

// Predators can interact with prey and other predators.
// If the predator is fertile and the other predator is fertile, both have enough energy to reproduce and is computed to be their max utility, they will try reproduce.
// Reproduction is prevented if there is no place near the mother to give birth. Or the organisms vector reached size of 300, to avoid it growing out of control.
// Predators also gain utilty from hunting prey to get energy. they would absorb enegy from the prey.
void Predator::interact(Organism* targetOrganism, std::vector<Organism*>& organismVector) {
	if(Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)){
		float absorbedEnergy;
		absorbedEnergy = std::min(energyAbsorbtionRate, targetOrganism->getEnergy());
		targetOrganism->setEnergy(targetOrganism->getEnergy() - absorbedEnergy);
		this->setEnergy(this->getEnergy() + absorbedEnergy);
	}
	else if (Predator* myPred = dynamic_cast<Predator*>(targetOrganism)) {

		bool validBirthPlace = false;

		float motherX; 
		float motherY; 
		float motherRadius; 
		if (this->getSex()) { // TRUE = FEMALE = MOTHER 
			motherX = this->getPosX() ; 
			motherY = this->getPosY() ; 
			motherRadius = this->getRadius() ; 
		}
		else{
			motherX = targetOrganism->getPosX() ; 
			motherY = targetOrganism->getPosY() ; 
			motherRadius = targetOrganism->getRadius() ; 
		}
		float childRadius = 2.0; // GET THE ACTUAL RADIUS THROUGH GENETICS ENGINE 
		float candidateBirthPlaceX = 0.0 ; 
		float candidateBirthPlaceY = 0.0 ; 

		int adequateAngleSectionNumber = 24 ; 
		int adequateStepNumber = 3 ; // gets into interaction distance 

		float validCandidateBirthPlace = false ; 
		bool wallCollision= false; 
		bool creatureCollision = false ; 

		int angleCounter = 0 ; // MAKE THIS FAUNA FUNCTION AT SOME POINT ??? 
		while ((angleCounter < adequateAngleSectionNumber) and not validCandidateBirthPlace) {
			int stepCounter = 0 ; 
			while ((stepCounter < adequateStepNumber) and not validCandidateBirthPlace){
				wallCollision = false ;
        		creatureCollision = false ; 
				candidateBirthPlaceX = motherX + (motherRadius + childRadius + stepCounter*1.0 )*cos(2 * M_PI * angleCounter / adequateAngleSectionNumber);
				candidateBirthPlaceY = motherY + (motherRadius + childRadius + stepCounter*1.0 )*sin(2 * M_PI * angleCounter / adequateAngleSectionNumber);
				int organismCounter = 0 ; 
				wallCollision = ((candidateBirthPlaceX > windowWidth - childRadius) or
					(candidateBirthPlaceX < 0 + childRadius) or
					(candidateBirthPlaceY > windowHeight - childRadius) or
					(candidateBirthPlaceY < 0 + childRadius));
				while ((organismCounter < organismVector.size()) and not wallCollision and not creatureCollision) {
							creatureCollision = (std::pow(candidateBirthPlaceX - organismVector.at(organismCounter)->getPosX(), 2) + 
								std::pow(candidateBirthPlaceY - organismVector.at(organismCounter)->getPosY(), 2)) < 
								std::pow(childRadius + organismVector.at(organismCounter)->getRadius(), 2);
							organismCounter++;
						}
				validCandidateBirthPlace = ((not creatureCollision) and (not wallCollision));
				stepCounter++; 
			}
			angleCounter++; 
		}
		
		if (validCandidateBirthPlace and organismVector.size() <= 300) {

			float energy = 2*baseReproductionCost;
			bool sex;

			int randomSexDetermination;
			randomSexDetermination = rand() % 2;
			sex = (randomSexDetermination == 0);

			int speed = 1;
			speed = static_cast<int> (
				
				
				("Predator", "Speed", this->getSpeed(), myPred->getSpeed()));

			float hungerSensitivity = 1;
			hungerSensitivity = mutateOffspring("Predator", "Hunger Sensitivity", this->getHungerSensitivity(), myPred->getHungerSensitivity());

			float metabolicRate = 0.1;
			metabolicRate = mutateOffspring("Predator", "Metabolic Rate", this->getMetabolicRate(), myPred->getMetabolicRate());

			int lustLevel = 1;
			lustLevel = mutateOffspring("Predator", "Lust Level", this->getLustLevel(), myPred->getLustLevel());

			int visionRange = 250;
			visionRange = mutateOffspring("Predator", "Vision Range", this->getVisionRange(), myPred->getVisionRange());

			Predator* offspring = new Predator(candidateBirthPlaceX, candidateBirthPlaceY,
			childRadius, energy, sex, speed, hungerSensitivity, metabolicRate, lustLevel, visionRange);
			organismVector.push_back(offspring);

			this->setEnergy(this->getEnergy() - baseReproductionCost);
			targetOrganism->setEnergy(targetOrganism->getEnergy() - baseReproductionCost);
			this->setNumberOfOffspring(this->getNumberOfOffspring() + 1);
			if (Predator* myPredator = dynamic_cast<Predator*>(this)){
				myPredator->setNumberOfOffspring(myPredator->getNumberOfOffspring() + 1);
			}
		} 
	}
}