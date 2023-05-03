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
	return Prey::predatorAversion;
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
        

float Prey::computeUtility(float distanceSquared, Organism* targetOrganism) {
    float distanceToInterraction;
    float distancefactor;

    distanceToInterraction = sqrt(distanceSquared) - Prey::getRadius() - targetOrganism->getRadius();//U used getRadius :p

    distancefactor = proximityEffectFactor(0, Prey::getVisionRange(), 1, distanceToInterraction);//use getters and always "Class::"

    if (Prey* myPrey = dynamic_cast<Prey*>(targetOrganism)) {
        if (myPrey->getSex() != Prey::getSex()) {
            float lustFactor;
            //1000 acts as placeholder for amount of energy at which the weight of sex drive is total 
            lustFactor = 1 - proximityEffectFactor(0, 1000, Prey::getLustLevel(), energy);
            // effect of size or energy of target mate ? 
            return lustFactor * distancefactor;
        }
    } 
    else if (Predator* myPredator = dynamic_cast<Predator*>(targetOrganism)) {
            //float lustFactor; FEAR FACTOR ?
            return (-distancefactor);
    }
    else if (Flora* myFlora = dynamic_cast<Flora*>(targetOrganism)) {
            float hungerFactor;
            //1000 acts as placeholder for amount of energy at which indifference to food is total 
            hungerFactor = proximityEffectFactor(0, 1000, Prey::getHungerSensitivity(), Prey::getEnergy());
            return hungerFactor * distancefactor;
            // effect of size or energy of target prey ? 
    }
        //return 0.0; 
}




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