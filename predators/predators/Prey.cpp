#include "Prey.h"
#include "Fauna.h"

Prey::Prey(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, int myAge, int myHungerLevel,
	float myMetabolicRate, int myLustLevel, float myVisionRange) : Fauna(myPosX, myPosY, myRadius, myEnergy,
		mySex, mySpeed, myAge, myHungerLevel,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Blue);
}

void Prey::update(std::vector<Organism*> organismVector) {
	std::cout << "I am a predator" << std::endl;
}

float Prey::computeUtility(float distance, Organism organism) {
	return 4;
}

float Prey::computeUtility2(float distanceSquared, Organism* targetOrganism) {
    float distanceToInterraction;
    distanceToInterraction = sqrt(distanceSquared) - shape.getRadius() - targetOrganism->getRadius()
    float distancefactor;
    distancefactor= proximityEffectFactor(0, visionRange, 1, distanceToInterraction ) ; 
    If (targetOrganism->getType() == "flora"){
            float hungerFactor; 
            //1000 acts as placeholder for amount of energy at which indifference to food is total 
            hungerFactor = proximityEffectFactor(0, 1000, hungerSensitivity , energy ) ; 
        return hungerFactor*distancefactor ; 
        // effect of size or energy of target prey ? 
    }
    Else If ( (targetOrganism->getType() == "prey") and ( targetOrganism->getSex()!=  sex ) )  {
          float lustFactor; 
            //1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
            lustFactor = 1 - proximityEffectFactor(0, 1000, lustLevel , energy ) ; 
        // effect of size or energy of target mate ? 
        return lustFactor*distancefactor ; 
    }
    Else If (targetOrganism->getType() == "predator")  {
 //         float lustFactor; FEAR FACTOR ? Hosted by Joe Rogan ? 
        return - distancefactor ; 
    }
    return 0.0; 
}