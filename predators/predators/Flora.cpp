#include "Flora.h"
#include "OrganicStats.h"
	
Flora::Flora(float myPosX, float myPosY, float myRadius, float myEnergy, float myGrowthRate) :
    Organism(myPosX, myPosY, myRadius, myEnergy) {
    growthRate = myGrowthRate;
    shape.setFillColor(sf::Color::Green);
    numberOfFlora += 1;
}

float Flora::getGrowthRate() {
    return this->growthRate;
}

//Flora energy is based on its Radius. Colour changes based on energy.
//Flora grows each turn but cannot exceed the maxEnergy.
void Flora::update(std::vector<Organism*>& organismVector) {
    float maxEnergyDensity = 500.0;
    float maxEnergy = maxEnergyDensity * this->getRadius();


    this->setEnergy(std::min(maxEnergy, (this->getEnergy() + this->getGrowthRate())));

    sf::CircleShape newShape;
    newShape = this->getShape();
    int newColorCode;
    float approximateColorCode;
    if (this->getEnergy() <= 0) {
        approximateColorCode = 100.0;
    }
    else if (this->getEnergy() <= maxEnergy * this->getRadius()) {
        approximateColorCode = 150.0 - (this->getEnergy() * 150.0 / (maxEnergy * this->getRadius()));
    }
    else {
        approximateColorCode = 0.0;
    }
    newColorCode = static_cast<int> (approximateColorCode);
    newColorCode = newColorCode % 256;
    uint8_t actualColorCode;
    actualColorCode = newColorCode;
    newShape.setFillColor(sf::Color::Color(actualColorCode, 255, actualColorCode, 255));
    this->setShape(newShape);

}

