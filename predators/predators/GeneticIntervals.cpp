#include "GeneticIntervals.h"
#include <string>
#include <vector>

GeneticTraitInterval preySpeedRange = {
    "Speed",
    {0.5 , 2.5 , 4.5 , 6.5 }
};

GeneticTraitInterval preyHungerSensitivityRange = {
    "Hunger Sensitivity",
    {0.2 , 0.5 , 2 , 5 }
};

GeneticTraitInterval preyMetabolicRateRange = {
    "Metabolic Rate",
    {0.0,  0.25 , 0.75 , 1}
};

GeneticTraitInterval preyLustLevelRange = {
    "Lust Level",
    {0.2 , 0.5 , 2 , 5 }
};

GeneticTraitInterval preyVisionRangeRange = {
    "Vision Range",
    {175.0 , 225.0 , 275.0 , 325.0 }
};

GeneticTraitInterval preyPredatorAversionRange = {
    "Predator Aversion",
    {0.2 , 0.5 , 2 , 5 }
};

//PREDATOR GENETIC TRAIT INTERVAL 

GeneticTraitInterval predatorSpeedRange = {
    "Speed",
    {0.5 , 2.5 , 4.5 , 6.5 }
};

GeneticTraitInterval predatorHungerSensitivityRange = {
    "Hunger Sensitivity",
    {0.2 , 0.5 , 2 , 5 }
};

GeneticTraitInterval predatorMetabolicRateRange = {
    "Metabolic Rate",
    {0.0,  0.25 , 0.75 , 1}
};

GeneticTraitInterval predatorLustLevelRange = {
    "Lust Level",
    {0.2 , 0.5 , 2 , 5 }
};

GeneticTraitInterval predatorVisionRangeRange = {
    "Vision Range",
    {175.0 , 225.0 , 275.0 , 325.0 }
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