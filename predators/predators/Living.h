#include "Vector2D.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#pragma once
#ifndef PRJ_Living_H
#define PRJ_Living_H

class Living {
protected:
	Vector2D pos;
	float radius;
	float energy;
	
	public:
	Living(Vector2D pos_, float radius_, float energy_);

    virtual ~Living ();

// Set
	void setPos(bool coord_select, double coord);

// Get
	const Vector2D getPos() const;
    const float getRadius() const;

// Type determination 
    virtual bool detFloraFauna() const;

// Color determination 
    virtual sf::Color detColor() const = 0 ; 


// Update
    virtual void update(); 
	};

#endif // PRJ_Living_H