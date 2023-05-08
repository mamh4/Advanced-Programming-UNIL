#include "OrganicStats.h"
#include <iostream>
#include <vector>
#include <sfml/Graphics.hpp>
#include <string>
#include "OrganicMaths.h"


Plot linePlot(float posX, float posY, std::vector<float> dataPoints, 
    sf::Font& font,std::string title, float height, float width, int timeSpan) {
    Plot myPlot;
  
    
    float maxDataPoint = 0.0;
    float minDataPoint = 0.0;
    //initialise lines
    sf::VertexArray xcoord(sf::LineStrip, 2);
    xcoord.setPrimitiveType(sf::LinesStrip);
    xcoord[0].position = sf::Vector2f(posX, posY);
    xcoord[1].position = sf::Vector2f(posX + width, posY);
    xcoord[0].color = sf::Color::Black;
    xcoord[1].color = sf::Color::Black;


    sf::VertexArray ycoord(sf::LineStrip, 2);
    ycoord.setPrimitiveType(sf::LinesStrip);
    ycoord[0].position = sf::Vector2f(posX, posY);
    ycoord[1].position = sf::Vector2f(posX, posY - height - 30);
    ycoord[0].color = sf::Color::Black;
    ycoord[1].color = sf::Color::Black;

    sf::VertexArray chartLines(sf::LineStrip, timeSpan);
    chartLines.setPrimitiveType(sf::LinesStrip);

    //initialise axes string

    //Y-axis
    sf::Text yAxisMax;
    yAxisMax.setFont(font);
    yAxisMax.setCharacterSize(12);
    yAxisMax.setPosition(posX - 7, posY - height);
    yAxisMax.setFillColor(sf::Color::Black);

    
    //mid Y-axis
        //Y-axis
    sf::Text yAxisMid;
    yAxisMid.setFont(font);
    yAxisMid.setCharacterSize(12);
    yAxisMid.setPosition(posX - 7, posY - height/2);
    yAxisMid.setFillColor(sf::Color::Black);


    //float newDataPoint = 1.0 * dataPoints.size();

//    if (dataPoints.size() > timeSpan) {
 //       for (int i = 0; i < (dataPoints.size() - 1); i++) {
  //          dataPoints[i] = dataPoints[i + 1];
   //     }
    //    dataPoints[dataPoints.size() - 1] = newDataPoint;
    //}
    //else {
      //  dataPoints.push_back(newDataPoint);
    //}

    for (int i = 0; i < dataPoints.size(); i++) {
        if (maxDataPoint < dataPoints[i]) {
            maxDataPoint = dataPoints[i];
            yAxisMax.setString(std::to_string(maxDataPoint));
            yAxisMid.setString(std::to_string(maxDataPoint/2));
        }
        if (minDataPoint > dataPoints[i]) {
            minDataPoint = dataPoints[i];
        }
    }
    if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints.size()), timeSpan); i++) {
            chartLines[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * dataPoints[i] / (maxDataPoint - minDataPoint));
            chartLines[i].color = sf::Color::Black;
        }
        if (static_cast<int>(dataPoints.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints.size())); i < std::max(static_cast<int>(dataPoints.size()), timeSpan); i++) {
                chartLines[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * dataPoints[dataPoints.size() - 1] / (maxDataPoint - minDataPoint));
                chartLines[i].color = sf::Color::Black;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }
    yAxisMax.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxisMid.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);

    myPlot.xcoord = xcoord;
    myPlot.ycoord = ycoord;
    myPlot.chartLine = chartLines;
    myPlot.maxValue = yAxisMax;
    myPlot.midValue = yAxisMid;
    return myPlot;
   
}


