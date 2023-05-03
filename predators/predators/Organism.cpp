#include "Organism.h"



	Organism::Organism(float myPosX, float myPosY, float myRadius,float myEnergy) {

		energy = myEnergy;

		posX = myPosX;
		posY = myPosY;
		radius = myRadius;
		shape.setRadius(myRadius);
		shape.setOrigin(myRadius, myRadius);
		shape.setPosition(myPosX, myPosY);
	}

	float Organism::getPosX() {
		return this->posX;
	}

	void Organism::setPosX(float myPosX) {
		this->shape.setPosition(myPosX, Organism::shape.getPosition().y);
		this->posX = myPosX;
	}

	float Organism::getPosY() {
		return this->posY;
	}

	void Organism::setPosY(float myPosY) {
		this->shape.setPosition(Organism::shape.getPosition().x, myPosY);
		this->posY = myPosY;
	}

	float Organism::getRadius() {
		return this->radius;
	}

	void Organism::setRadius(float myRadius) {
		Organism::shape.setRadius(myRadius);
		Organism::shape.setOrigin(myRadius, myRadius);
		this->radius = myRadius;
	}

	float Organism::getEnergy() {
		return this->energy;
	}

	void Organism::setEnergy(float myEnergy) {
		this->energy = myEnergy;
	}

	sf::CircleShape Organism::getShape() {
		return this->shape;
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
