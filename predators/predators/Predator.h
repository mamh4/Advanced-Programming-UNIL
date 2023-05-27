#pragma once
#include "Fauna.h"
#include "Flora.h"
class Predator : public Fauna
{

	float const satietyThreshold = 2000.f;
	// float const satietyThreshold = 750.f; test
	float const baseReproductionCost = 500.f; // 500 before 
	float const energyAbsorbtionRate = 30.0f; // was 10 was 15 // BEST SCENARIO 50 // 40 = machine stability 25 or 30 RECALL 30

	public:
		Predator(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
			int mySpeed, float myHungerSensitivity,
			float myMetabolicRate, float myLustLevel, float myVisionRange);

		virtual ~Predator() {};

		//virtual void computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, float& maxDirectionalUtility, int maxDirectionalUtilityTarget, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget);

		virtual void computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget);

		virtual void interact(Organism* organism, std::vector<Organism*>& organismVector);

		//virtual float computeUtility(float distance, Flora* flora);
};

