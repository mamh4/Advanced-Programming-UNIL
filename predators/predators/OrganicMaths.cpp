#include <cmath>
#include "Organism.h"
#define M_PI 3.14159265358979323846

float distanceSquared (Organism* target1 , Organism* target2 ) {
    return std::pow(target1->getShape().getPosition().x - target2->getShape().getPosition().x,2) + std::pow(target1->getShape().getPosition().y - target2->getShape().getPosition().y,2);
//    return std::pow(target1->getShape().getPosition().x - target2->getShape().getPosition().x,2) + std::pow(target1->getShape().getPosition().y - target2->getShape().getPosition().y,2);
}

float l2NormSquared (Organism* target) {
    return std::pow(target->getShape().getPosition().x,2) + std::pow(target->getShape().getPosition().y,2);
}

//float alternativeAngle (Organism* target1 , Organism* target2) {
//   return target1->getShape().getPosition().angle(target2->getShape().getPosition()); 
//}

float angle (Organism* target1 , Organism* target2) {
    float target1Norm ;
    float target2Norm ; 
    target1Norm = sqrt( l2NormSquared(target1) ); 
    target2Norm = sqrt( l2NormSquared(target2) ); 
    if ( target1Norm != 0 and  target2Norm != 0 ){
        return acos( (target1->getShape().getPosition().x*target2->getShape().getPosition().x + target1->getShape().getPosition().y*target2->getShape().getPosition().y) / (1.0 * target1Norm * target2Norm));
    }
    else if  ( target1Norm != 0 ){
        return acos( target1->getShape().getPosition().x / target1Norm  ) ; 
    }
    else if  ( target2Norm != 0 ){
        return acos( target2->getShape().getPosition().x / target2Norm  ) ; 
    }
    else {
        return 0; 
    }
}

// acos gives in 0 pi range 
int angleSorting (float angle) {
    int angleSectionNumber;
    angleSectionNumber=12; 
    int angleSectionCounter;
    angleSectionCounter=0; 
    while  (not ( (angle >= (angleSectionCounter *1.0)*M_PI/angleSectionNumber ) and (angle <  (angleSectionCounter *1.0 + 1.0)*M_PI/angleSectionNumber ) ) ){
        angleSectionCounter++ ; 
    }
    return angleSectionCounter; 
}

// shift factor from 1/n 
float proximityEffectFactor (float lowerRange, float upperRange, float shiftFactor, float evaluationPoint) {
    if (evaluationPoint < lowerRange ) {
        return 1.0; 
    }
    else if (evaluationPoint > upperRange ) {
        return 1.0; 
    }
    else {
    return 0.5 - 0.5*(atan(10 *(-0.5 + pow((( evaluationPoint - lowerRange )/ (upperRange - lowerRange) ), shiftFactor)  ) ) /(M_PI*0.43717)) ;  
    } 
} 