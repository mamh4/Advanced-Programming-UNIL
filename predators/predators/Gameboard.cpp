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

#include <random>
#include <thread>

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


//TODO: Decide on intialisation in main class of two vectors Fauna and Flora and then we loop through all Faunas, then all Floras? I think so
//TODO: Implement update for Prey and Flora

int main()
{    
    //////////////////////////////////////////////////////// USER INPUT //////////////////////////////////////////////////////////////
    
    sf::RenderWindow windowParam(sf::VideoMode(350, 300), "Input Box Example");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }

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

    bool isPredatorInputFocused = false;
    bool isPreyInputFocused = false;
    bool isFloraInputFocused = false;


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
                            numberOfPredators = 0;
                        }
                        else {
                            numberOfPredators = std::stoi(predatorInputString);
                        }
                        try {
                            if (numberOfPredators > 50) {
                                throw std::runtime_error("Input value too large! Maximum is 50");
                            }
                        }
                        catch (std::runtime_error& e) {
                            std::cout << "Exception caught: " << e.what() << std::endl;
                        }
                        
                    }
                }//Prey
                else if (isPreyInputFocused) {
                    if (event.text.unicode == '\b' && preyInputString.size() > 0) {
                        // Backspace was pressed
                        preyInputString.pop_back();
                        preyInputText.setString(preyInputString);
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
                            numberOfPrey = 0;
                        }
                        else {
                            numberOfPrey = std::stoi(preyInputString);
                        }
                        try {
                            if (numberOfPrey > 50) {
                                throw std::runtime_error("Input value too large! Maximum is 50");
                            }
                        }
                        catch (std::runtime_error& e) {
                            std::cout << "Exception caught: " << e.what() << std::endl;
                        }
                    }
                }//Flora
                else if (isFloraInputFocused) {
                    if (event.text.unicode == '\b' && floraInputString.size() > 0) {
                        // Backspace was pressed
                        floraInputString.pop_back();
                        floraInputText.setString(floraInputString);
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
                            numberOfFlora = 0;
                        }
                        else {
                            numberOfFlora = std::stoi(floraInputString);
                        }
                        try {
                            if (numberOfFlora > 50) {
                                throw std::runtime_error("Input value too large! Maximum is 50");
                            }
                        }
                        catch (std::runtime_error& e) {
                            std::cout << "Exception caught: " << e.what() << std::endl;
                        }

                    }
                }
            }
        }

        windowParam.clear(sf::Color::White);
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

        windowParam.display();
    }


    //////////////////////////////////////////////////////// USER INPUT END //////////////////////////////////////////////////////////////
   
    /////////////////////////////////////////////////// Variable Initialisations /////////////////////////////////////////////////////////

    std::time_t seed = std::time(nullptr);
    srand(seed);

    std::vector<Organism*> organismVector;

    //Data vectors initialisations:

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

    float totalEnergy = totalEnergyFlora + totalEnergyPrey + totalEnergyPredator;
    std::vector<float> totalEnergyAtTimeT;
    totalEnergyAtTimeT.push_back(totalEnergy);

    std::vector<float> numberOfFemalePredatorsAtTimeT;
    numberOfFemalePredatorsAtTimeT.push_back(numberOfFemalePredator);


    
    //TO BE DELETED Below
    Predator* myPredator = new Predator(500, 500, 5, 400, true, 1, 10, 1, 50, 400);
    organismVector.push_back(myPredator);
    Predator* myPredator2 = new Predator(475, 596, 5, 100, false, 1, 10, 1, 50, 800);
    organismVector.push_back(myPredator2);

    Predator* myPredator3 = new Predator(500, 290, 5, 290, true, 1, 10, 1, 50, 800);
    organismVector.push_back(myPredator3);

    Predator* myPredator4 = new Predator(500, 290, 5, 290, true, 1, 10, 1, 50, 800);
    organismVector.push_back(myPredator4);

    Predator* myPredator5 = new Predator(330, 290, 5, 290, true, 1, 10, 1, 50, 800);
    organismVector.push_back(myPredator5);

    Prey* myPrey = new Prey(400, 460, 7, 200, true, 2, 10, 0.1, 50, 900, 1);
    organismVector.push_back(myPrey);

    Prey* myPrey2 = new Prey(700, 700, 7, 200, true, 2, 10, 0.1, 50, 900, 1);
    organismVector.push_back(myPrey2);

    Prey* myPrey3 = new Prey(50, 660, 7, 200, false, 2, 10, 0.1, 50, 900, 1);
    organismVector.push_back(myPrey3);

    Flora* myFlora = new Flora(500, 190, 10, 800, 0.5);
    organismVector.push_back(myFlora);

    Flora* myFlora2 = new Flora(900, 500, 10, 800, 0.5);
    organismVector.push_back(myFlora2);

    Flora* myFlora3 = new Flora(100, 600, 10, 800, 0.5);
    organismVector.push_back(myFlora3);
    //To be deleted Above
    
    /*
    //std::cout << organismVector.at(0)->getType() << std::endl;
    for (int i = 0; i < numberOfPredators; i++) {
        bool validRespawnPlace = false;
        float posX = 500;
        float posY = 500;
        float radius = 3;
        while (not validRespawnPlace){
            posX = rand() % windowWidth;
            posY = rand() % windowHeight;
            radius = static_cast<float>(rand() % 10 + 5);
            for (int j = 0; j <= i; j++) {
                float distanceSquare = pow(posX - organismVector.at(i)->getPosX(), 2) + pow(posY - organismVector.at(i)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(i)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
            }
        }
        float energy = rand() % 100 + 1;
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = rand() % 3 +1;
        int hungerLevel = rand() % 100 + 1;
        float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
        int lustLevel = rand() % 100 + 1;
        int visionRange = rand() % 100 + 1;
        Predator* myPredator = new Predator(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange);
        organismVector.push_back(myPredator);
    }

    for (int i = 0; i < numberOfPrey; i++) {
        bool validRespawnPlace = false;
        float posX = 500;
        float posY = 500;
        float radius = 3;
        while (not validRespawnPlace) {
            posX = rand() % windowWidth;
            posY = rand() % windowHeight;
            radius = static_cast<float>(rand() % 10 + 5);
            for (int j = 0; j <= i; j++) {
                float distanceSquare = pow(posX - organismVector.at(i)->getPosX(), 2) + pow(posY - organismVector.at(i)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(i)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
            }
        }
        float energy = rand() % 100 + 1;
        bool sex = rand() % 2 == 0 ? true : false;
        int speed = rand() % 10 + 1;
        int hungerLevel = rand() % 100 + 1;
        float metabolicRate = static_cast<float>(rand() % 10 + 1) / 10.0f;
        int lustLevel = rand() % 100 + 1;
        int visionRange = rand() % 100 + 1;
        float predatorAversion = static_cast<float>(rand() * 100);
        Prey* myPrey = new Prey(posX, posY, radius, energy, sex, speed, hungerLevel, metabolicRate, lustLevel, visionRange, predatorAversion);
        organismVector.push_back(myPrey);
    }

    for (int i = 0; i < numberOfFlora; i++) {
        bool validRespawnPlace = false;
        float posX = 500;
        float posY = 500;
        float radius = 3;
        while (not validRespawnPlace) {
            posX = rand() % windowWidth;
            posY = rand() % windowHeight;
            radius = static_cast<float>(rand() % 10 + 5);
            for (int j = 0; j <= i; j++) {
                float distanceSquare = pow(posX - organismVector.at(i)->getPosX(), 2) + pow(posY - organismVector.at(i)->getPosY(), 2);
                if (distanceSquare > pow(organismVector.at(i)->getRadius() + radius, 2)) {
                    validRespawnPlace = true;
                }
            }
        }
        float energy = rand() % 100 + 1;
        float growthRate = static_cast<float>(rand() * 100);
        Flora* myFlora = new Flora(posX, posY, radius, energy, growthRate);
        organismVector.push_back(myFlora);
    }
    UNCOMMENT*/


    sf::RenderWindow window(sf::VideoMode(windowWidth+300, windowHeight), "Prey vs Predator");


    /////////////////////////////////////////////// Statistics ////////////////////////////////////////////////////

    //Overlay on top of each other population counts!!!! with different colour plots based on flora, prey and pred
    sf::RectangleShape pane(sf::Vector2f(300.f, 720.f));
    pane.setPosition(sf::Vector2f(980.f, 0.f));
    pane.setFillColor(sf::Color(128,128,128));

    /*
    //plotting stuff
    float plotHeight = 120.0;
    float plotWidth = 250.0;

    float plotX = 1010.0; // lower corner 
    float plotY = 170.0;

    float maxDataPoint = 0.0;
    float minDataPoint = 0.0;

    int timeWindow = 500; // Number of Data Points 


    sf::VertexArray xcoord(sf::LineStrip, 2);
    xcoord.setPrimitiveType(sf::LinesStrip);
    xcoord[0].position = sf::Vector2f(plotX, plotY);
    xcoord[1].position = sf::Vector2f(plotX + plotWidth, plotY);
    xcoord[0].color = sf::Color::Black;
    xcoord[1].color = sf::Color::Black;


    sf::VertexArray ycoord(sf::LineStrip, 2);
    ycoord.setPrimitiveType(sf::LinesStrip);
    ycoord[0].position = sf::Vector2f(plotX, plotY);
    ycoord[1].position = sf::Vector2f(plotX, plotY - plotHeight-30);
    ycoord[0].color = sf::Color::Black;
    ycoord[1].color = sf::Color::Black;

    sf::VertexArray chartLines(sf::LineStrip, timeWindow);
    chartLines.setPrimitiveType(sf::LinesStrip);

    */
    // Set the frame rate
    window.setFramerateLimit(60);

    // start the game loop
    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        for (int i = 0; i < organismVector.size(); i++) {

            organismVector.at(i)->update(organismVector);

        }

        numberOfPredatorsAtTimeT.push_back(numberOfPredators);
        numberOfPreyAtTimeT.push_back(numberOfPrey);
        totalNumberOfFauna = numberOfPrey + numberOfPredators;
        numberOfFaunaAtTimeT.push_back(totalNumberOfFauna);


        totalEnergyOfFloraAtTimeT.push_back(totalEnergyFlora);
        totalEnergyOfPredatorAtTimeT.push_back(totalEnergyPredator);
        totalEnergyOfPreyAtTimeT.push_back(totalEnergyPrey);
        totalEnergy = totalEnergyPredator + totalEnergyPrey + totalEnergyFlora;
        totalEnergyAtTimeT.push_back(totalEnergy);

        numberOfFemalePredatorsAtTimeT.push_back(numberOfFemalePredator);
        
        ///dataPointvectors
        
        
        /*
        //float newDataPoint = 1.0*organismVector.size();

//        if (dataPoints.size() > timeWindow  ) {
 //           for (int i = 0; i < (dataPoints.size() - 1) ; i++) {
  //              dataPoints[i] = dataPoints[i + 1];
   //         }
    //        dataPoints[dataPoints.size() -1 ] = newDataPoint;
     //   }
      //  else {
       //     dataPoints.push_back(newDataPoint);
        //}

        for (int i = 0; i < dataPoints.size(); i++) {
            if (maxDataPoint < dataPoints[i]) {
                maxDataPoint = dataPoints[i];
            }
            if (minDataPoint > dataPoints[i]) {
                minDataPoint = dataPoints[i];
            }
        }
        if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
            for (int i = 0; i < std::min(static_cast<int>(dataPoints.size()), timeWindow); i++) { 
                chartLines[i].position = sf::Vector2f(plotX + 1.0 * i * plotWidth / (timeWindow * 1.0),
                    plotY - plotHeight * dataPoints[i] / (maxDataPoint - minDataPoint));
                chartLines[i].color = sf::Color::Black;
            }
            if (static_cast<int>(dataPoints.size()) < timeWindow ){
                for (int i = (static_cast<int>(dataPoints.size())) ; i < std::max(static_cast<int>(dataPoints.size()), timeWindow); i++) {
                    chartLines[i].position = sf::Vector2f(plotX + 1.0 * (static_cast<int>(dataPoints.size()) -1)  * plotWidth / (timeWindow * 1.0),
                        plotY - plotHeight * dataPoints[dataPoints.size()-1] / (maxDataPoint - minDataPoint));
                    chartLines[i].color = sf::Color::Black;
                }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
            }
        }
        */
        
        ///Trial


        //

        // Print statistics at the top left corner
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        if (!font.loadFromFile("arial.ttf")) {
           
        }
        text.setFont(font);
        text.setString("Population size: " + std::to_string(organismVector.size()) + "\n" +
            "Predators: " + std::to_string(numberOfPredators) + "\n" +
            "Prey: " + std::to_string(numberOfPrey) + "\n" +
            "Flora: " + std::to_string(numberOfFlora));
        // +std::to_string(organismVector.size()));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color::Black);


        // clear the window
        window.clear(sf::Color::White);
        
        //Plot linePlot1 = linePlot(1010.0, 170.0,numberOfPredatorsAtTimeT, font,"Hello",120.0,250.0,2000);
        Plot2 mixedPlot = twoLinesPlot(1010.0, 170.0, numberOfFaunaAtTimeT,numberOfPredatorsAtTimeT, numberOfPreyAtTimeT
            , font, "Hello", 120.0, 250.0, 2000);

        Plot3 mixedPlot2 = threeLinesPlot(1010.0, 470.0, totalEnergyAtTimeT, totalEnergyOfPredatorAtTimeT, totalEnergyOfPreyAtTimeT,
            totalEnergyOfFloraAtTimeT, font, "Hello", 120.0, 250.0, 2000);
        
        Plot4 myPieChart = pieChart(1050.0, 570.0, numberOfPredatorsAtTimeT, numberOfFemalePredatorsAtTimeT,font,"hello");

        // draw the organisms and the text
        for (Organism* organism : organismVector) {
            window.draw(organism->getShape());
            window.draw(pane);
            window.draw(text);

            window.draw(mixedPlot.xcoord);
            window.draw(mixedPlot.ycoord);
            window.draw(mixedPlot.chartLine);
            window.draw(mixedPlot.chartLine2);
            window.draw(mixedPlot.maxValue);
            window.draw(mixedPlot.midValue);

            window.draw(mixedPlot2.xcoord);
            window.draw(mixedPlot2.ycoord);
            window.draw(mixedPlot2.chartLine);
            window.draw(mixedPlot2.chartLine2);
            window.draw(mixedPlot2.chartLine3);
            window.draw(mixedPlot2.maxValue);
            window.draw(mixedPlot2.midValue);

            for (int i = 0; i < myPieChart.chartlinesVector.size(); i++) {
                window.draw(myPieChart.chartlinesVector[i]);
            }
            //window.draw(linePlot(1010.0, 170.0, dataPoints, "Hello")[1]);
            //window.draw(linePlot(1010.0, 170.0, dataPoints, "Hello")[2]);

        }

        window.display();
    }
    
    return 0;
}