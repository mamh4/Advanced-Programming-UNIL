#pragma once
#include "Fauna.h"
#include "Flora.h"
class Prey : public Fauna
{
private: 
	float predatorAversion;

public:
	Prey(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
		int mySpeed, float myHungerSensitivity,
		float myMetabolicRate, float myLustLevel, float myVisionRange, float myPredatorAversion);

	float getPredatorAversion();

//	virtual void update(std::vector<Organism*>& organismVector);

//	virtual float computeUtility(float distance, Fauna* fauna);

	virtual void computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget);

	virtual void interact(Organism* organism, std::vector<Organism*>& organismVector);

}
;


