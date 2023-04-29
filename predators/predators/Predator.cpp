#include "Predator.h"
#include "Animal.h"
#include <SFML/Graphics.hpp>

Predator::Predator(float myPosX, float myPosY, float myRadius, bool mySex,
	int mySpeed, int myAge, int myStaminaLevel, int myHungerLevel,
	float myMetabolicRate, int myLustLevel, int myVisionRange) : Animal(myPosX, myPosY, myRadius, mySex,
		mySpeed, myAge, myStaminaLevel, myHungerLevel,
		myMetabolicRate, myLustLevel, myVisionRange) {
	shape.setFillColor(sf::Color::Red);
}