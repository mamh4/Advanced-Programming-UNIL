#pragma once
//#ifndef ORGANICMATHS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ORGANICMATHS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Organism.h"
#define M_PI 3.14159265358979323846
#define angleSectionNumber 12
#define stepSize  1.0

float distanceSquared (Organism* target1 , Organism* target2 ) ;

float l2NormSquared (Organism* target) ;

float angle (Organism* target1 , Organism* target2) ;

// acos gives in 0 pi range 
int angleSorting (float angle) ;
// shift factor from 1/n 
//float proximityEffectFactor (float lowerRange, float upperRange, float shiftFactor, float evaluationPoint); 

float proximityEffectFactor (float lowerRange, float upperRange, float evaluationPoint); 


//#endif

