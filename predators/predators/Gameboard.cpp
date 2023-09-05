#include "Gameboard.h"
#include <SFML/Graphics.hpp>
#include "Predator.h"
#include "Prey.h"
#include "Flora.h"
#include <iostream>
#include <string>
#include "OrganicMaths.h"
#include <chrono>
#include <ctime>
#include <cmath>
#include "OrganicStats.h"
#include "OrganicStats.h"
#include <iomanip>
#include <sstream>
#include "GeneticIntervals.h"
#include <random>
#include <thread>

/////////////////////////////////////////////////////////////// Tracking variables for plots and stats /////////////////////////////////////////////////////////////////

int simulationTime = 0;

int numberOfPredators = 0;
int numberOfPrey = 0;
int numberOfFlora = 0;

float totalEnergyPredator=0.0;
float totalEnergyPrey=0.0;
float totalEnergyFlora=0.0;

int numberOfMalePredator = 0;
int numberOfFemalePredator = 0;

int numberOfMalePrey = 0;
int numberOfFemalePrey = 0;


int numberOfFertileFemalePrey = 0;
int numberOfFertileFemalePredator = 0;

int numberOfFertileMalePrey = 0;
int numberOfFertileMalePredator = 0;

float totalAgePredator = 0.0;
float totalAgePrey = 0.0;
float avgAgePredator = 0.0;
float avgAgePrey = 0.0;

/////////////////////////////////////////////////////////// Tracking variables for plots and stats End /////////////////////////////////////////////////////////////////

