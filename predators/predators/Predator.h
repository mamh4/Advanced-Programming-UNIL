#pragma once
#include "Fauna.h"
class Predator : public Fauna
{
	public:
		Predator(float myPosX, float myPosY, float myRadius, int myEnergy, bool mySex,
			int mySpeed, int myAge, int myHungerLevel,
			float myMetabolicRate, int myLustLevel, int myVisionRange);

};

