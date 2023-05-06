#include "Flora.h"
//#include <stdint.h>
	
	Flora::Flora(float myPosX, float myPosY, float myRadius, float myEnergy, float myGrowthRate) :
		Organism(myPosX, myPosY, myRadius, myEnergy) {
		growthRate = myGrowthRate;
		shape.setFillColor(sf::Color::Green);
	}

    float Flora::getGrowthRate() {
		return this->growthRate;
	}

	void Flora::update(std::vector<Organism*>& organismVector) {
    std::cout << "I am a plant and I am Updating " << std::endl ; 
    float maxEnergy = 500.0 ; 
    
	this->setEnergy( std::min( maxEnergy * this->getRadius(), (this->getEnergy() +  this->getGrowthRate() )) );

    sf::CircleShape newShape;
    newShape = this->getShape(); 

    int newColorCode ;
    float approximateColorCode ; 
    if (this->getEnergy() <= 0 ){
        approximateColorCode = 100.0 ; 
    }
    else if (this->getEnergy()  <=  maxEnergy * this->getRadius() ) {
        approximateColorCode = 100.0 + (this->getEnergy()*155.0/(maxEnergy * this->getRadius())) ; 
        std::cout << "My energy is " << this->getEnergy() << " which is the following percentage of the max " << (this->getEnergy()*100.0/(maxEnergy * this->getRadius())) << std::endl; 
    }
    else {
        approximateColorCode = 255.0 ; 
    }
    newColorCode = static_cast<int> (approximateColorCode ); 
    newColorCode = newColorCode % 256 ; 
    uint8_t actualColorCode ; 
    actualColorCode = newColorCode ; 
    std::cout << "actual Color Code is now " << actualColorCode << std::endl ; 
    newShape.setFillColor(sf::Color::Color( 0 , actualColorCode, 0 , 255 )); 
    this->setShape(newShape);

	}