Plot2 twoLinesPlot(float posX, float posY, std::vector<float> dataPoints, std::vector<float> dataPoints2, std::vector<float> dataPoints3,
    sf::Font& font, std::string title, float height, float width, int timeSpan) {
    Plot2 myPlot;


    float maxDataPoint = 0.0;
    float minDataPoint = 0.0;
    //initialise lines
    sf::VertexArray xcoord(sf::LineStrip, 2);
    xcoord.setPrimitiveType(sf::LinesStrip);
    xcoord[0].position = sf::Vector2f(posX, posY);
    xcoord[1].position = sf::Vector2f(posX + width, posY);
    xcoord[0].color = sf::Color::Black;
    xcoord[1].color = sf::Color::Black;


    sf::VertexArray ycoord(sf::LineStrip, 2);
    ycoord.setPrimitiveType(sf::LinesStrip);
    ycoord[0].position = sf::Vector2f(posX, posY);
    ycoord[1].position = sf::Vector2f(posX, posY - height - 30);
    ycoord[0].color = sf::Color::Black;
    ycoord[1].color = sf::Color::Black;

    sf::VertexArray chartLines(sf::LineStrip, timeSpan);
    chartLines.setPrimitiveType(sf::LinesStrip);

    sf::VertexArray chartLines2(sf::LineStrip, timeSpan);
    chartLines2.setPrimitiveType(sf::LinesStrip);

    //initialise axes string

    //Y-axis
    sf::Text yAxisMax;
    yAxisMax.setFont(font);
    yAxisMax.setCharacterSize(12);
    yAxisMax.setPosition(posX - 7, posY - height);
    yAxisMax.setFillColor(sf::Color::Black);


    //mid Y-axis
        //Y-axis
    sf::Text yAxisMid;
    yAxisMid.setFont(font);
    yAxisMid.setCharacterSize(12);
    yAxisMid.setPosition(posX - 7, posY - height / 2);
    yAxisMid.setFillColor(sf::Color::Black);


    //float newDataPoint = 1.0 * dataPoints.size();

//    if (dataPoints.size() > timeSpan) {
 //       for (int i = 0; i < (dataPoints.size() - 1); i++) {
  //          dataPoints[i] = dataPoints[i + 1];
   //     }
    //    dataPoints[dataPoints.size() - 1] = newDataPoint;
    //}
    //else {
      //  dataPoints.push_back(newDataPoint);
    //}

    for (int i = 0; i < dataPoints.size(); i++) {
        if (maxDataPoint < dataPoints[i]) {
            maxDataPoint = dataPoints[i];
            yAxisMax.setString(std::to_string(maxDataPoint));
            yAxisMid.setString(std::to_string(maxDataPoint / 2));
        }
        if (minDataPoint > dataPoints[i]) {
            minDataPoint = dataPoints[i];
        }
    }

    //Ttwice
    if((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints2.size()), timeSpan); i++) {
            chartLines[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * dataPoints2[i] / (maxDataPoint - minDataPoint));
            chartLines[i].color = sf::Color::Red;
        }
        if (static_cast<int>(dataPoints2.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints2.size())); i < std::max(static_cast<int>(dataPoints2.size()), timeSpan); i++) {
                chartLines[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints2.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * dataPoints2[dataPoints2.size() - 1] / (maxDataPoint - minDataPoint));
                chartLines[i].color = sf::Color::Red;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints3.size()), timeSpan); i++) {
            chartLines2[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * dataPoints3[i] / (maxDataPoint - minDataPoint));
            chartLines2[i].color = sf::Color::Blue;
        }
        if (static_cast<int>(dataPoints3.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints3.size())); i < std::max(static_cast<int>(dataPoints3.size()), timeSpan); i++) {
                chartLines2[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints3.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * dataPoints3[dataPoints3.size() - 1] / (maxDataPoint - minDataPoint));
                chartLines2[i].color = sf::Color::Blue;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    yAxisMax.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxisMid.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);

    myPlot.xcoord = xcoord;
    myPlot.ycoord = ycoord;
    myPlot.chartLine = chartLines;
    myPlot.chartLine2 = chartLines2;
    myPlot.maxValue = yAxisMax;
    myPlot.midValue = yAxisMid;
    return myPlot;

}

