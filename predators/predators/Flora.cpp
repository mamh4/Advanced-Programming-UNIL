#include "Flora.h"
//#include <stdint.h>
	
	Flora::Flora(float myPosX, float myPosY, float myRadius, float myEnergy, float myGrowthRate) :
		Organism(myPosX, myPosY, myRadius, myEnergy) {
		growthRate = myGrowthRate;
		shape.setFillColor(sf::Color::Green);
	}

	void Flora::update() {
		this->energy = std::min(this->maxEnergy * this->getRadius(), (energy * growthRate + 1));

    sf::CircleShape newShape;
    newShape = this->getShape(); 
    int newColorCode ;
    float approximateColorCode ; 
    if (this->getEnergy() <= 0 ){
        approximateColorCode = 100.0 ; 
    }
    else if (this->getEnergy()  <=  1000.0 ) {
        approximateColorCode = 100.0 + (getEnergy()*155.0/1000.0) ; 
    }
    else {
        approximateColorCode = 255.0 ; 
    }
    newColorCode = static_cast<int> (approximateColorCode ); 
    newShape.setFillColor(sf::Color::Color( 0 , 0, newColorCode, 255 )); 
    this->setShape(newShape);

	}

