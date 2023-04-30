#include "Vector2D.h"
#include "Living.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#pragma once
#ifndef PRJ_Vegetation_H
#define PRJ_Vegetation_H
class Vegetation : public Living 
{
	public:
//~ PUBLIC

// Initialization
	Vegetation(Vector2D pos_ = {0,0}, float radius_ =0, float energy_, float growthRate_);

    virtual ~Living ();

// Type determination 
    virtual bool detFloraFauna() const override;

// Color determination 
    virtual sf::Color detColor() const override = 0 ; 

// Update
    virtual void update() override; 

	protected:
//~ PROTECTED
	
// Attributes
    float growthRate; 
    static float maxEnergyDensity ;

    private :
//~ PRIVATE

};

#endif // PRJ_Vegetation_H