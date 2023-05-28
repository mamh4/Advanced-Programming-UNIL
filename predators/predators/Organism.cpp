#include "Organism.h"



Organism::Organism(float myPosX, float myPosY, float myRadius, float myEnergy) {

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
	this->shape.setPosition(myPosX, this->getPosY());
	this->posX = myPosX;
}

float Organism::getPosY() {
	return this->posY;
}

void Organism::setPosY(float myPosY) {
	this->shape.setPosition(this->getPosX(), myPosY);
	this->posY = myPosY;
}

float Organism::getRadius() {
	return this->radius;
}

void Organism::setRadius(float myRadius) {
	this->shape.setRadius(myRadius);
	this->shape.setOrigin(myRadius, myRadius);
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

void Organism::die(std::vector<Organism*>& organismVector) {
}
