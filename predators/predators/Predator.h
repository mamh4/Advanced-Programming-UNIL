#pragma once
#include "Fauna.h"
#include "Flora.h"
class Predator : public Fauna
{
	public:
		Predator(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
			int mySpeed, float myHungerSensitivity,
			float myMetabolicRate, float myLustLevel, float myVisionRange);

		virtual float computeUtility(float distance, Organism* organism);

		virtual void interact(Organism* organism, std::vector<Organism*>& organismVector);

		//virtual float computeUtility(float distance, Flora* flora);
};

