#include "Vector2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#pragma once
#ifndef PRJ_Living_H
#define PRJ_Living_H

class Living {
	
	public:
//~ PUBLIC

// Initialization
	Vector2D(Vector2D pos = {0,0}, double y =0);

    virtual ~Living ();

// Set
	void setPos(boolean coord_select, double coord);

// Get
	const Vector2D getPos() const;
    const float getRadius() const;
    const bool getFloraFauna() const;

// Color determination 
    virtual sf::Color detColor() const = 0 ; 

	protected:
//~ PRIVATE
	
// Attributes
    Vector2D pos; 
    float radius;
    bool floraFauna;
	};

#endif // PRJ_Living_H