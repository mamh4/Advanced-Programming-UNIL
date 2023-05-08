#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <variant>

extern int numberOfPredators;
extern int numberOfPrey;
extern int numberOfFlora;

extern float avgAgePredators;
extern float avgAgePrey;

extern float totalEnergyPredator;
extern float totalEnergyPrey;
extern float totalEnergyFlora;

extern int numberOfMalePredator;
extern int numberOfFemalePredator;

extern int numberOfMalePrey;
extern int numberOfFemalePrey;


struct Plot {
    sf::VertexArray xcoord;
    sf::VertexArray ycoord;
    sf::VertexArray chartLine;
    //sf::Text theTitle;
    //sf::Text xlabel;
    //sf::Text ylabel;
    sf::Text maxValue;
    sf::Text midValue;
};

struct Plot2 {
    sf::VertexArray xcoord;
    sf::VertexArray ycoord;
    sf::VertexArray chartLine;
    sf::VertexArray chartLine2;
    sf::Text title;
    //sf::Text xlabel;
    //sf::Text ylabel;
    sf::Text maxValue;
    sf::Text midValue;
    sf::Text percentile25;
    sf::Text percentile75;
};

struct Plot3 {
    sf::VertexArray xcoord;
    sf::VertexArray ycoord;
    sf::VertexArray chartLine;
    sf::VertexArray chartLine2;
    sf::VertexArray chartLine3;
    //sf::Text title;
    //sf::Text xlabel;
    //sf::Text ylabel;
    sf::Text maxValue;
    sf::Text midValue;
    sf::Text percentile25;
    sf::Text percentile75;
};

struct Plot4 {
    sf::CircleShape circle;
    std::vector<sf::VertexArray> chartlinesVector;
    sf::Text title;
    sf::Text xlabel;
    //sf::Text ylabel;
    //sf::Text percentage;
};

Plot linePlot(float posX, float posY, std::vector<float> dataPoints, sf::Font& font,
    std::string title, float height = 120.0, float width = 225.0, int timeSpan = 500);


Plot2 twoLinesPlot(float posX, float posY, std::vector<float> dataPoints, std::vector<float>& dataPoints2, std::vector<float>& dataPoints3,
    sf::Font& font, std::string title, float height = 120.0, float width = 225.0, int timeSpan = 500);

Plot3 threeLinesPlot(float posX, float posY, std::vector<float> dataPoints, std::vector<float>& dataPoints2, std::vector<float>& dataPoints3,
    std::vector<float>& dataPoints4, sf::Font& font, std::string title, float height = 120.0, float width = 225.0, int timeSpan = 500);

Plot4 pieChart(float posX, float posY,std::vector<float> dataPoints, std::vector<float> dataPoints2 
    ,sf::Font& font, std::string title, float radius = 50.0);

