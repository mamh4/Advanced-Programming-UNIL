#pragma once
#include "Fauna.h"
class Predator : public Fauna
{
	public:
		Predator(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
			int mySpeed, int myAge, int myHungerLevel,
			float myMetabolicRate, int myLustLevel, float myVisionRange);
		
		virtual void update(std::vector<Organism*> organismVector);

		virtual float computeUtility(float distance, Organism organism);
};

