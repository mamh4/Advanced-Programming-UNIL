#pragma once
#include "Organism.h"
#include <SFML/Graphics.hpp>
class Flora : public Organism
{
private:
	float growthRate;
	const float maxEnergy = 100;
	
public:
	Flora(float myPosX, float myPosY, float myRadius, float myEnergy, float myGrowthRate);

	void update();
};
