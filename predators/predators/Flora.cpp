#include "Flora.h"
	
	Flora::Flora(float myPosX, float myPosY, float myRadius, int myEnergy, float myGrowthRate) :
		Organism(myPosX, myPosY, myRadius, myEnergy) {
		shape.setFillColor(sf::Color::Green);
	}

	void Flora::update() {
		Flora::energy = std::min(Flora::maxEnergy * Flora::getShape().getRadius(), (energy * growthRate + 1));
	}
