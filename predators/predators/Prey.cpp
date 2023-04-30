#include "Prey.h"
#include "Fauna.h"
#include "OrganicMaths.cpp"

Prey::Prey(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, int myAge, int myHungerLevel,
	float myMetabolicRate, int myLustLevel, float myVisionRange) : Fauna(myPosX, myPosY, myRadius, myEnergy,
		mySex, mySpeed, myAge, myHungerLevel,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Blue);
}

void Prey::update(std::vector<Organism*> organismVector) {//PROBABLY UPDATE FUNCION HERE SHOULD TAKE TWO VECTORS;FAUNA AND FLORA!!!
	std::cout << "I am a predator" << std::endl;
}

float Prey::computeUtility(float distanceSquared, Flora* targetOrganism) {
    float distanceToInterraction;
    float distancefactor;

    distanceToInterraction = sqrt(distanceSquared) - Prey::shape.getRadius() - targetOrganism->getShape().getRadius();//U used getRadius :p

    distancefactor = proximityEffectFactor(0, Prey::getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

    float hungerFactor;
    //1000 acts as placeholder for amount of energy at which indifference to food is total 
    hungerFactor = proximityEffectFactor(0, 1000, Prey::getHungerLevel(), energy);
    return hungerFactor * distancefactor;
    // effect of size or energy of target prey ? 
}
        

float Prey::computeUtility(float distanceSquared, Fauna* targetOrganism) {
    float distanceToInterraction;
    float distancefactor;

    distanceToInterraction = sqrt(distanceSquared) - Prey::shape.getRadius() - targetOrganism->getShape().getRadius();//U used getRadius :p

    distancefactor = proximityEffectFactor(0, Prey::getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

    if( (targetOrganism->getType() == "prey") and ( targetOrganism->getSex()!=  Prey::getSex() ) )  {
          float lustFactor; 
            //1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
            lustFactor = 1 - proximityEffectFactor(0, 1000, Prey::getLustLevel(), energy);
        // effect of size or energy of target mate ? 
        return lustFactor*distancefactor ; 
    }
    else {
        //float lustFactor; FEAR FACTOR ? Hosted by Joe Rogan ? 
        return - distancefactor ; 
    }
    return 0.0; 
}