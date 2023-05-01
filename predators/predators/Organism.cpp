#include "Organism.h"



	Organism::Organism(float myPosX, float myPosY, float myRadius,float myEnergy) {

		energy = myEnergy;

		shape.setRadius(myRadius);
		shape.setOrigin(myRadius, myRadius);
		shape.setPosition(myPosX, myPosY);
	}

	float Organism::getPosX() {
		return Organism::shape.getPosition().x;
	}

	void Organism::setPosX(float myPosX) {
		Organism::shape.setPosition(myPosX, Organism::shape.getPosition().y);
		this->posX = myPosX;
	}

	float Organism::getPosY() {
		return Organism::shape.getPosition().y;
	}

	void Organism::setPosY(float myPosY) {
		Organism::shape.setPosition(Organism::shape.getPosition().x, myPosY);
		this->posY = myPosY;
	}

	float Organism::getRadius() {
		return Organism::shape.getRadius();
	}

	void Organism::setRadius(float myRadius) {
		Organism::shape.setRadius(myRadius);
		Organism::shape.setOrigin(myRadius, myRadius);
		this->radius = myRadius;
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

	void Organism::update(std::vector<Organism*>& organismVector) {
	}

	void Organism::dies(std::vector<Organism*>& organismVector) {
	}
