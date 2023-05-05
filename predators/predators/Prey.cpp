#include "Prey.h"
#include "Fauna.h"
#include "OrganicMaths.h"
#include "Predator.h"
#include "Flora.h"

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
        



void Prey::interact(Organism* targetOrganism, std::vector<Organism*>& OrganismVector) {
    /*
    if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
        float energyAbsorbtionSpeed;
        energyAbsorbtionSpeed = 10.0;
        // CLASS CONST OR ATTRIBUTE ? Maximum amount of energy the prey can take from a flora in one interaction 
        float absorbedEnergy;
        absorbedEnergy = std::min(energyAbsorbtionSpeed, myFlora->getEnergy());
        myFlora->setEnergy(myFlora->getEnergy() - absorbedEnergy);
        Prey::setEnergy(Prey::getEnergy() + absorbedEnergy);
    }
    else {
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
        float predatorAversion = static_cast<float>(rand() * 100);
        // CHECK EMPTY SPACE 
        Prey* offspring = new Prey(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange, predatorAversion);
        OrganismVector.push_back(offspring);
    }
    */
}



void Prey::computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility , std::vector<Organism*>& possibleCollisions, 
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
			if ((this->getSex() != myPrey->getSex()) and this->getFertile() and myPrey->getFertile() and (myPrey->getEnergy() > baseReproductionEnergyCost)) {

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
		else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
            float distanceToInterraction;
            distanceToInterraction = sqrt(distanceSquared) - this->getRadius() - targetOrganism->getRadius();
            float fearFactor; 
            fearFactor = proximityEffectFactor(0, 1000, this->getPredatorAversion(), distanceToInterraction);
            currentUtility = 1000.0 * fearFactor ; 
            int oppositeCurrentIntegerDirection = ( ( (angleSectionNumber/2) + currentIntegerDirection ) % angleSectionNumber ) ; 
            directionalUtility[oppositeCurrentIntegerDirection] += currentUtility;
            //	if ( directionalUtility[currentIntegerDirection] > maxDirectionalUtility ) { 
            //		maxDirectionalUtility = directionalUtility[currentIntegerDirection] ; 
            //		maxDirectionalUtilityTarget = currentIntegerDirection ; 
            //	 } 
            for (int l = 1; l <= (angleSectionNumber / 4); l++) {
                                    int testInteger =0 ;
                                    testInteger = directionalUtility.size() ; 
                                    testInteger = (((oppositeCurrentIntegerDirection + l) % angleSectionNumber)) ; 
                                    directionalUtility[((oppositeCurrentIntegerDirection + l) % angleSectionNumber)] +=  (currentUtility / (l + 1));
                                    testInteger = (((oppositeCurrentIntegerDirection - l + angleSectionNumber) % angleSectionNumber)) ; 
                                    directionalUtility[((oppositeCurrentIntegerDirection - l + angleSectionNumber ) % angleSectionNumber)] +=   (currentUtility / (l + 1));
                                
	        }
            currentUtility = maxInteractionUtility -10 ; // disqualifying interaction as an option  
		}
		else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
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