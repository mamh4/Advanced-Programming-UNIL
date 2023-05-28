#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Organism.h"
#define M_PI 3.14159265358979323846
#define angleSectionNumber 12
#define stepSize  1.0

float distanceSquared (Organism* target1 , Organism* target2 ) ;

float l2NormSquared (Organism* target) ;

float angle (Organism* target1 , Organism* target2) ;


int angleSorting (float angle) ;

float proximityEffectFactor (float lowerRange, float upperRange, float evaluationPoint); 

