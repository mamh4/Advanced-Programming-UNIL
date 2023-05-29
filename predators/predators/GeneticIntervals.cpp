#include "GeneticIntervals.h"
#include <string>
#include <vector>

//Parameters for the fauna defined for each class. example speed (slowest is 0.5, highest is 1.5) for for class 1, 1.5 to 2.5 for class 2, 2.5 to 3.5 for class 3
GeneticTraitInterval preySpeedRange = {
    "Speed",
    {0.5 , 1.5 , 2.5 , 3.5 }
};

GeneticTraitInterval preyHungerSensitivityRange = {
    "Hunger Sensitivity",
   {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval preyMetabolicRateRange = {
    "Metabolic Rate",
    {1.0,  1.5 , 2.0 , 2.5}
};

GeneticTraitInterval preyLustLevelRange = {
    "Lust Level",
    {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval preyVisionRangeRange = {
    "Vision Range",
     {100.0 , 150.0 , 200.0 , 250.0 }
};

GeneticTraitInterval preyPredatorAversionRange = {
    "Predator Aversion",
    {0.0 , 0.25 , 0.75 , 1.0 }
};

//PREDATOR GENETIC TRAIT INTERVAL 

GeneticTraitInterval predatorSpeedRange = {
    "Speed",
    {0.5 , 2.5 , 3.5 , 5.5 }
};

GeneticTraitInterval predatorHungerSensitivityRange = {
    "Hunger Sensitivity",
    {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval predatorMetabolicRateRange = {
    "Metabolic Rate",
    {1.0,  1.5 , 2.0 , 2.5}
};

GeneticTraitInterval predatorLustLevelRange = {
    "Lust Level",
     {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval predatorVisionRangeRange = {
    "Vision Range",
    {250.0 , 300.0 , 400.0 , 450.0 }
};

// SPECIED GENETIC TRAITS INTERVALS 

SpeciesGeneticTraitsIntervals preyGeneticTraitIntervals = {
    "Prey" ,
    {preySpeedRange, preyHungerSensitivityRange, preyMetabolicRateRange, preyLustLevelRange, preyVisionRangeRange, preyPredatorAversionRange }
};

SpeciesGeneticTraitsIntervals predatorGeneticTraitIntervals = {
     "Predator",
    {predatorSpeedRange, predatorHungerSensitivityRange, predatorMetabolicRateRange, predatorLustLevelRange, predatorVisionRangeRange }
};

// GENETICS DATABASE 

std::vector<SpeciesGeneticTraitsIntervals> geneticDatabase = { preyGeneticTraitIntervals, predatorGeneticTraitIntervals };