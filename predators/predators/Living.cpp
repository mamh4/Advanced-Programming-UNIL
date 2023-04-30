
#include "Living.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Living::Living(Vector2D myPosition, float radius_ , float energy_)
: pos(pos_), radius(radius_), energy(energy_)
{}

Living::~Living ()
{}

const float Living::getRadius ()
{
return radius;
}

	const Vector2D getPos()
{
return pos;
}