#pragma once
#include "Fauna.h"
#include "Flora.h"
class Predator : public Fauna
{

	float const satietyThreshold = 2000.f;
	float const baseReproductionCost = 500.f;
	float const energyAbsorbtionRate = 30.0f;

	public:
		Predator(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
			int mySpeed, float myHungerSensitivity,
			float myMetabolicRate, float myLustLevel, float myVisionRange);

		virtual ~Predator() {};

		virtual void computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget);

		virtual void interact(Organism* organism, std::vector<Organism*>& organismVector);

};

