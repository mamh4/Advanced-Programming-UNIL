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
	shape.setFillColor(sf::Color::Blue);
}

float Prey::getPredatorAversion() {
	return this->predatorAversion;
}



/*/float Prey::computeUtility(float distanceSquared, Organism* targetOrganism) {
    float distanceToInterraction;
    float distancefactor;

    distanceToInterraction = sqrt(distanceSquared) - Prey::shape.getRadius() - targetOrganism->getShape().getRadius();//U used getRadius :p

    distancefactor = proximityEffectFactor(0, Prey::getVisionRange(), 1, distanceToInterraction); //use getters and always "Class::"

    float hungerFactor;
    //1000 acts as placeholder for amount of energy at which indifference to food is total 
    hungerFactor = proximityEffectFactor(0, 1000, Prey::getHungerSensitivity(), Prey::getEnergy());
    return hungerFactor * distancefactor;
    // effect of size or energy of target prey ? 
} /*/
        



void Prey::interact(Organism* targetOrganism, std::vector<Organism*>& organismVector) {
	if(Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)){
		float energyAbsorbtionSpeed;
		energyAbsorbtionSpeed = 10.0;
		// CLASS CONST OR ATTRIBUTE ? Maximum amount of energy the predator can take from a prey in one interaction 
		float absorbedEnergy;
		absorbedEnergy = std::min(energyAbsorbtionSpeed, targetOrganism->getEnergy());
		targetOrganism->setEnergy(targetOrganism->getEnergy() - absorbedEnergy);
		this->setEnergy(this->getEnergy() + absorbedEnergy);
	}
	else if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
		//NEW!! Age must be greater than 30 to reproduce

		/*/

		float baseReproductionEnergyCost;
		baseReproductionEnergyCost = 250.0; 
		float energy = 500;//rand() % 100 + 1; 2* BASEREPRODZCTION COST 
		bool sex = false;//rand() % 2 == 0 ? true : false;
		int speed = 1;//rand() % 10 + 1;
		float hungerSensitivity = 1;//rand() % 100 + 1;
		float metabolicRate = 0.1;//static_cast<float>(rand() % 10 + 1) / 10.0f;
		int lustLevel = 50;//rand() % 100 + 1;
		int visionRange = 300; //rand() % 100 + 1;
		float predatorAversion = 1;//static_cast<float>(rand() % 10 + 1) / 10.0f;
		this->setEnergy(this->getEnergy() - baseReproductionEnergyCost);
		targetOrganism->setEnergy(targetOrganism->getEnergy() - baseReproductionEnergyCost);  // MOVE TO AFTER CHEcK IF REPRO POSSIBLE 
		// CHECK EMPTY SPACE
		//float childRadius = 5.0;
		//float posXBirthPlace = (this->getPosX() + targetOrganism->getPosX()) / 2.0; // avg of parents position 
		//float posYBirthPlace = (this->getPosY() + targetOrganism->getPosY()) / 2.0; // avg of parents position 
		bool validBirthPlace = false;
		//loat posXProspectiveBirthPlace = posXBirthPlace;
		//float posYProspectiveBirthPlace = posYBirthPlace;
		//bool creatureCollision;
		//bool wallCollision;
		/*/

		float baseReproductionEnergyCost;
		baseReproductionEnergyCost = 250.0; 
		float energy = 500;//rand() % 100 + 1; 2* BASEREPRODZCTION COST 
		bool sex; //= false;//rand() % 2 == 0 ? true : false;

		int randomSexDetermination ; 
		randomSexDetermination = rand() % 2 ; 
		sex = (randomSexDetermination== 0 ); 

		int speed = 1;//rand() % 10 + 1;
		speed = static_cast<int> (geneticEngine ("Prey", "Speed", this->getSpeed(), myPrey->getSpeed() ))  ; 
		std::cout << "Speed test genetics Engine " << speed << std::endl; 

		float hungerSensitivity = 1;//rand() % 100 + 1
		hungerSensitivity = geneticEngine ("Prey", "Hunger Sensitivity", this->getHungerSensitivity(), myPrey->getHungerSensitivity() ); 
		std::cout << "Hunger Sensitivity test genetics Engine " << hungerSensitivity << std::endl; 

		float metabolicRate = 0.1;//static_cast<float>(rand() % 10 + 1) / 10.0f;
		metabolicRate = geneticEngine ("Prey", "Metabolic Rate", this->getMetabolicRate(), myPrey->getMetabolicRate() ); 
		std::cout << "Metabolic Rate test genetics Engine " << metabolicRate << std::endl; 

		int lustLevel = 1;//rand() % 100 + 1;
		lustLevel = geneticEngine ("Prey", "Lust Level", this->getLustLevel(), myPrey->getLustLevel() ); 
		std::cout << "Lust Level test genetics Engine " << lustLevel << std::endl; 

		int visionRange = 250; //rand() % 100 + 1;
		visionRange = geneticEngine ("Prey", "Vision Range", this->getVisionRange(), myPrey->getVisionRange() ); 
		std::cout << "Vision Range test genetics Engine " << visionRange << std::endl; 

		int predatorAversion = 1;//rand() % 100 + 1;
		predatorAversion = geneticEngine ("Prey", "Predator Aversion", this->getPredatorAversion(), myPrey->getPredatorAversion() ); 
		std::cout << "Predator Aversion test genetics Engine " << predatorAversion << std::endl; 

		this->setEnergy(this->getEnergy() - baseReproductionEnergyCost);
		targetOrganism->setEnergy(targetOrganism->getEnergy() - baseReproductionEnergyCost);  // MOVE TO AFTER CHEcK IF REPRO POSSIBLE ELSE ENERGY TAKEN WITH NO OFFSPRING 
		// CHECK EMPTY SPACE
		//float childRadius = 5.0;
		//float posXBirthPlace = (this->getPosX() + targetOrganism->getPosX()) / 2.0; // avg of parents position 
		//float posYBirthPlace = (this->getPosY() + targetOrganism->getPosY()) / 2.0; // avg of parents position 
		bool validBirthPlace = false;
		//loat posXProspectiveBirthPlace = posXBirthPlace;
		//float posYProspectiveBirthPlace = posYBirthPlace;
		//bool creatureCollision;
		//bool wallCollision;

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

		/*
		const int limitNumberOfSteps = 20;
		int numberOfSteps = 1;
		while ((numberOfSteps <= limitNumberOfSteps) and not validBirthPlace) {
			int newAngleSectionNumber;
			int j = 0;//switch to 1 and replace here
			newAngleSectionNumber = static_cast<int> ((M_PI * limitNumberOfSteps * stepSize / childRadius));
			while ((j < newAngleSectionNumber) and not validBirthPlace) {
				//std::cout << " testing angle " << numberOfSteps << "at angle " << j << "out of " << newAngleSectionNumber << std::endl;
				// test location 
				posXProspectiveBirthPlace = posXBirthPlace + numberOfSteps * stepSize * cos(2 * M_PI * j / newAngleSectionNumber);
				posYProspectiveBirthPlace = posYBirthPlace + numberOfSteps * stepSize * sin(2 * M_PI * j / newAngleSectionNumber);
				creatureCollision = false;
				wallCollision = false;

				if ((posXProspectiveBirthPlace > windowWidth - childRadius) or
					(posXProspectiveBirthPlace < 0 + childRadius) or
					(posYProspectiveBirthPlace > windowHeight - childRadius) or
					(posYProspectiveBirthPlace < 0 + childRadius)) {
					wallCollision = true;
				}
				int k = 0;
				while ((k < organismVector.size()) and not wallCollision and not creatureCollision) {
					creatureCollision = (std::pow(posXProspectiveBirthPlace - organismVector.at(k)->getPosX(), 2) + std::pow(posYProspectiveBirthPlace - organismVector.at(k)->getPosY(), 2)) < std::pow(childRadius + organismVector.at(k)->getRadius(), 2);
					k++;
					if (creatureCollision) { std::cout << "COLLISION WITH CREATURE " << std::endl; }
				}
				validBirthPlace = ((not creatureCollision) and (not wallCollision));
				//if (not validBirthPlace) {
				//	std::cout << " there is a collision " << std::endl;
				//}
				j++;
				//till here
			}
			numberOfSteps++;
		}
		/*/
		if (validCandidateBirthPlace) {
			Prey* offspring = new Prey(candidateBirthPlaceX, candidateBirthPlaceY,
		childRadius, energy, sex, speed, hungerSensitivity, metabolicRate, lustLevel, visionRange,predatorAversion);//Above parameters cause program failure!
		organismVector.push_back(offspring);
		numberOfPrey += 1;
		} 
		else{
			std::cout << "no valid birthplace arround mother" << std::endl; 
		}
		
	}
}