void startSimulation() {
    ////////////////////////////////////////////////////////////////////// Genetic Engine Data /////////////////////////////////////////////////////////////////////////

/* The input parameters for the initial population is set to be normally distributed around the average values of the genetic intervals. We leverage our implementation
* of the Genetic Intervals class to generate the initial population of prey and predators.
*/
    int averagePredatorSpeed = (geneticDatabase[1].geneticTraitIntervals[0].traitRange[1] + geneticDatabase[1].geneticTraitIntervals[0].traitRange[2]) / 2.0;
    float averagePredatorVisionRange = (geneticDatabase[1].geneticTraitIntervals[4].traitRange[1] + geneticDatabase[1].geneticTraitIntervals[4].traitRange[2]) / 2.0;
    float averagePredatorMetabolicRate = (geneticDatabase[1].geneticTraitIntervals[2].traitRange[1] + geneticDatabase[1].geneticTraitIntervals[2].traitRange[2]) / 2.0;
    float averagePredatorLustLevel = (geneticDatabase[1].geneticTraitIntervals[3].traitRange[1] + geneticDatabase[1].geneticTraitIntervals[3].traitRange[2]) / 2.0;
    float averagePredatorHungerSensitivity = (geneticDatabase[1].geneticTraitIntervals[1].traitRange[1] + geneticDatabase[1].geneticTraitIntervals[1].traitRange[2]) / 2.0;

    int averagePreySpeed = (geneticDatabase[0].geneticTraitIntervals[0].traitRange[1] + geneticDatabase[0].geneticTraitIntervals[0].traitRange[2]) / 2.0;
    float averagePreyVisionRange = (geneticDatabase[0].geneticTraitIntervals[4].traitRange[1] + geneticDatabase[0].geneticTraitIntervals[4].traitRange[2]) / 2.0;
    float averagePreyMetabolicRate = (geneticDatabase[0].geneticTraitIntervals[2].traitRange[1] + geneticDatabase[0].geneticTraitIntervals[2].traitRange[2]) / 2.0;
    float averagePreyLustLevel = (geneticDatabase[0].geneticTraitIntervals[3].traitRange[1] + geneticDatabase[0].geneticTraitIntervals[3].traitRange[2]) / 2.0;
    float averagePreyHungerSensitivity = (geneticDatabase[0].geneticTraitIntervals[1].traitRange[1] + geneticDatabase[0].geneticTraitIntervals[1].traitRange[2]) / 2.0;
    float averagePreyPredatorAversion = (geneticDatabase[0].geneticTraitIntervals[5].traitRange[1] + geneticDatabase[0].geneticTraitIntervals[5].traitRange[2]) / 2.0;

    ////////////////////////////////////////////////////////////////// Genetic Engine Data End ////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////// USER INPUT /////////////////////////////////////////////////////////////////////////////

    /* Here is all the UI code for the user input. We use SFML to create a window with input boxes for the user to input the number of predators, prey and flora.
    We then use our implementation of the Genetic Intervals class to generate the initial population of prey and predators.
    */

    int inputNrPred = 0;
    int inputNrPrey = 0;
    int inputNrFlora = 0;
    const int maxInput = 50;

    sf::RenderWindow windowParam(sf::VideoMode(350, 300), "Main menu");

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");


    // Create a sprite for the background
    sf::Sprite backgroundSprite(backgroundTexture);



    sf::Font font;
    font.loadFromFile("arial.ttf");


    sf::Font font2;
    font2.loadFromFile("aerial.ttf");


    //Number of predators
    sf::Text numberOfPredatorsTxtPrompt;
    numberOfPredatorsTxtPrompt.setFont(font);
    numberOfPredatorsTxtPrompt.setCharacterSize(20);
    numberOfPredatorsTxtPrompt.setFillColor(sf::Color::Black);
    numberOfPredatorsTxtPrompt.setString("Number of predators:");
    numberOfPredatorsTxtPrompt.setPosition(5, 0);

    sf::RectangleShape predatorInputBox(sf::Vector2f(50.f, 20.f));
    predatorInputBox.setFillColor(sf::Color::White);
    predatorInputBox.setOutlineThickness(2.f);
    predatorInputBox.setOutlineColor(sf::Color::Black);
    predatorInputBox.setPosition(260.f, 3.f);

    std::string predatorInputString;
    sf::Text predatorInputText;
    predatorInputText.setFont(font);
    predatorInputText.setCharacterSize(20);
    predatorInputText.setFillColor(sf::Color::Black);
    predatorInputText.setString("");
    predatorInputText.setPosition(262.f, 2.f);

    //Number of prey
    sf::Text numberOfPreyTxtPrompt;
    numberOfPreyTxtPrompt.setFont(font);
    numberOfPreyTxtPrompt.setCharacterSize(20);
    numberOfPreyTxtPrompt.setFillColor(sf::Color::Black);
    numberOfPreyTxtPrompt.setString("Number of prey:");
    numberOfPreyTxtPrompt.setPosition(5, 30);

    sf::RectangleShape preyInputBox(sf::Vector2f(50.f, 20.f));
    preyInputBox.setFillColor(sf::Color::White);
    preyInputBox.setOutlineThickness(2.f);
    preyInputBox.setOutlineColor(sf::Color::Black);
    preyInputBox.setPosition(260.f, 33.f);

    std::string preyInputString;
    sf::Text preyInputText;
    preyInputText.setFont(font);
    preyInputText.setCharacterSize(20);
    preyInputText.setFillColor(sf::Color::Black);
    preyInputText.setString("");
    preyInputText.setPosition(262.f, 32.f);

    //Number of flora
    sf::Text numberOfFloraTxtPrompt;
    numberOfFloraTxtPrompt.setFont(font);
    numberOfFloraTxtPrompt.setCharacterSize(20);
    numberOfFloraTxtPrompt.setFillColor(sf::Color::Black);
    numberOfFloraTxtPrompt.setString("Number of flora:");
    numberOfFloraTxtPrompt.setPosition(5, 60);

    sf::RectangleShape floraInputBox(sf::Vector2f(50.f, 20.f));
    floraInputBox.setFillColor(sf::Color::White);
    floraInputBox.setOutlineThickness(2.f);
    floraInputBox.setOutlineColor(sf::Color::Black);
    floraInputBox.setPosition(260.f, 63.f);

    std::string floraInputString;
    sf::Text floraInputText;
    floraInputText.setFont(font);
    floraInputText.setCharacterSize(20);
    floraInputText.setFillColor(sf::Color::Black);
    floraInputText.setString("");
    floraInputText.setPosition(262.f, 62.f);

    //Modes
    //preyVsPred
    sf::RectangleShape preyVsPredMode(sf::Vector2f(87.5, 20.f));
    preyVsPredMode.setFillColor(sf::Color::White);
    preyVsPredMode.setOutlineThickness(2.f);
    preyVsPredMode.setOutlineColor(sf::Color::Black);
    preyVsPredMode.setPosition(87.5, 150.f);

    sf::Text preyVsPredTextPrompt;
    preyVsPredTextPrompt.setFont(font);
    preyVsPredTextPrompt.setCharacterSize(14);
    preyVsPredTextPrompt.setFillColor(sf::Color::Black);
    preyVsPredTextPrompt.setString("PreyVsPred");
    preyVsPredTextPrompt.setPosition(90, 153);

    //standardMode
    sf::RectangleShape standardMode(sf::Vector2f(87.5, 20.f));
    standardMode.setFillColor(sf::Color::White);
    standardMode.setOutlineThickness(2.f);
    standardMode.setOutlineColor(sf::Color::Black);
    standardMode.setPosition(175.f, 150.f);

    sf::Text standardModeTextPrompt;
    standardModeTextPrompt.setFont(font);
    standardModeTextPrompt.setCharacterSize(14);
    standardModeTextPrompt.setFillColor(sf::Color::Black);
    standardModeTextPrompt.setString("Standard");
    standardModeTextPrompt.setPosition(188., 153);


    bool isPredatorInputFocused = false;
    bool isPreyInputFocused = false;
    bool isFloraInputFocused = false;
    //default is standard mode
    bool isStandardModeFocused = true;
    standardMode.setFillColor(sf::Color(120, 120, 120));
    bool isPreyVsPredFocused = false;


    while (windowParam.isOpen()) {
        sf::Event event;
        while (windowParam.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                windowParam.close();
                exit(1);
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the mouse is clicked on one of the input boxes
                sf::Vector2i mousePos = sf::Mouse::getPosition(windowParam);
                if (predatorInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isPredatorInputFocused = true;
                    isPreyInputFocused = false;
                    isFloraInputFocused = false;
                }
                else if (preyInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isPredatorInputFocused = false;
                    isPreyInputFocused = true;
                    isFloraInputFocused = false;
                }
                //flora
                else if (floraInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isPredatorInputFocused = false;
                    isPreyInputFocused = false;
                    isFloraInputFocused = true;
                }
                else if (preyVsPredMode.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isPreyVsPredFocused = true;
                    isStandardModeFocused = false;
                    preyVsPredMode.setFillColor(sf::Color(120, 120, 120));
                    standardMode.setFillColor(sf::Color::White);
                }
                else if (standardMode.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    isPreyVsPredFocused = false;
                    isStandardModeFocused = true;
                    standardMode.setFillColor(sf::Color(120, 120, 120));
                    preyVsPredMode.setFillColor(sf::Color::White);
                }
                else {
                    isPredatorInputFocused = false;
                    isPreyInputFocused = false;
                    isFloraInputFocused = false;

                }
            }
            else if (event.type == sf::Event::TextEntered) {
                if (isPredatorInputFocused) {
                    if (event.text.unicode == '\b' && predatorInputString.size() > 0) {
                        // Backspace was pressed
                        predatorInputString.pop_back();
                        predatorInputText.setString(predatorInputString);
                        inputNrPred = predatorInputString.empty() ? 0 : std::stoi(predatorInputString);
                        //predator
                    }

                    else if (event.text.unicode == '\r') {
                        // predator
                        if (!predatorInputString.empty()) {
                            predatorInputString = predatorInputText.getString();
                        }
                        windowParam.close();
                    }
                    else if (predatorInputString.size() < 3 && event.text.unicode >= '0' && event.text.unicode <= '9') {
                        predatorInputString += static_cast<char>(event.text.unicode);
                        predatorInputText.setString(predatorInputString);
                        if (predatorInputString.empty()) {
                            inputNrPred = 0;
                        }
                        else {
                            inputNrPred = std::stoi(predatorInputString);
                        }
                        try {
                            if (inputNrPred > maxInput) {
                                throw std::runtime_error("Input value too large! Maximum is 50. Only Max. will be considered!");
                            }
                        }
                        catch (std::runtime_error& e) {
                            std::cout << "Exception caught: " << e.what() << std::endl;
                            inputNrPred = maxInput;
                        }

                    }
                }//Prey
                else if (isPreyInputFocused) {
                    if (event.text.unicode == '\b' && preyInputString.size() > 0) {
                        // Backspace was pressed
                        preyInputString.pop_back();
                        preyInputText.setString(preyInputString);
                        inputNrPrey = preyInputString.empty() ? 0 : std::stoi(preyInputString);
                        //predator
                    }

                    else if (event.text.unicode == '\r') {
                        // predator
                        if (!preyInputString.empty()) {
                            preyInputString = preyInputText.getString();
                        }
                        windowParam.close();
                    }
                    else if (preyInputString.size() < 3 && event.text.unicode >= '0' && event.text.unicode <= '9') {
                        preyInputString += static_cast<char>(event.text.unicode);
                        preyInputText.setString(preyInputString);
                        if (preyInputString.empty()) {
                            inputNrPrey = 0;
                        }
                        else {
                            inputNrPrey = std::stoi(preyInputString);
                        }
                        try {
                            if (inputNrPrey > maxInput) {
                                throw std::runtime_error("Input value too large! Maximum is 50. Only Max. will be considered!");

                            }
                        }
                        catch (std::runtime_error& e) {
                            std::cout << "Exception caught: " << e.what() << std::endl;
                            inputNrPrey = maxInput;
                        }
                    }
                }//Flora
                else if (isFloraInputFocused) {
                    if (event.text.unicode == '\b' && floraInputString.size() > 0) {
                        // Backspace was pressed
                        floraInputString.pop_back();
                        floraInputText.setString(floraInputString);
                        inputNrFlora = floraInputString.empty() ? 0 : std::stoi(floraInputString);
                        //predator
                    }

                    else if (event.text.unicode == '\r') {
                        // predator
                        if (!floraInputString.empty()) {
                            floraInputString = floraInputText.getString();
                        }
                        windowParam.close();
                    }
                    else if (floraInputString.size() < 3 && event.text.unicode >= '0' && event.text.unicode <= '9') {
                        floraInputString += static_cast<char>(event.text.unicode);
                        floraInputText.setString(floraInputString);
                        if (floraInputString.empty()) {
                            inputNrFlora = 0;
                        }
                        else {
                            inputNrFlora = std::stoi(floraInputString);
                        }
                        try {
                            if (inputNrFlora > maxInput) {
                                throw std::runtime_error("Input value too large! Maximum is 50. Only Max. will be considered!");
                            }
                        }
                        catch (std::runtime_error& e) {
                            std::cout << "Exception caught: " << e.what() << std::endl;
                            inputNrFlora = maxInput;
                        }

                    }
                }
            }
        }

        sf::Text maxInputString;
        maxInputString.setFont(font);
        maxInputString.setCharacterSize(10);
        maxInputString.setFillColor(sf::Color::Black);
        maxInputString.setString("Maximum input per species: 50.");
        maxInputString.setStyle(sf::Text::Italic);
        maxInputString.setPosition(5, 280);

        sf::Text versionText;
        versionText.setFont(font);
        versionText.setCharacterSize(10);
        versionText.setFillColor(sf::Color::Black);
        versionText.setString("version 1.0.0");
        versionText.setStyle(sf::Text::Italic);
        versionText.setPosition(280, 280);

        sf::Text provideInputThenEnter;
        provideInputThenEnter.setFont(font2);
        provideInputThenEnter.setCharacterSize(10);
        provideInputThenEnter.setFillColor(sf::Color::Black);
        provideInputThenEnter.setString("Provide Input then hit Enter!");
        provideInputThenEnter.setOrigin(provideInputThenEnter.getGlobalBounds().width / 2, provideInputThenEnter.getGlobalBounds().height / 2);
        provideInputThenEnter.setPosition(175.f, 250.f);


        windowParam.clear(sf::Color::White);
        windowParam.draw(backgroundSprite);
        //Predator
        windowParam.draw(numberOfPredatorsTxtPrompt);
        windowParam.draw(predatorInputBox);
        windowParam.draw(predatorInputText);
        //prey
        windowParam.draw(numberOfPreyTxtPrompt);
        windowParam.draw(preyInputBox);
        windowParam.draw(preyInputText);
        //flora
        windowParam.draw(numberOfFloraTxtPrompt);
        windowParam.draw(floraInputBox);
        windowParam.draw(floraInputText);

        //version + notificiation
        windowParam.draw(maxInputString);
        windowParam.draw(versionText);


        //modes
        windowParam.draw(preyVsPredMode);
        windowParam.draw(preyVsPredTextPrompt);
        windowParam.draw(standardMode);
        windowParam.draw(standardModeTextPrompt);

        //provide input then enter
        windowParam.draw(provideInputThenEnter);


        windowParam.display();
    }

    ///////////////////////////////////////////////////////////////////// USER INPUT END //////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////// Variable Initialisations ////////////////////////////////////////////////////////////////////////

    /* OrganismVector is used to storee all organisms. we start initialising predators, prey and flora according to user input.
    * We then initlise the vectors contianing the statistics data.
    */


    std::time_t seed = std::time(nullptr);
    srand(seed);

    std::vector<Organism*> organismVector;

    for (int i = 0; i < inputNrPred; i++) {
        bool validRespawnPlace = false;
        float posX = isStandardModeFocused ? rand() % windowWidth : rand() % windowWidth / 2;
        float posY = rand() % windowHeight;
        float radius = rand() %2 +2;
        while (not validRespawnPlace) {
            for (int j = 0; j < i; j++) {
                float distanceSquare = pow(posX - organismVector.at(j)->getPosX(), 2) + pow(posY - organismVector.at(j)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(j)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
                else {
                    posX = isStandardModeFocused ? rand() % windowWidth : rand() % windowWidth / 2;
                    posY = rand() % windowHeight;
                    validRespawnPlace = false;
                    break;
                }
            }
            validRespawnPlace = true;
        }
        float energy = 1000.0;
        float visionRange = mutateOffspring("Predator", "Vision Range", averagePredatorVisionRange, averagePredatorVisionRange);
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = static_cast<int>(mutateOffspring("Predator", "Speed", averagePredatorSpeed, averagePredatorSpeed));
        float hungerLevel = mutateOffspring("Predator", "Hunger Sensitivity", averagePredatorHungerSensitivity, averagePredatorHungerSensitivity);
        float metabolicRate = mutateOffspring("Predator", "Metabolic Rate", averagePredatorMetabolicRate, averagePredatorMetabolicRate);
        float lustLevel = mutateOffspring("Predator", "Lust Level", averagePredatorLustLevel, averagePredatorLustLevel);

        Predator* myPredator = new Predator(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange);
        organismVector.push_back(myPredator);
    }
    
    for (int i = 0; i < inputNrPrey; i++) {
        bool validRespawnPlace = false;
        float posX = isStandardModeFocused ? rand() % windowWidth : (rand() % (windowWidth - windowWidth / 2 + 1)) + windowWidth / 2;
        float posY = rand() % windowHeight;
        float radius = rand() % 2 + 2;
        while (not validRespawnPlace) {
            for (int j = 0; j < i; j++) {
                float distanceSquare = pow(posX - organismVector.at(j)->getPosX(), 2) + pow(posY - organismVector.at(j)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(j)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
                else {
                    posX = isStandardModeFocused ? rand() % windowWidth : (rand() % (windowWidth - windowWidth / 2 + 1)) + windowWidth / 2;
                    posY = rand() % windowHeight;
                    validRespawnPlace = false;
                    break;
                }
            }
            validRespawnPlace = true;
        }
        float energy = 500.0;
        float visionRange = mutateOffspring("Prey", "Vision Range", averagePreyVisionRange, averagePreyVisionRange);
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = static_cast<int>(mutateOffspring("Prey", "Speed", averagePreySpeed, averagePreySpeed));
        float hungerLevel = mutateOffspring("Prey", "Hunger Sensitivity", averagePreyHungerSensitivity, averagePreyHungerSensitivity);
        float metabolicRate = mutateOffspring("Prey", "Metabolic Rate", averagePreyMetabolicRate, averagePreyMetabolicRate);
        float lustLevel = mutateOffspring("Prey", "Lust Level", averagePreyLustLevel, averagePreyLustLevel);
        float predatorAversion = mutateOffspring("Prey", "Predator Aversion", averagePreyPredatorAversion, averagePreyPredatorAversion);

        Prey* myPrey = new Prey(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange, predatorAversion);
        organismVector.push_back(myPrey);
    }

    for (int i = 0; i < inputNrFlora; i++) {
        bool validRespawnPlace = false;
        float posX = rand() % windowWidth;
        float posY = rand() % windowHeight;
        float radius = rand() % 2 + 2;
        while (not validRespawnPlace) {
            for (int j = 0; j < i; j++) {
                float distanceSquare = pow(posX - organismVector.at(j)->getPosX(), 2) + pow(posY - organismVector.at(j)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(j)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
                else {
                    posX = rand() % windowWidth;
                    posY = rand() % windowHeight;
                    validRespawnPlace = false;
                    break;
                }
            }
            validRespawnPlace = true;
        }
        float energy = 500; //TODO NEED TO PICK A VALID RANDOM ENERGY
        float growthRate = 7.0;// static_cast<float>(rand() % 10 + 1) * 10.0f;
        Flora* myFlora = new Flora(posX, posY, radius, energy, growthRate);
        organismVector.push_back(myFlora);
    }

    std::vector<float> numberOfFaunaAtTimeT;
    float totalNumberOfFauna = numberOfPrey + numberOfPredators;
    numberOfFaunaAtTimeT.push_back(totalNumberOfFauna);

    std::vector<float> numberOfPredatorsAtTimeT;
    numberOfPredatorsAtTimeT.push_back(numberOfPredators);

    std::vector<float> numberOfPreyAtTimeT;
    numberOfPreyAtTimeT.push_back(numberOfPrey);

    std::vector<float> totalEnergyOfPredatorAtTimeT;
    totalEnergyOfPredatorAtTimeT.push_back(totalEnergyPredator);

    std::vector<float> totalEnergyOfPreyAtTimeT;
    totalEnergyOfPreyAtTimeT.push_back(totalEnergyPrey);

    std::vector<float> totalEnergyOfFloraAtTimeT;
    totalEnergyOfFloraAtTimeT.push_back(totalEnergyFlora);

    std::vector<float> numberOfFemalePredatorsAtTimeT;
    numberOfFemalePredatorsAtTimeT.push_back(numberOfFemalePredator);

    std::vector<float> numberOfFemalePreyAtTimeT;
    numberOfFemalePreyAtTimeT.push_back(numberOfFemalePrey);

    std::vector<float> numberOfFertileFemalePreyAtTimeT;
    numberOfFertileFemalePreyAtTimeT.push_back(numberOfFertileFemalePrey);

    std::vector<float> numberOfFertileMalePreyAtTimeT;
    numberOfFertileMalePreyAtTimeT.push_back(numberOfFertileMalePrey);

    std::vector<float> numberOfFertileFemalePredatorAtTimeT;
    numberOfFertileFemalePredatorAtTimeT.push_back(numberOfFertileFemalePredator);

    std::vector<float> numberOfFertileMalePredatorAtTimeT;
    numberOfFertileMalePredatorAtTimeT.push_back(numberOfFertileMalePredator);

    std::vector<float> avgAgePredatorAtTimeT;
    std::vector<float> avgAgePreyAtTimeT;

    //////////////////////////////////////////////////////////////// Variable Initialisations End /////////////////////////////////////////////////////////////////////




    ///////////////////////////////////////////////////////////////////// Simulation Window //////////////////////////////////////////////////////////////////////////

    /* Here we create the window and set the frame rate, and then we enter the main loop of the program
    the one that handles events, draws the window, and processes user input until the program ends.
    */

    sf::RenderWindow window(sf::VideoMode(windowWidth + paneWidth, windowHeight), "Prey vs Predator");

    //Pane that will display the statistics
    sf::RectangleShape pane(sf::Vector2f(paneWidth, 720.f));
    pane.setPosition(sf::Vector2f(980.f, 0.f));
    pane.setFillColor(sf::Color(50, 60, 70));


    // Set the frame rate
    window.setFramerateLimit(frameRate);

    // start the game loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Main programme, we call update method on each organism which invodes other functions influecing the behaviour of each organism.
        for (int i = 0; i < organismVector.size(); i++) {
            organismVector.at(i)->update(organismVector);
        }


        // Simplified Survey Loop of Living Population to keep track of the energy flow in the system. We track it per species.
        totalEnergyFlora = 0.0;
        totalEnergyPrey = 0.0;
        totalEnergyPredator = 0.0;
        for (int i = 0; i < organismVector.size(); i++) {
            if (Flora* myFlora = dynamic_cast<Flora*>(organismVector.at(i))) {
                totalEnergyFlora += myFlora->getEnergy();
            }
            if (Prey* myPrey = dynamic_cast<Prey*>(organismVector.at(i))) {
                totalEnergyPrey += myPrey->getEnergy();
            }
            if (Predator* myPredator = dynamic_cast<Predator*>(organismVector.at(i))) {
                totalEnergyPredator += myPredator->getEnergy();
            }
        }

        //update the summary statistics vectors
        numberOfPredatorsAtTimeT.push_back(numberOfPredators);
        numberOfPreyAtTimeT.push_back(numberOfPrey);
        totalNumberOfFauna = numberOfPrey + numberOfPredators;
        numberOfFaunaAtTimeT.push_back(totalNumberOfFauna);

        totalEnergyOfFloraAtTimeT.push_back(totalEnergyFlora);
        totalEnergyOfPredatorAtTimeT.push_back(totalEnergyPredator);
        totalEnergyOfPreyAtTimeT.push_back(totalEnergyPrey);

        numberOfFemalePredatorsAtTimeT.push_back(numberOfFemalePredator);
        numberOfFemalePreyAtTimeT.push_back(numberOfFemalePrey);

        numberOfFertileFemalePredatorAtTimeT.push_back(numberOfFertileFemalePredator);
        numberOfFertileFemalePreyAtTimeT.push_back(numberOfFertileFemalePrey);

        numberOfFertileMalePredatorAtTimeT.push_back(numberOfFertileMalePredator);
        numberOfFertileMalePreyAtTimeT.push_back(numberOfFertileMalePrey);

        avgAgePredator = numberOfPredators == 0 ? 0 : totalAgePredator / numberOfPredators;
        avgAgePrey = numberOfPrey == 0 ? 0 : totalAgePrey / numberOfPrey;
        avgAgePredatorAtTimeT.push_back(avgAgePredator / frameRate);
        avgAgePreyAtTimeT.push_back(avgAgePrey / frameRate);



        // Print statistics at the top left corner
        sf::Text text;
        text.setFont(font);
        text.setString("Simulation Time: " + std::to_string(simulationTime / 60) + "\n" +
            "Population: " + std::to_string(organismVector.size()) + "\n" +
            "Predators: " + std::to_string(numberOfPredators) + "\n" +
            "Prey: " + std::to_string(numberOfPrey) + "\n" +
            "Flora: " + std::to_string(numberOfFlora));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::White);


        // clear the window
        window.clear(sf::Color::Black);

        /////////////////////////////////////////////////////////////// Simulation Window End //////////////////////////////////////////////////////////////////////////


        /////////////////////////////////////////////////////////////////// Simulation pane ////////////////////////////////////////////////////////////////////////////

        /* The pan contains all the plots and the legends of the organisms
        */


        // Population plot
        Plot2 mixedPlot = twoLinesPlot(1030.0, 170.0, numberOfPredatorsAtTimeT, numberOfPreyAtTimeT
            , font, "Total Population", 110.0, 225.0, 1800);

        // Energy plot
        Plot3 mixedPlot2 = threeLinesPlot(1030.0, 330.0, totalEnergyOfPredatorAtTimeT, totalEnergyOfPreyAtTimeT,
            totalEnergyOfFloraAtTimeT, font, "Total Energy", 110.0, 225.0, 1800);

        // Average Age plot
        Plot2 mixedPlot3 = twoLinesPlot(1030.0, 490.0, avgAgePredatorAtTimeT, avgAgePreyAtTimeT,
            font, "Average Age", 110.0, 225.0, 1800);

        // Pie Charts Gender and fertility for Predators
        Plot5 myPieChart3 = pieChart2(1065.0, 605.0, numberOfPredatorsAtTimeT, numberOfFemalePredatorsAtTimeT,
            numberOfFertileFemalePredatorAtTimeT, numberOfFertileMalePredatorAtTimeT, font, "Predator", 30);

        // Pie Charts Gender and fertility for Prey
        Plot5 myPieChart4 = pieChart2(1200, 605.0, numberOfPreyAtTimeT, numberOfFemalePreyAtTimeT,
            numberOfFertileFemalePreyAtTimeT, numberOfFertileMalePreyAtTimeT, font, "Prey", 30);

        // draw the organisms and the text
        for (Organism* organism : organismVector) {
            window.draw(organism->getShape());
        }

        // Draw the pane and the plots
        window.draw(pane);
        window.draw(text);

        window.draw(mixedPlot.xcoord);
        window.draw(mixedPlot.ycoord);
        window.draw(mixedPlot.chartLine);
        window.draw(mixedPlot.chartLine2);
        window.draw(mixedPlot.maxValue);
        window.draw(mixedPlot.midValue);
        window.draw(mixedPlot.percentile25);
        window.draw(mixedPlot.percentile75);
        window.draw(mixedPlot.title);
        window.draw(mixedPlot.maxXValue);
        window.draw(mixedPlot.midXValue);
        window.draw(mixedPlot.percentile25XValue);
        window.draw(mixedPlot.percentile75XValue);

        window.draw(mixedPlot2.xcoord);
        window.draw(mixedPlot2.ycoord);
        window.draw(mixedPlot2.chartLine);
        window.draw(mixedPlot2.chartLine2);
        window.draw(mixedPlot2.chartLine3);
        window.draw(mixedPlot2.maxValue);
        window.draw(mixedPlot2.midValue);
        window.draw(mixedPlot2.percentile25);
        window.draw(mixedPlot2.percentile75);
        window.draw(mixedPlot2.maxXValue);
        window.draw(mixedPlot2.midXValue);
        window.draw(mixedPlot2.percentile25XValue);
        window.draw(mixedPlot2.percentile75XValue);
        window.draw(mixedPlot2.title);

        window.draw(mixedPlot3.xcoord);
        window.draw(mixedPlot3.ycoord);
        window.draw(mixedPlot3.chartLine);
        window.draw(mixedPlot3.chartLine2);
        window.draw(mixedPlot3.maxValue);
        window.draw(mixedPlot3.midValue);
        window.draw(mixedPlot3.percentile25);
        window.draw(mixedPlot3.percentile75);
        window.draw(mixedPlot3.maxXValue);
        window.draw(mixedPlot3.midXValue);
        window.draw(mixedPlot3.percentile25XValue);
        window.draw(mixedPlot3.percentile75XValue);
        window.draw(mixedPlot3.title);
        window.draw(mixedPlot3.ylabel);


        window.draw(myPieChart3.circle);
        window.draw(myPieChart3.title);
        window.draw(myPieChart3.xlabel);
        for (int i = 0; i < myPieChart3.chartlinesVector.size(); i++) {
            window.draw(myPieChart3.chartlinesVector2[i]);
            window.draw(myPieChart3.chartlinesVector[i]);
            window.draw(myPieChart3.circle);
        }

        //tiral new Pie chart
        window.draw(myPieChart4.circle);
        window.draw(myPieChart4.title);
        window.draw(myPieChart4.xlabel);
        for (int i = 0; i < myPieChart4.chartlinesVector.size(); i++) {
            window.draw(myPieChart4.chartlinesVector2[i]);
            window.draw(myPieChart4.chartlinesVector[i]);
            window.draw(myPieChart4.circle);
        }


        //Line Plots legend
        sf::RectangleShape predatorBox(sf::Vector2f(8.f, 8.f));
        predatorBox.setFillColor(sf::Color::Red);
        predatorBox.setPosition(1040, 525);

        sf::RectangleShape preyBox(sf::Vector2f(8.f, 8.f));
        preyBox.setFillColor(sf::Color::Color(0, 120, 255));
        preyBox.setPosition(1110, 525);

        sf::RectangleShape floraBox(sf::Vector2f(8.f, 8.f));
        floraBox.setFillColor(sf::Color::Green);
        floraBox.setPosition(1165, 525);

        sf::Text predatorTextString;
        predatorTextString.setFont(font);
        predatorTextString.setCharacterSize(12);
        predatorTextString.setFillColor(sf::Color::White);
        predatorTextString.setString("Predator");
        predatorTextString.setPosition(1050, 521);

        sf::Text preyTextString;
        preyTextString.setFont(font);
        preyTextString.setCharacterSize(12);
        preyTextString.setFillColor(sf::Color::White);
        preyTextString.setString("Prey");
        preyTextString.setPosition(1120, 521);


        sf::Text floraTextString;
        floraTextString.setFont(font);
        floraTextString.setCharacterSize(12);
        floraTextString.setFillColor(sf::Color::White);
        floraTextString.setString("Flora");
        floraTextString.setPosition(1175, 521);

        window.draw(predatorBox);
        window.draw(preyBox);
        window.draw(floraBox);
        window.draw(predatorTextString);
        window.draw(preyTextString);
        window.draw(floraTextString);

        //Pie Chart Legend
        sf::RectangleShape maleBox(sf::Vector2f(8.f, 8.f));
        maleBox.setFillColor(sf::Color(130, 190, 230));
        maleBox.setPosition(1035, 705);

        sf::RectangleShape femaleBox(sf::Vector2f(8.f, 8.f));
        femaleBox.setFillColor(sf::Color::Color(230, 130, 220));
        femaleBox.setPosition(1100, 705);

        sf::RectangleShape fertileBox(sf::Vector2f(8.f, 8.f));
        fertileBox.setFillColor(sf::Color::Color(230, 100, 0));
        fertileBox.setPosition(1180, 705);

        sf::Text maleTextString;
        maleTextString.setFont(font);
        maleTextString.setCharacterSize(12);
        maleTextString.setFillColor(sf::Color::White);
        maleTextString.setString("Male");
        maleTextString.setPosition(1045, 701);

        sf::Text femaleTextString;
        femaleTextString.setFont(font);
        femaleTextString.setCharacterSize(12);
        femaleTextString.setFillColor(sf::Color::White);
        femaleTextString.setString("Female");
        femaleTextString.setPosition(1110, 701);

        sf::Text fertileTextString;
        fertileTextString.setFont(font);
        fertileTextString.setCharacterSize(12);
        fertileTextString.setFillColor(sf::Color::White);
        fertileTextString.setString("Fertile");
        fertileTextString.setPosition(1190, 701);

        window.draw(maleBox);
        window.draw(femaleBox);
        window.draw(maleTextString);
        window.draw(femaleTextString);
        window.draw(fertileBox);
        window.draw(fertileTextString);

        simulationTime++;
        window.display();
    }

    /////////////////////////////////////////////////////////////// Simulation pane End ////////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////// DEATH REPORT ////////////////////////////////////////////////////////////////////////////// 
    /* Show all summary statistics for dead orgarnisms.
    */


    sf::RenderWindow windowSummary(sf::VideoMode(windowWidth + paneWidth, windowHeight), "Death Summary");

    float canvasWidth;
    float canvasHeight;
    float newOriginX;
    float newOriginY;
    float lineHeight;
    float columnWidth;

    canvasWidth = 0.9 * (windowWidth + paneWidth);
    canvasHeight = 0.9 * windowHeight;
    newOriginX = 0.05 * (windowWidth + paneWidth);
    newOriginY = 0.05 * windowHeight;
    lineHeight = canvasHeight / 14.0;
    columnWidth = canvasWidth / 20.0;


    while (windowSummary.isOpen()) {
        // handle events
        sf::Event event;
        while (windowSummary.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowSummary.close();
        }

        windowParam.clear(sf::Color::White);

        sf::RectangleShape testBox(sf::Vector2f((windowWidth + paneWidth), windowHeight));
        testBox.setFillColor(sf::Color::White);
        testBox.setOutlineThickness(2.f);
        testBox.setOutlineColor(sf::Color::Black);
        testBox.setPosition(0.f, 0.f);
        windowSummary.draw(testBox);




        sf::Text currentText;
        currentText.setFont(font);
        currentText.setCharacterSize(20);
        currentText.setFillColor(sf::Color::Black);
        currentText.setString("Population Summary");
        currentText.setPosition(newOriginX + canvasWidth * 0.5 - (currentText.getLocalBounds().width / 2.0), newOriginY + lineHeight * (1.0) -
            (currentText.getLocalBounds().height / 2.0));
        windowSummary.draw(currentText);

        currentText.setCharacterSize(12);


        for (int i = 0; i < summaryStatistics.size(); i++) {



            currentText.setString(summaryStatistics[i].speciesName);
            currentText.setPosition(newOriginX + 2.0 * columnWidth, newOriginY + (2.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            currentText.setString("Species:");
            currentText.setPosition(newOriginX, newOriginY + (2.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            currentText.setString("Trait:");
            currentText.setPosition(newOriginX, newOriginY + (3.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            currentText.setString("Category:");
            currentText.setPosition(newOriginX, newOriginY + (4.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            currentText.setString("Population:");
            currentText.setPosition(newOriginX, newOriginY + (5.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            currentText.setString("AVG Age at Death:");
            currentText.setPosition(newOriginX, newOriginY + (6.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            currentText.setString("AVG # of Offsprings:");
            currentText.setPosition(newOriginX, newOriginY + (7.0 + i * 6.0) * lineHeight);
            windowSummary.draw(currentText);
            /*
            sf::RectangleShape traitSeparator(sf::Vector2f(2.0, 4.8 * lineHeight));
            traitSeparator.setFillColor(sf::Color::Black);
            traitSeparator.setOutlineThickness(0.f);
            traitSeparator.setOutlineColor(sf::Color::Black);

            sf::RectangleShape classSeparator(sf::Vector2f(1.0, 3.8 * lineHeight));
            classSeparator.setFillColor(sf::Color::Black);
            classSeparator.setOutlineThickness(0.f);
            classSeparator.setOutlineColor(sf::Color::Black);
            */


            for (int j = 0; j < summaryStatistics[i].traitSummaryStatisticVector.size(); j++) {
                currentText.setString(summaryStatistics[i].traitSummaryStatisticVector[j].traitName);
                currentText.setPosition(newOriginX + (2.0 + 3.0 * j) * columnWidth, newOriginY + (3.0 + i * 6.0) * lineHeight);
                windowSummary.draw(currentText);
                //traitSeparator.setPosition(newOriginX + (1.8 + 3.0 * (j + 1)) * columnWidth, newOriginY + (3.0 + i * 6.0) * lineHeight);
                //windowSummary.draw(traitSeparator);
                for (int k = 0; k < 3; k++) {
                    currentText.setString(std::to_string(k + 1));
                    currentText.setPosition(newOriginX + (2.0 + 3.0 * j + 1.0 * k) * columnWidth, newOriginY + (4.0 + i * 6.0) * lineHeight);
                    windowSummary.draw(currentText);
                    //classSeparator.setPosition(newOriginX + (1.8 + 3.0 * j + 1.0 * k) * columnWidth, newOriginY + (4.0 + i * 6.0) * lineHeight);
                    //windowSummary.draw(classSeparator);
                    std::stringstream stream1;
                    stream1 << std::fixed << std::setprecision(0) << (summaryStatistics[i].traitSummaryStatisticVector[j].population[k]);
                    currentText.setString(stream1.str());
                    currentText.setPosition(newOriginX + (2.0 + 3.0 * j + 1.0 * k) * columnWidth, newOriginY + (4.0 + i * 6.0 + 1.0) * lineHeight);
                    windowSummary.draw(currentText);
                    std::string averageAgeAtDeath;
                    std::string averageOffspringNumberAtDeath;
                    if (not (summaryStatistics[i].traitSummaryStatisticVector[j].population[k] == 0)) {
                        std::stringstream stream2;
                        stream2 << std::fixed << std::setprecision(2) << ((1.0 * summaryStatistics[i].traitSummaryStatisticVector[j].sumOfAgesAtDeath[k]) /
                            (1.0 * summaryStatistics[i].traitSummaryStatisticVector[j].population[k]));
                        averageAgeAtDeath = stream2.str();
                        std::stringstream stream3;
                        stream3 << std::fixed << std::setprecision(2) << ((1.0 * summaryStatistics[i].traitSummaryStatisticVector[j].sumOfOffsprings[k]) /
                            (1.0 * summaryStatistics[i].traitSummaryStatisticVector[j].population[k]));
                        averageOffspringNumberAtDeath = stream3.str();
                    }
                    else {
                        averageAgeAtDeath = "No Data";
                        averageOffspringNumberAtDeath = "No Data";
                    }
                    currentText.setString(averageAgeAtDeath);
                    currentText.setPosition(newOriginX + (2.0 + 3.0 * j + 1.0 * k) * columnWidth, newOriginY + (4.0 + i * 6.0 + 2.0) * lineHeight);
                    windowSummary.draw(currentText);
                    currentText.setString(averageOffspringNumberAtDeath);
                    currentText.setPosition(newOriginX + (2.0 + 3.0 * j + 1.0 * k) * columnWidth, newOriginY + (4.0 + i * 6.0 + 3.0) * lineHeight);
                    windowSummary.draw(currentText);
                }
            }

        }




        windowSummary.display();
        /////////////////////////////////////////////////////////////// DEATH REPORT End ////////////////////////////////////////////////////////////////////////////// 
    }

}


int main()
{
    startSimulation();
    return 0;
}
