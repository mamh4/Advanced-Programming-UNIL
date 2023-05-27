#include "GeneticIntervals.h"
#include <string>
#include <vector>

GeneticTraitInterval preySpeedRange = {
    "Speed",
    {0.5 , 1.5 , 2.5 , 3.5 }
};

GeneticTraitInterval preyHungerSensitivityRange = {
    "Hunger Sensitivity",
   // {0.2 , 0.5 , 2 , 5 }
   {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval preyMetabolicRateRange = {
    "Metabolic Rate",
    {1.0,  1.5 , 2.0 , 2.5}
};

GeneticTraitInterval preyLustLevelRange = {
    "Lust Level",
    //{0.2 , 0.5 , 2 , 5 }
    {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval preyVisionRangeRange = {
    "Vision Range",
    //{200.0 , 250.0 , 300.0 , 350.0 }
    //{150.0 , 200.0 , 250.0 , 300.0 }
     {100.0 , 150.0 , 200.0 , 250.0 }
};

GeneticTraitInterval preyPredatorAversionRange = {
    "Predator Aversion",
    //{0.2 , 0.5 , 2 , 5 }
    {0.0 , 0.25 , 0.75 , 1.0 }
};

//PREDATOR GENETIC TRAIT INTERVAL 

GeneticTraitInterval predatorSpeedRange = {
    "Speed",
    //{0.5 , 1.5 , 3.5 , 4.5 }
    {0.5 , 2.5 , 3.5 , 5.5 }//THE HAWK TM
    //{1.5 , 3.5 , 5.5 , 7.5 }      
    //{0.5 , 1.5 , 2.5 , 3.5 } // the regular
};

GeneticTraitInterval predatorHungerSensitivityRange = {
    "Hunger Sensitivity",
    //{0.2 , 0.5 , 2 , 5 }
    {0.0 , 0.25 , 0.75 , 1.0 }
};

GeneticTraitInterval predatorMetabolicRateRange = {
    "Metabolic Rate",
    {1.0,  1.5 , 2.0 , 2.5}
};

GeneticTraitInterval predatorLustLevelRange = {
    "Lust Level",
    //{0.2 , 0.5 , 2 , 5 }
    //{0.0 , 0.25 , 0.75 , 1.0 }
    //{0.75 , 1.0 , 2.0 , 2.25 }
     {0.0 , 0.25 , 0.75 , 1.0 }
    //{0.5 , 1.0 , 2.0 , 2.5 }
    //{0.5 , 1.0 , 1.5 , 2.0 }
    //{0.25 , 0.75 , 1.25 , 1.75 }
};

GeneticTraitInterval predatorVisionRangeRange = {
    "Vision Range",
// THE HAWK TM    
    {250.0 , 300.0 , 400.0 , 450.0 }
    //{250.0 , 350.0 , 450.0 , 550.0 } // TURBO HAWK 
    //{200.0 , 250.0 , 300.0 , 400.0 }
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