void Prey::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility , std::vector<Organism*>& possibleCollisions, 
	float& maxInteractionUtility , Organism*& maxInteractionUtilityTarget ) {
    
	float currentUtility = 0 ;
	float angleBetween = 0 ;
    int currentIntegerDirection =0 ; 

	float baseReproductionEnergyCost;
	baseReproductionEnergyCost = 250.0;

    float energyAbsorbtionSpeed;
	energyAbsorbtionSpeed = 50.0;

    angleBetween = angle( this, targetOrganism);
    currentIntegerDirection = angleSorting(angleBetween); 

    if (distanceSquared < std::pow(this->getRadius() + targetOrganism->getRadius() + rangeOfInteraction, 2)) {
        possibleCollisions.push_back(targetOrganism);
        if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
			//std::cout << " I can interract with a Prey" << std::endl; 
			if ((this->getSex() != myPrey->getSex()) and this->getFertile() and myPrey->getFertile() and (myPrey->getEnergy() > baseReproductionEnergyCost)) {

                if (this->getEnergy() <= baseReproductionEnergyCost){
					//std::cout << " I do not have enough energy :( my energy level is " << this->getEnergy() << std::endl; 
                    // ARBITRARY 250
                    currentUtility = - baseReproductionEnergyCost; 
                } 
                else{
					//std::cout << " I have enough energy" << std::endl; 
                    // ARBITRARY 250
					currentUtility = baseReproductionEnergyCost;
                }
			}
		}
        else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
			//std::cout << " I can interract with a Predator" << std::endl; 
			float distanceToInterraction;
            distanceToInterraction = sqrt(distanceSquared) - this->getRadius() - targetOrganism->getRadius();
			float fearFactor;
            fearFactor = proximityEffectFactor(0, 1000, this->getPredatorAversion(), distanceToInterraction);
            currentUtility = 1000.0 * fearFactor;
            int oppositeCurrentIntegerDirection = (((angleSectionNumber / 2) + currentIntegerDirection) % angleSectionNumber);
            directionalUtility[oppositeCurrentIntegerDirection] += currentUtility;
            //	if ( directionalUtility[currentIntegerDirection] > maxDirectionalUtility ) { 
            //		maxDirectionalUtility = directionalUtility[currentIntegerDirection] ; 
            //		maxDirectionalUtilityTarget = currentIntegerDirection ; 
            //	 } 
            for (int l = 1; l <= (angleSectionNumber / 4); l++) {
                int testInteger = 0;
                testInteger = directionalUtility.size();
                testInteger = (((oppositeCurrentIntegerDirection + l) % angleSectionNumber));
                directionalUtility[((oppositeCurrentIntegerDirection + l) % angleSectionNumber)] += (currentUtility / (l + 1));
                testInteger = (((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber));
                directionalUtility[((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)] += (currentUtility / (l + 1));

            }
            currentUtility = maxInteractionUtility - 10; // disqualifying interaction as an option  
        }
		else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
			//std::cout << " I can interract with a Flora" << std::endl; 
            currentUtility = std::min( myFlora->getEnergy(), energyAbsorbtionSpeed); 
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
            if ((this->getSex() != myPrey->getSex()) and this->getFertile() and myPrey->getFertile() and (myPrey->getEnergy() > baseReproductionEnergyCost)) {
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
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
            float fearFactor; 
            fearFactor = proximityEffectFactor(0, 1000, this->getPredatorAversion(), distanceToInterraction);
            currentUtility = -1000.0 * fearFactor ; 
		}
        else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
            float hungerFactor;
			//1000 acts as placeholder for amount of energy at which indifference to food is total 
			hungerFactor = proximityEffectFactor(0, 1000, this->getHungerSensitivity(), this->getEnergy());
			currentUtility =  std::min( myFlora->getEnergy(), energyAbsorbtionSpeed) * hungerFactor * distancefactor;
			// effect of size or energy of target prey ? 
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