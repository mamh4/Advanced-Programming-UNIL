#include "Flora.h"
	
	Flora::Flora(float myPosX, float myPosY, float myRadius, float myEnergy, float myGrowthRate) :
		Organism(myPosX, myPosY, myRadius, myEnergy) {
		growthRate = myGrowthRate;
		shape.setFillColor(sf::Color::Green);
	}

	void Flora::update() {
		this->energy = std::min(this->maxEnergy * this->getRadius(), (energy * growthRate + 1));
	}

