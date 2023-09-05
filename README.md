# Prey-Predator Simulation
In this project, we propose to simulate the behaviour of preys and predators with the aim to study the influence of certain parameters on the flourishing of their respective populations. To this end, we consider a set of creatures evolving in a planar environment that compete for resources in order to insure their survival. The behaviour of said creatures is simulated in real time through the maximization of their individual utilities, expressed as a function of their environment as well as their idiosyncratic attributes. Among the environmental decision making criteria are the proximity of the creature to preys, predators and resources. In conjunction with these external parameters, the attributes of the creature in question, such as its energy levels, physical capabilities and behavioral inclinations, intervene in the determination of the action it prefers to undertake next. The first option with an affordable energy cost within the list of possible actions ordered by their associated utility is then performed. Once survival of the creatures is ensured, secondary needs, such as reproduction, take a more predominant role in the decision making process. This mechanic in particular allows the generation of new creatures in the simulation, whose attributes are passed on from their parents. We then plan to monitor various trends within populations in order to get insight as to the prevalence of given traits and their impact on survival.
## System Requirements

- x86/x64 CPU Architecture.

## Installation
Download the folder [Advanced-Programming-UNIL/predators/Release](https://github.com/mamh4/Advanced-Programming-UNIL/tree/main/predators/Release) and double click 'predators.exe'.

## Running the simulation
Upon double clicking the 'predators.exe' a small input window would open for the simulation parameters. Tap the input window and plug-in the desired parameters.

![mainmenu (1)](https://github.com/mamh4/Advanced-Programming-UNIL/assets/57665567/036edc7b-d993-4d32-8869-272dc2fadc78)

![simulationWindow (1)](https://github.com/mamh4/Advanced-Programming-UNIL/assets/57665567/23c6a16a-e5e5-4466-9a7b-fe9531cc84c6)


![deathSummary](https://github.com/mamh4/Advanced-Programming-UNIL/assets/57665567/e36ca617-9b39-4564-a361-f51318ec88b8)


## Implementation

![hopefullyLastUML](https://github.com/mamh4/Advanced-Programming-UNIL/assets/57665567/3fc32712-ed46-4208-a187-e20a7968f2fc)


## Adjusting the parameters
Adjustemnet to further parameters requires re-running the code after adjusting either the 'GeneticIntervals.cpp' file or the 'Gameboard.cpp' file.

The individual population parameters (e.g. Speed, Vision Range, Hunger Level,...etc) can be found and adjusted inside the GeneticIntervals.cpp file. The input Energy levels for Flora can be adjusted in the Gameboard.cpp file under 'Variable Initialisations'.





