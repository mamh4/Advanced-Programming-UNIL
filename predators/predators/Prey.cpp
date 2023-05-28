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
			currentUtility = 50.0 * (1 + this->getPredatorAversion()); // 1000 AS DEATH SCORE ----> DISCUSS 
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

		distancefactor = proximityEffectFactor(0, this->getVisionRange(), distanceToInterraction);// USE VISION RANGE OR % OF IT ? 

		if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			if ((this->getSex() != myPrey->getSex()) and this->getFertile() and myPrey->getFertile() and (myPrey->getEnergy() > 1.5 * baseReproductionCost)) {
				if (not this->getEnergy() <= 1.5 * baseReproductionCost) {
					currentUtility = 5.0 * (1 + this->getLustLevel()) * distancefactor * (1 - satietyEffectFactor);
				}
			}
		}
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			currentUtility = 15.0 * distancefactor * (1 + this->getPredatorAversion()); // 1000 arbitraty as death score  Then 50 then 25 
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

void Prey::interact(Organism* targetOrganism, std::vector<Organism*>& organismVector) {
	if(Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)){
		// CLASS CONST OR ATTRIBUTE ? Maximum amount of energy the predator can take from a prey in one interaction 
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

			bool sex; //= false;//rand() % 2 == 0 ? true : false;

			int randomSexDetermination;
			randomSexDetermination = rand() % 2;
			sex = (randomSexDetermination == 0);

			int speed = 1;//rand() % 10 + 1;
			speed = static_cast<int> (geneticEngine("Prey", "Speed", this->getSpeed(), myPrey->getSpeed()));
			//std::cout << "Speed test genetics Engine " << speed << std::endl;

			float hungerSensitivity = 1;//rand() % 100 + 1
			hungerSensitivity = geneticEngine("Prey", "Hunger Sensitivity", this->getHungerSensitivity(), myPrey->getHungerSensitivity());
			//std::cout << "Hunger Sensitivity test genetics Engine " << hungerSensitivity << std::endl;

			float metabolicRate = 0.1;//static_cast<float>(rand() % 10 + 1) / 10.0f;
			metabolicRate = geneticEngine("Prey", "Metabolic Rate", this->getMetabolicRate(), myPrey->getMetabolicRate());
			//std::cout << "Metabolic Rate test genetics Engine " << metabolicRate << std::endl;

			int lustLevel = 1;//rand() % 100 + 1;
			lustLevel = geneticEngine("Prey", "Lust Level", this->getLustLevel(), myPrey->getLustLevel());
			//std::cout << "Lust Level test genetics Engine " << lustLevel << std::endl;

			int visionRange = 250; //rand() % 100 + 1;
			visionRange = geneticEngine("Prey", "Vision Range", this->getVisionRange(), myPrey->getVisionRange());
			//std::cout << "Vision Range test genetics Engine " << visionRange << std::endl;

			int predatorAversion = 1;//rand() % 100 + 1;
			predatorAversion = geneticEngine("Prey", "Predator Aversion", this->getPredatorAversion(), myPrey->getPredatorAversion());
			//std::cout << "Predator Aversion test genetics Engine " << predatorAversion << std::endl;


			Prey* offspring = new Prey(candidateBirthPlaceX, candidateBirthPlaceY,
				childRadius, baseReproductionCost*2.0 , sex, speed, hungerSensitivity, metabolicRate, lustLevel, visionRange, predatorAversion);//Above parameters cause program failure!
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
