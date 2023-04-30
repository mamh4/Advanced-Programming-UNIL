
#include "Vegetation.h"
#include "Vector2D.h"
#include "Living.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

Vegetation::Vegetation(Vector2D pos_, float radius_, float energy_, float growthRate_) : Living(pos_, radius_, energy_), growthRate(growthRate_)
{}

Vegetation::~Vegetation()
{}

bool Vegetation::detFloraFauna() {
    return true;
}

sf::Color Vegetation::detColor() {
    retun sf::Color::Green;
}

void Vegetation::update() {
    energy = min((maxEnergyDensity * radius), (energy * growthRate + 1))
}

//arbitrary constant 
float Vegetation::maxEnergyDensity(100);