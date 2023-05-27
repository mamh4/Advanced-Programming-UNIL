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

    float maxEnergyDensity = 500.0 ; 

	void Flora::update(std::vector<Organism*>& organismVector) {
    //std::cout << "I am a plant and I am Updating " << std::endl ; 
    float maxEnergy = maxEnergyDensity*this->getRadius(); 
    

	this->setEnergy( std::min( maxEnergy, (this->getEnergy() +  this->getGrowthRate() )) );
  
    //totalEnergyFlora += std::min(maxEnergy * this->getRadius(), (this->getEnergy() + this->getGrowthRate()));

    // vvv COLOR AS A FUNCTION OF ENERGY vvv
    sf::CircleShape newShape; 
    newShape = this->getShape(); 
    int newColorCode ;
    float approximateColorCode ; 
    if (this->getEnergy() <= 0 ){
        approximateColorCode = 100.0 ; 
    }
    else if (this->getEnergy()  <=  maxEnergy * this->getRadius() ) {
        approximateColorCode = 150.0 - (this->getEnergy()*150.0/(maxEnergy * this->getRadius())) ; 
       // std::cout << "My energy is " << this->getEnergy() << " which is the following percentage of the max " << (this->getEnergy()*100.0/(maxEnergy * this->getRadius())) << std::endl; 
    }
    else {
        approximateColorCode = 0.0 ; 
    }
    newColorCode = static_cast<int> (approximateColorCode ); 
    newColorCode = newColorCode % 256 ; 
    uint8_t actualColorCode ; 
    actualColorCode = newColorCode ; 
    // std::cout << "actual Color Code is now " << actualColorCode << std::endl ; 
    newShape.setFillColor(sf::Color::Color( actualColorCode , 255, actualColorCode , 255 )); 
    // newShape.setOutlineThickness (0.5); 
    // newShape.setOutlineColor(sf::Color::Color( 50+ actualColorCode , 255, 50+ actualColorCode , 255 )); 
    this->setShape(newShape);
    // ^^^ COLOR AS A FUNCTION OF ENERGY ^^^

	}

