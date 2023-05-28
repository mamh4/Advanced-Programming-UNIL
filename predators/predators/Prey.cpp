#include "Prey.h"
#include "Fauna.h"
#include "OrganicMaths.h"
#include "Predator.h"
#include "Flora.h"
#include "Gameboard.h"
#include "OrganicStats.h"

Prey::Prey(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, float myHungerSensitivity,
	float myMetabolicRate, float myLustLevel, float myVisionRange, float myPredatorAversion) : Fauna(myPosX, myPosY, myRadius, myEnergy,
		mySex, mySpeed, myHungerSensitivity,
		myMetabolicRate, myLustLevel, myVisionRange) {
    
    predatorAversion = myPredatorAversion;
	shape.setFillColor(sf::Color::Color(0,120,255));
	numberOfPrey += 1;

	if (mySex) {
		numberOfFemalePrey += 1;
	}
	else {
		numberOfMalePrey += 1;
	}
}

float Prey::getPredatorAversion() {
	return this->predatorAversion;
}

//Is invoked by the update method of the Fauna class. Computes the utility of interacting with an organism and stores it in the directionalUtility vector.
//computes the utility of interacting with the organism with the highest utility and stores it in maxInteractionUtility.
//Also stores the organism in the possibleCollisions vector if it is within the interaction range.
//The utility is spread out onto the half circle. i.e if the prey gains + utility to move 90 degrees but the action is blocked due to collision it can circle it.
// Prey gain utility to run in opposite direction of predators. The utility is based on the predators aversion and the distance to the predator.
void Prey::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions,
	float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget) {

	float currentUtility = 0;
	float angleBetween = 0;
	int currentIntegerDirection = 0;

	angleBetween = angle(this, targetOrganism);
	currentIntegerDirection = angleSorting(angleBetween);

	float satietyEffectFactor;
	satietyEffectFactor = proximityEffectFactor(0.0, satietyThreshold, this->getEnergy());

	if (distanceSquared < std::pow(this->getRadius() + targetOrganism->getRadius() + rangeOfInteraction, 2)) {
		possibleCollisions.push_back(targetOrganism);
		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			if ((this->getSex() != myPrey->getSex()) and this->getFertile() and myPrey->getFertile() and (myPrey->getEnergy() > 1.5 * baseReproductionCost)) {
				if (this->getEnergy() <= 1.5 * baseReproductionCost) {
					currentUtility = maxInteractionUtility - 1000.0;
				}
				else {
					currentUtility = 25.0 * (1 + this->getLustLevel()) * (1 - satietyEffectFactor);

				}
			}
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			currentUtility = 50.0 * (1 + this->getPredatorAversion());
			int oppositeCurrentIntegerDirection = (((angleSectionNumber / 2) + currentIntegerDirection) % angleSectionNumber);
			directionalUtility[oppositeCurrentIntegerDirection] += currentUtility;
			for (int l = 1; l <= (angleSectionNumber / 4); l++) {
				int testInteger = 0;
				testInteger = directionalUtility.size();
				testInteger = (((oppositeCurrentIntegerDirection + l) % angleSectionNumber));
				directionalUtility[((oppositeCurrentIntegerDirection + l) % angleSectionNumber)] += (currentUtility / (l + 1));
				testInteger = (((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber));
				directionalUtility[((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)] += (currentUtility / (l + 1));

			}
			currentUtility = maxInteractionUtility - 1000.0;
		}
		else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
			currentUtility = 10.0 * std::min(myFlora->getEnergy(), energyAbsorbtionRate) * (1.0 + this->getHungerSensitivity()) * satietyEffectFactor;
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

		distancefactor = proximityEffectFactor(0, this->getVisionRange(), distanceToInterraction);

		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			if ((this->getSex() != myPrey->getSex()) and this->getFertile() and myPrey->getFertile() and (myPrey->getEnergy() > 1.5 * baseReproductionCost)) {
				if (not this->getEnergy() <= 1.5 * baseReproductionCost) {
					currentUtility = 5.0 * (1 + this->getLustLevel()) * distancefactor * (1 - satietyEffectFactor);
				}
			}
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			currentUtility = 15.0 * distancefactor * (1 + this->getPredatorAversion());
			int oppositeCurrentIntegerDirection = (((angleSectionNumber / 2) + currentIntegerDirection) % angleSectionNumber);
			directionalUtility[oppositeCurrentIntegerDirection] += currentUtility;
			for (int l = 1; l <= (angleSectionNumber / 4); l++) {
				int testInteger = 0;
				testInteger = directionalUtility.size();
				testInteger = (((oppositeCurrentIntegerDirection + l) % angleSectionNumber));
				directionalUtility[((oppositeCurrentIntegerDirection + l) % angleSectionNumber)] += (currentUtility / (l + 1));
				testInteger = (((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber));
				directionalUtility[((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)] += (currentUtility / (l + 1));

			}
			currentUtility = 0.0;
		}
		else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
			currentUtility = std::min(myFlora->getEnergy(), energyAbsorbtionRate) * satietyEffectFactor * distancefactor * (1 + this->getHungerSensitivity());
		}
		directionalUtility[currentIntegerDirection] += currentUtility;
		for (int l = 1; l <= (angleSectionNumber / 4); l++) {
			int testInteger = 0;
			testInteger = directionalUtility.size();
			testInteger = (((currentIntegerDirection + l) % angleSectionNumber));
			directionalUtility[((currentIntegerDirection + l) % angleSectionNumber)] += (currentUtility / (l + 1));
			testInteger = (((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber));
			directionalUtility[((currentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)] += (currentUtility / (l + 1));
		}
	}
}

// Prey can interact with prey, flora and other predators.
// If the prey is fertile and the other prey is fertile, both have enough energy to reproduce and is computed to be their max utility, they will try reproduce.
// Reproduction is prevented if there is no place near the mother to give birth. Or the organisms vector reached size of 300, to avoid it growing out of control.
// Prey also gain utilty from eating flora to get energy. they would absorb enegy from the flora.
void Prey::interact(Organism* targetOrganism, std::vector<Organism*>& organismVector) {
	if(Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)){
		float absorbedEnergy;
		absorbedEnergy = std::min(energyAbsorbtionRate, targetOrganism->getEnergy());
		targetOrganism->setEnergy(targetOrganism->getEnergy() - absorbedEnergy);
		this->setEnergy(this->getEnergy() + absorbedEnergy);
	}
	else if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
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

		int angleCounter = 0 ; 
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

		if (validCandidateBirthPlace and organismVector.size()<=300) {

			bool sex = (rand() % 2 == 0);

			int speed = 1;
			speed = static_cast<int> (mutateOffspring("Prey", "Speed", this->getSpeed(), myPrey->getSpeed()));

			float hungerSensitivity = 1;
			hungerSensitivity = mutateOffspring("Prey", "Hunger Sensitivity", this->getHungerSensitivity(), myPrey->getHungerSensitivity());

			float metabolicRate = 0.1;
			metabolicRate = mutateOffspring("Prey", "Metabolic Rate", this->getMetabolicRate(), myPrey->getMetabolicRate());

			int lustLevel = 1;
			lustLevel = mutateOffspring("Prey", "Lust Level", this->getLustLevel(), myPrey->getLustLevel());

			int visionRange = 250;
			visionRange = mutateOffspring("Prey", "Vision Range", this->getVisionRange(), myPrey->getVisionRange());

			int predatorAversion = 1;
			predatorAversion = mutateOffspring("Prey", "Predator Aversion", this->getPredatorAversion(), myPrey->getPredatorAversion());


			Prey* offspring = new Prey(candidateBirthPlaceX, candidateBirthPlaceY,
			childRadius, baseReproductionCost*2.0 , sex, speed, hungerSensitivity, metabolicRate, lustLevel, visionRange, predatorAversion);
			organismVector.push_back(offspring);

			this->setEnergy(this->getEnergy() - baseReproductionCost);
			targetOrganism->setEnergy(targetOrganism->getEnergy() - baseReproductionCost);
			this->setNumberOfOffspring(this->getNumberOfOffspring() + 1);
			if (Prey* myPrey = dynamic_cast<Prey*>(this)) {
				myPrey->setNumberOfOffspring(myPrey->getNumberOfOffspring() + 1);
			}
		}
	}
}
