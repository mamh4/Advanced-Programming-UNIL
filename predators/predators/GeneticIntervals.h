#pragma once
#include <string>
#include <vector>

//STRUCTURE DEFINITION 

struct GeneticTraitInterval {
    std::string traitName;
    std::vector<float> traitRange;
};

struct SpeciesGeneticTraitsIntervals {
    std::string speciesName;
    std::vector<GeneticTraitInterval> geneticTraitIntervals;
};


//PREY GENETIC TRAIT INTERVAL 

extern GeneticTraitInterval preySpeedRange;

extern GeneticTraitInterval preyHungerSensitivityRange;

extern GeneticTraitInterval preyMetabolicRateRange;

extern GeneticTraitInterval preyLustLevelRange;

extern GeneticTraitInterval preyVisionRangeRange;

extern GeneticTraitInterval preyPredatorAversionRange;

//PREDATOR GENETIC TRAIT INTERVAL 

extern GeneticTraitInterval predatorSpeedRange;

extern GeneticTraitInterval predatorHungerSensitivityRange;

extern GeneticTraitInterval predatorMetabolicRateRange;

extern GeneticTraitInterval predatorLustLevelRange;

extern GeneticTraitInterval predatorVisionRangeRange;

// SPECIED GENETIC TRAITS INTERVALS 

extern SpeciesGeneticTraitsIntervals preyGeneticTraitIntervals;

extern SpeciesGeneticTraitsIntervals predatorGeneticTraitIntervals;

// GENETICS DATABASE 

extern std::vector<SpeciesGeneticTraitsIntervals> geneticDatabase;