Plot3 threeLinesPlot(float posX, float posY, std::vector<float> dataPoints, std::vector<float> dataPoints2, std::vector<float> dataPoints3,
    std::vector<float> dataPoints4, sf::Font& font, std::string title, float height, float width, int timeSpan) {

    Plot3 myPlot;


    float maxDataPoint = 0.0;
    float minDataPoint = 0.0;
    //initialise lines
    sf::VertexArray xcoord(sf::LineStrip, 2);
    xcoord.setPrimitiveType(sf::LinesStrip);
    xcoord[0].position = sf::Vector2f(posX, posY);
    xcoord[1].position = sf::Vector2f(posX + width, posY);
    xcoord[0].color = sf::Color::Black;
    xcoord[1].color = sf::Color::Black;


    sf::VertexArray ycoord(sf::LineStrip, 2);
    ycoord.setPrimitiveType(sf::LinesStrip);
    ycoord[0].position = sf::Vector2f(posX, posY);
    ycoord[1].position = sf::Vector2f(posX, posY - height - 30);
    ycoord[0].color = sf::Color::Black;
    ycoord[1].color = sf::Color::Black;

    sf::VertexArray chartLines(sf::LineStrip, timeSpan);
    chartLines.setPrimitiveType(sf::LinesStrip);

    sf::VertexArray chartLines2(sf::LineStrip, timeSpan);
    chartLines2.setPrimitiveType(sf::LinesStrip);

    sf::VertexArray chartLines3(sf::LineStrip, timeSpan);
    chartLines3.setPrimitiveType(sf::LinesStrip);

    //initialise axes string

    //Y-axis
    sf::Text yAxisMax;
    yAxisMax.setFont(font);
    yAxisMax.setCharacterSize(12);
    yAxisMax.setPosition(posX - 7, posY - height);
    yAxisMax.setFillColor(sf::Color::Black);


    //mid Y-axis
        //Y-axis
    sf::Text yAxisMid;
    yAxisMid.setFont(font);
    yAxisMid.setCharacterSize(12);
    yAxisMid.setPosition(posX - 7, posY - height / 2);
    yAxisMid.setFillColor(sf::Color::Black);


    //float newDataPoint = 1.0 * dataPoints.size();

//    if (dataPoints.size() > timeSpan) {
 //       for (int i = 0; i < (dataPoints.size() - 1); i++) {
  //          dataPoints[i] = dataPoints[i + 1];
   //     }
    //    dataPoints[dataPoints.size() - 1] = newDataPoint;
    //}
    //else {
      //  dataPoints.push_back(newDataPoint);
    //}

    for (int i = 0; i < dataPoints.size(); i++) {
        if (maxDataPoint < dataPoints[i]) {
            maxDataPoint = dataPoints[i];
            yAxisMax.setString(std::to_string(maxDataPoint));
            yAxisMid.setString(std::to_string(maxDataPoint / 2));
        }
        if (minDataPoint > dataPoints[i]) {
            minDataPoint = dataPoints[i];
        }
    }

    //Thrice
    if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints2.size()), timeSpan); i++) {
            chartLines[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * dataPoints2[i] / (maxDataPoint - minDataPoint));
            chartLines[i].color = sf::Color::Red;
        }
        if (static_cast<int>(dataPoints2.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints2.size())); i < std::max(static_cast<int>(dataPoints2.size()), timeSpan); i++) {
                chartLines[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints2.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * dataPoints2[dataPoints2.size() - 1] / (maxDataPoint - minDataPoint));
                chartLines[i].color = sf::Color::Red;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints3.size()), timeSpan); i++) {
            chartLines2[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * dataPoints3[i] / (maxDataPoint - minDataPoint));
            chartLines2[i].color = sf::Color::Blue;
        }
        if (static_cast<int>(dataPoints3.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints3.size())); i < std::max(static_cast<int>(dataPoints3.size()), timeSpan); i++) {
                chartLines2[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints3.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * dataPoints3[dataPoints3.size() - 1] / (maxDataPoint - minDataPoint));
                chartLines2[i].color = sf::Color::Blue;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints4.size()), timeSpan); i++) {
            chartLines3[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * dataPoints4[i] / (maxDataPoint - minDataPoint));
            chartLines3[i].color = sf::Color::Green;
        }
        if (static_cast<int>(dataPoints4.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints4.size())); i < std::max(static_cast<int>(dataPoints4.size()), timeSpan); i++) {
                chartLines3[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints4.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * dataPoints4[dataPoints4.size() - 1] / (maxDataPoint - minDataPoint));
                chartLines3[i].color = sf::Color::Green;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    yAxisMax.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxisMid.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);

    myPlot.xcoord = xcoord;
    myPlot.ycoord = ycoord;
    myPlot.chartLine = chartLines;
    myPlot.chartLine2 = chartLines2;
    myPlot.chartLine3 = chartLines3;
    myPlot.maxValue = yAxisMax;
    myPlot.midValue = yAxisMid;
    return myPlot;

}

Plot4 pieChart(float posX, float posY,std::vector<float> dataPoints, std::vector<float> dataPoints2
    , sf::Font& font, std::string title, float radius) {
    Plot4 myPlot;

    float one = dataPoints.size();
    float two = dataPoints2.size();

    float percentageOfFemale = dataPoints2[dataPoints2.size()-1]/ dataPoints[dataPoints.size()-1];

    float degrees = 360;

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(radius, radius);
    circle.setPosition(posX, posY);

    //Create lines
    std::vector<sf::VertexArray> chartlineVector;
    for (int i = 0; i < degrees; i++) {
        sf::VertexArray chartLine(sf::LineStrip,2);
        chartLine.setPrimitiveType(sf::LineStrip);
        chartLine[0].position = sf::Vector2f(posX, posY);
        chartLine[1].position = sf::Vector2f(posX, posY); //will override in the next loop
        chartlineVector.push_back(chartLine);
    }
    if ( (percentageOfFemale != 0) and (percentageOfFemale != 1)) {
        //pie charting
        for (int i = 0; i < degrees; i++) {
            if (i < percentageOfFemale * degrees) {
                chartlineVector[i][1].position = sf::Vector2f(posX + radius * cos(2 * M_PI * i / degrees), posY + radius * sin(2 * M_PI * i / degrees));
                chartlineVector[i][0].color = sf::Color::Magenta;
                chartlineVector[i][1].color = sf::Color::Magenta;
            }
            else {
                chartlineVector[i][1].position = sf::Vector2f(posX + radius * cos(2 * M_PI * i / degrees), posY + radius * sin(2 * M_PI * i / degrees));
                chartlineVector[i][0].color = sf::Color(173, 216, 230);
                chartlineVector[i][1].color = sf::Color(173, 216, 230);
            }
        }
    }

   myPlot.chartlinesVector = chartlineVector;
   myPlot.circle = circle;

   return myPlot;
}

