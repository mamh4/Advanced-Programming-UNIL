#include <cmath>
#include "Organism.h"
#include "OrganicMaths.h"
#include <SFML/Graphics.hpp>


//Distance between two organisms squared
float distanceSquared (Organism* target1 , Organism* target2 ) {
    return std::pow(target1->getPosX() - target2->getPosX(), 2) + std::pow(target1->getPosY() - target2->getPosY(), 2);
}
//Distance between self and a target organism squared.
float l2NormSquared (Organism* target) {
    return std::pow(target->getPosX(),2) + std::pow(target->getPosY(),2);
}

//The angle between two organisms in degrees
float angle (Organism* target1 , Organism* target2) {
    float target1Norm ;
    float target2Norm ; 
    target1Norm = sqrt( l2NormSquared(target1) ); 
    target2Norm = sqrt( l2NormSquared(target2) ); 

    float xcoord = target2->getPosX() - target1->getPosX(); 
    float ycoord = target2->getPosY() - target1->getPosY(); 
    float newNorm = sqrt (pow(xcoord, 2 ) + pow(ycoord, 2 )) ; 



    if (newNorm == 0.0  ) {
        return 0.0 ;
    } 
    else {
            
        float phi = acos(xcoord / newNorm);
        if (ycoord >=0 ){ 
                return phi ; 
        }
        else {
                return 2*M_PI - phi ; 
        }
    }
}

//Convert angle in degrees to an an angle section. In our implementation 12.
int angleSorting (float angle) {
    int angleSectionCounter;
    angleSectionCounter=0; 
    float adjustedAngle ; 
    adjustedAngle = angle ; 
    while (adjustedAngle < 0 ) {
        adjustedAngle += 2* M_PI ; 
    }
    while  (not ( (adjustedAngle >= (angleSectionCounter *1.0)*2*M_PI/angleSectionNumber ) and
        (adjustedAngle <  (angleSectionCounter *1.0 + 1.0)*2*M_PI/angleSectionNumber ) ) ){
        angleSectionCounter++ ; 
    }
    angleSectionCounter = angleSectionCounter % angleSectionNumber ; 
    return angleSectionCounter; 
}


// A weight to is assigned how far away an organism is from another organism. Lower range is normally 0 i.e. within interaction range.
// Upper range is normally the vision range of the organism.
float proximityEffectFactor (float lowerRange, float upperRange, float evaluationPoint) {
    
    if (evaluationPoint < lowerRange ) {
        return 1.0; 
    }
    else if (evaluationPoint > upperRange ) {
        return 0.0; 
    }
    else {
    float x ; 
    x= (evaluationPoint - lowerRange)/(upperRange - lowerRange ) ; 
    return (std::pow(1.0 - x , 2)) ;
    } 
} 
