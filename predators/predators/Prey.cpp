#include "Prey.h"
#include "Fauna.h"

Prey::Prey(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
	int mySpeed, int myAge, int myHungerLevel,
	float myMetabolicRate, int myLustLevel, int myVisionRange) : Fauna(myPosX, myPosY, myRadius, myEnergy,
		mySex, mySpeed, myAge, myHungerLevel,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Blue);
}