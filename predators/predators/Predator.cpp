#include "Predator.h"
#include <SFML/Graphics.hpp>

Predator::Predator(float myPosX, float myPosY, float myRadius, int myEnergy,bool mySex,
	int mySpeed, int myAge, int myHungerLevel,
	float myMetabolicRate, int myLustLevel, int myVisionRange) : Fauna(myPosX, myPosY,myRadius, myEnergy, 
		mySex, mySpeed, myAge, myHungerLevel,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Red);
}