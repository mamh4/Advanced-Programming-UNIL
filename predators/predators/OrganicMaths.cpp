#include <cmath>
#include "Organism.h"
#include "OrganicMaths.h"
#include <SFML/Graphics.hpp>

float distanceSquared (Organism* target1 , Organism* target2 ) {
    return std::pow(target1->getPosX() - target2->getPosX(), 2) + std::pow(target1->getPosY() - target2->getPosY(), 2);
//    return std::pow(target1->getShape().getPosition().x - target2->getShape().getPosition().x,2) + std::pow(target1->getShape().getPosition().y - target2->getShape().getPosition().y,2);
}

float l2NormSquared (Organism* target) {
    return std::pow(target->getPosX(),2) + std::pow(target->getPosY(),2);
}

//float alternativeAngle (Organism* target1 , Organism* target2) {
//   return target1->getShape().getPosition().angle(target2->getShape().getPosition()); 
//}

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
 /*/
    if ()
    if ( target1Norm != 0 and  target2Norm != 0 ){
        return acos( ( target2->getPosX() - target1->getPosX() + target1->getPosY()*target2->getPosY()) / (1.0 * target1Norm * target2Norm));

        return acos( (target1->getPosX() *target2->getPosX() + target1->getPosY()*target2->getPosY()) / (1.0 * target1Norm * target2Norm));
    }
    else if  ( target1Norm != 0 ){
        return acos( target1->getPosX() / target1Norm  ) ;
    }
    else if  ( target2Norm != 0 ){
        return acos( target2->getPosX() / target2Norm  ) ;
    }
    else {
        return 0; 
    }
    /*/
}

// acos gives in 0 pi range 
int angleSorting (float angle) {
    int angleSectionCounter;
    angleSectionCounter=0; 
    float adjustedAngle ; 
    adjustedAngle = angle ; 
    while (adjustedAngle < 0 ) {
        adjustedAngle += 2* M_PI ; 
    }
    while  (not ( (adjustedAngle >= (angleSectionCounter *1.0)*2*M_PI/angleSectionNumber ) and (adjustedAngle <  (angleSectionCounter *1.0 + 1.0)*2*M_PI/angleSectionNumber ) ) ){
        angleSectionCounter++ ; 
    }
    angleSectionCounter = angleSectionCounter % angleSectionNumber ; 
    return angleSectionCounter; 
}

// shift factor from 1/n 
float proximityEffectFactor (float lowerRange, float upperRange, float shiftFactor, float evaluationPoint) {
    
    if (evaluationPoint < lowerRange ) {
        return 1.0; 
    }
    else if (evaluationPoint > upperRange ) {
        return 0.0; 
    }
    else {
   // return 0.5 - 0.5*(atan(10 *(-0.5 + pow((( evaluationPoint - lowerRange )/ (upperRange - lowerRange) ), shiftFactor)  ) ) /(M_PI*0.43717)) ;  
    float x ; 
    // float compensationFactor = atan(2.0 ) ; 
    x= (evaluationPoint - lowerRange)/(upperRange - lowerRange ) ; 
    return std::pow( x - 1.0, 2) ;
    //return(1.0 - x ) ; 
    //return (1.0  - atan( (x - 0.5)*0.25 )/compensationFactor)/2.0 ; // close to 1 when evaluation point is close to lower range, close to 0 for upper range 
    // how to take shift factor into consideration ? 
    } 
} 
