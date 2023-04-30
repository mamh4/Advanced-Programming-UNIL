#include "Organism.h"


	Organism::Organism(float myPosX, float myPosY, float myRadius,float myEnergy) {

		energy = myEnergy;

		shape.setRadius(myRadius);
		shape.setOrigin(myRadius, myRadius);
		shape.setPosition(myPosX, myPosY);
	}

	float Organism::getEnergy() {
		return Organism::energy;
	}

	void Organism::setEnergy(float myEnergy) {
		this->energy = myEnergy;
	}

	sf::CircleShape Organism::getShape() {
		return Organism::shape;
	}

	void Organism::setShape(sf::CircleShape shape) {
		this->shape = shape;
	}

	std::string Organism::getType() {
		return typeid(*this).name();
	}

	void Organism::update(std::vector<Organism*> organismVector) {
	}
