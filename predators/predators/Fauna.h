#pragma once
#include "Organism.h"
#include <SFML/Graphics.hpp>
class Fauna : public Organism
{
private:
    bool sex;
    float speed;
    int age;
    float hungerSensitivity;
    float metabolicRate;
    float lustLevel;
    float visionRange;
    bool fertile;
protected:
    static const int rangeOfInteraction = 2;
    //static const float stepSize = 1.0;
public:
    Fauna(float myPosX, float myPosY, float myRadius, float myEnergy,bool mySex,
        int mySpeed, float myHungerSensitivity,
        float myMetabolicRate, float myLustLevel, float myVisionRange);

    virtual ~Fauna() {};

    int getSpeed();

    void setSpeed();

    int getAge();

    void setAge(int age);

    bool getSex();

    float getHungerSensitivity();

    void setHungerSensitivity(float hungerSensitivity);

    float getMetabolicRate();

    void setMetabolicRate(float metabolicRate);

    float getLustLevel();

    void setLustLevel(float lustLevel);

    float getVisionRange();

   // virtual void computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, float& maxDirectionalUtility, int maxDirectionalUtilityTarget, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget);

    virtual void computeUtility(float distanceSquared, Organism* targetOrganism, std::vector<float>& directionalUtility, std::vector<Organism*>& possibleCollisions, float& maxInteractionUtility, Organism*& maxInteractionUtilityTarget);

    void move(int direction);

    void ageing();

    bool getFertile() {
        return this->fertile;
    }
    void setFertile(bool fertile){
        this->fertile = fertile;
        }

    virtual void update(std::vector<Organism*>& organismVector);

    virtual void interact(Organism* organism, std::vector<Organism*>& organismVector);

    virtual void dies(std::vector<Organism*>& organismVector);


};

