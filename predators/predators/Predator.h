#pragma once
#include "Animal.h"
class Predator : public Animal
{
	private:
		sf::Color color;
		sf::CircleShape shape;
	public:
		Predator(float myPosX, float myPosY, float myRadius, bool mySex,
			int mySpeed, int myAge, int myStaminaLevel, int myHungerLevel,
			float myMetabolicRate, int myLustLevel, int myVisionRange);

};

