#include "Organism.h"

	Organism::Organism(float myPosX, float myPosY, float myRadius,int myEnergy) {

		energy = myEnergy;

		shape.setRadius(myRadius);
		shape.setOrigin(myRadius, myRadius);
		shape.setPosition(myPosX, myPosY);
	}

	int Organism::getEnergy() {
		return Organism::energy;
	}

	void Organism::setEnergy(int myEnergy) {
		this->energy = myEnergy;
	}

	sf::CircleShape Organism::getShape() {
		return Organism::shape;
	}

	void Organism::setShape(sf::CircleShape shape) {
		this->shape = shape;
	}