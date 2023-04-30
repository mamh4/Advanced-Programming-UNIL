#pragma once
#include "Fauna.h"
#include "Flora.h"
class Predator : public Fauna
{
	public:
		Predator(float myPosX, float myPosY, float myRadius, float myEnergy, bool mySex,
			int mySpeed, int myAge, int myHungerLevel,
			float myMetabolicRate, int myLustLevel, float myVisionRange);
		
		virtual void update(std::vector<Fauna*> organismVector);

		virtual float computeUtility(float distance, Fauna* fuana);

		virtual float computeUtility(float distance, Flora* flora);
};

