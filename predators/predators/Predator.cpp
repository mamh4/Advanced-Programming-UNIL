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

			float energy = 2*baseReproductionCost;//rand() % 100 + 1; 2* BASEREPRODZCTION COST 
			bool sex; //= false;//rand() % 2 == 0 ? true : false;

			int randomSexDetermination;
			randomSexDetermination = rand() % 2;
			sex = (randomSexDetermination == 0);

			int speed = 1;//rand() % 10 + 1;
			speed = static_cast<int> (geneticEngine("Predator", "Speed", this->getSpeed(), myPred->getSpeed()));
			//std::cout << "Speed test genetics Engine " << speed << std::endl; 

			float hungerSensitivity = 1;//rand() % 100 + 1
			hungerSensitivity = geneticEngine("Predator", "Hunger Sensitivity", this->getHungerSensitivity(), myPred->getHungerSensitivity());
			//std::cout << "Hunger Sensitivity test genetics Engine " << hungerSensitivity << std::endl; 

			float metabolicRate = 0.1;//static_cast<float>(rand() % 10 + 1) / 10.0f;
			metabolicRate = geneticEngine("Predator", "Metabolic Rate", this->getMetabolicRate(), myPred->getMetabolicRate());
			//std::cout << "Metabolic Rate test genetics Engine " << metabolicRate << std::endl; 

			int lustLevel = 1;//rand() % 100 + 1;
			lustLevel = geneticEngine("Predator", "Lust Level", this->getLustLevel(), myPred->getLustLevel());
			//std::cout << "Lust Level test genetics Engine " << lustLevel << std::endl; 

			int visionRange = 250; //rand() % 100 + 1;
			visionRange = geneticEngine("Predator", "Vision Range", this->getVisionRange(), myPred->getVisionRange());

			Predator* offspring = new Predator(candidateBirthPlaceX, candidateBirthPlaceY,
			childRadius, energy, sex, speed, hungerSensitivity, metabolicRate, lustLevel, visionRange);//Above parameters cause program failure!
			organismVector.push_back(offspring);

			this->setEnergy(this->getEnergy() - baseReproductionCost);
			targetOrganism->setEnergy(targetOrganism->getEnergy() - baseReproductionCost);  // MOVE TO AFTER CHEcK IF REPRO POSSIBLE ELSE ENERGY TAKEN WITH NO OFFSPRING 
			this->setNumberOfOffspring(this->getNumberOfOffspring() + 1);
			if (Predator* myPredator = dynamic_cast<Predator*>(this)){
				myPredator->setNumberOfOffspring(myPredator->getNumberOfOffspring() + 1);
			}
		} 
	}
}