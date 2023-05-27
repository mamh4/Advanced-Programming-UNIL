#include "OrganicStats.h"
#include <iostream>
#include <vector>
#include <sfml/Graphics.hpp>
#include <string>
#include "OrganicMaths.h"
#include <iomanip>
#include <sstream>


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


Plot2 twoLinesPlot(float posX, float posY, std::vector<float>& dataPoints2, std::vector<float>& dataPoints3,
    sf::Font& font, std::string title, float height, float width, int timeSpan) {
    Plot2 myPlot;


    float maxDataPoint = 0.0;
    float minDataPoint = 0.0;
    //initialise lines
    sf::VertexArray xcoord(sf::LineStrip, 2);
    xcoord.setPrimitiveType(sf::LinesStrip);
    xcoord[0].position = sf::Vector2f(posX, posY);
    xcoord[1].position = sf::Vector2f(posX + width, posY);
    xcoord[0].color = sf::Color::White;
    xcoord[1].color = sf::Color::White;


    sf::VertexArray ycoord(sf::LineStrip, 2);
    ycoord.setPrimitiveType(sf::LinesStrip);
    ycoord[0].position = sf::Vector2f(posX, posY);
    ycoord[1].position = sf::Vector2f(posX, posY - height - 30);
    ycoord[0].color = sf::Color::White;
    ycoord[1].color = sf::Color::White;

    sf::VertexArray chartLines(sf::LineStrip, timeSpan);
    chartLines.setPrimitiveType(sf::LinesStrip);

    sf::VertexArray chartLines2(sf::LineStrip, timeSpan);
    chartLines2.setPrimitiveType(sf::LinesStrip);

    //title
    //TODO include label Predator with red rectangle, and prey with blue rectangle, for next plot do the same and include green for Fauna
    sf::Text theTitle;
    theTitle.setFont(font);
    theTitle.setCharacterSize(12);
    theTitle.setPosition(posX +(width)/2,posY-height-15);//posX+width/2 , posY - height-20);
    theTitle.setFillColor(sf::Color::White);
    theTitle.setString(title);
    theTitle.setOrigin(theTitle.getGlobalBounds().width/2, 0);
    theTitle.setStyle(sf::Text::Italic);



    //ylabes
    sf::Text ylabel;
    ylabel.setFont(font);
    ylabel.setCharacterSize(12);
    ylabel.setPosition(posX+width-ylabel.getGlobalBounds().width, posY + 8);
    ylabel.setFillColor(sf::Color::White);
    ylabel.setString("Simulation Time");
    ylabel.setOrigin(ylabel.getGlobalBounds().width, 0);


    //X-axis
    sf::Text xAxisMax;
    xAxisMax.setFont(font);
    xAxisMax.setCharacterSize(12);
    xAxisMax.setPosition(posX + width, posY +5);
    xAxisMax.setFillColor(sf::Color::White);
    float maxXDataPoint = timeSpan / 60.0;

    sf::Text xAxisMid;
    xAxisMid.setFont(font);
    xAxisMid.setCharacterSize(12);
    xAxisMid.setPosition(posX + width/2, posY + 5);
    xAxisMid.setFillColor(sf::Color::White);

    sf::Text xAxis25;
    xAxis25.setFont(font);
    xAxis25.setCharacterSize(12);
    xAxis25.setPosition(posX + width / 4, posY + 5);
    xAxis25.setFillColor(sf::Color::White);

    sf::Text xAxis75;
    xAxis75.setFont(font);
    xAxis75.setCharacterSize(12);
    xAxis75.setPosition(posX + 3*width / 4, posY + 5);
    xAxis75.setFillColor(sf::Color::White);






    if (dataPoints2.size() >= timeSpan) {
        maxXDataPoint = simulationTime / 60.0;
        }



    std::stringstream streamx;
    streamx << std::fixed << std::setprecision(1) << maxXDataPoint;
    std::string maxX = streamx.str();
    xAxisMax.setString(maxX);


    std::stringstream stream2x;
    stream2x << std::fixed << std::setprecision(1) << (maxXDataPoint / 2.0);
    std::string midX = stream2x.str();
    xAxisMid.setString(midX);


    std::stringstream stream3x;
    stream3x << std::fixed << std::setprecision(1) << (maxXDataPoint / 4.0);
    std::string m25x = stream3x.str();
    xAxis25.setString(m25x);


    std::stringstream stream4x;
    stream4x << std::fixed << std::setprecision(1) << (maxXDataPoint * 3.0 / 4.0);
    std::string m75x = stream4x.str();
    xAxis75.setString(m75x);



    //initialise axes string
    // 
    //Y-axis
    sf::Text yAxisMax;
    yAxisMax.setFont(font);
    yAxisMax.setCharacterSize(12);
    yAxisMax.setPosition(posX - 7, posY - height);
    yAxisMax.setFillColor(sf::Color::White);


    //mid Y-axis
        //Y-axis
    sf::Text yAxisMid;
    yAxisMid.setFont(font);
    yAxisMid.setCharacterSize(12);
    yAxisMid.setPosition(posX - 7, posY - height / 2);
    yAxisMid.setFillColor(sf::Color::White);

    sf::Text yAxis75;
    yAxis75.setFont(font);
    yAxis75.setCharacterSize(12);
    yAxis75.setPosition(posX - 7, posY - (height * 3.0 / 4.0));
    yAxis75.setFillColor(sf::Color::White);


    sf::Text yAxis25;
    yAxis25.setFont(font);
    yAxis25.setCharacterSize(12);
    yAxis25.setPosition(posX - 7, posY - (height * 1 / 4.0));
    yAxis25.setFillColor(sf::Color::White);



    if (dataPoints2.size() > timeSpan) {
        for (int i = 0; i < (dataPoints2.size() - 1); i++) {
            dataPoints2[i] = dataPoints2[i + 1];
        }
        dataPoints2.pop_back();
    }
    

    if (dataPoints3.size() > timeSpan) {
        for (int i = 0; i < (dataPoints3.size() - 1); i++) {
            dataPoints3[i] = dataPoints3[i + 1];
        }
        dataPoints3.pop_back();
    }




    //Was commented
    //if (dataPoints.size() > 0 ){
      //  maxDataPoint = dataPoints[0] ; 
     //   minDataPoint = dataPoints[0] ; 
    //}
    //std::vector<float> maximumVector;
    //for (int i = 0; i < dataPoints2.size();i++) {
     //   maximumVector.push_back(std::max(dataPoints2[i], dataPoints3[i]));
    //}

    //for (int i = 0; i < dataPoints.size(); i++) {
     //   if (maxDataPoint < dataPoints[i] ) {
      //      maxDataPoint = dataPoints[i] ;
       // }
        //if (minDataPoint > dataPoints[i]) {
         //   minDataPoint = dataPoints[i];
        //}
    //}
    
    for (int i = 0; i < dataPoints2.size(); i++) {
        if (maxDataPoint < std::max(dataPoints2[i], dataPoints3[i])) {
            maxDataPoint = std::max(dataPoints2[i], dataPoints3[i]);
        }
        if (minDataPoint > std::min(dataPoints2[i], dataPoints3[i])) {
			minDataPoint = std::min(dataPoints2[i], dataPoints3[i]);
		}
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << maxDataPoint;
    std::string max = stream.str();
    yAxisMax.setString(max);


    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(1) << (minDataPoint + ( maxDataPoint - minDataPoint) / 2.0);
    std::string mid = stream2.str();
    yAxisMid.setString(mid);
        
            
    std::stringstream stream3;
    stream3 << std::fixed << std::setprecision(1) << (minDataPoint + ( maxDataPoint - minDataPoint) / 4.0);
    std::string m25 = stream3.str();
    yAxis25.setString(m25);


    std::stringstream stream4;
    stream4 << std::fixed << std::setprecision(1) << (minDataPoint + ( maxDataPoint - minDataPoint) * 3.0 / 4.0);
    std::string m75 = stream4.str();
    yAxis75.setString(m75);

    //Twice
    if((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints2.size()), timeSpan); i++) {
            chartLines[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * (dataPoints2[i]- minDataPoint) / (maxDataPoint - minDataPoint));
            chartLines[i].color = sf::Color::Red;
        }
        if (static_cast<int>(dataPoints2.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints2.size())); i < std::max(static_cast<int>(dataPoints2.size()), timeSpan); i++) {
                chartLines[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints2.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * (dataPoints2[dataPoints2.size() - 1] - minDataPoint)/ (maxDataPoint - minDataPoint));
                chartLines[i].color = sf::Color::Red;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    if ((maxDataPoint - minDataPoint) != 0.0) {//Removed if timeframe==0
        for (int i = 0; i < std::min(static_cast<int>(dataPoints3.size()), timeSpan); i++) {
            chartLines2[i].position = sf::Vector2f(posX + 1.0 * i * width / (timeSpan * 1.0),
                posY - height * (dataPoints3[i]- minDataPoint) / (maxDataPoint - minDataPoint));
            chartLines2[i].color = sf::Color::Blue;
        }
        if (static_cast<int>(dataPoints3.size()) < timeSpan) {
            for (int i = (static_cast<int>(dataPoints3.size())); i < std::max(static_cast<int>(dataPoints3.size()), timeSpan); i++) {
                chartLines2[i].position = sf::Vector2f(posX + 1.0 * (static_cast<int>(dataPoints3.size()) - 1) * width / (timeSpan * 1.0),
                    posY - height * (dataPoints3[dataPoints3.size() - 1] - minDataPoint)/ (maxDataPoint - minDataPoint));
                chartLines2[i].color = sf::Color::Blue;
            }// CHECK SOLIDITY AS THIS WAS BUILT LAZILY 
        }
    }

    yAxisMax.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxisMid.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxis25.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxis75.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    xAxisMax.setOrigin(xAxisMax.getLocalBounds().width, xAxisMax.getLocalBounds().height);
    xAxisMid.setOrigin(xAxisMid.getLocalBounds().width, xAxisMid.getLocalBounds().height);
    xAxis25.setOrigin(xAxis25.getLocalBounds().width, xAxis25.getLocalBounds().height);
    xAxis75.setOrigin(xAxis75.getLocalBounds().width, xAxis75.getLocalBounds().height);


    myPlot.xcoord = xcoord;
    myPlot.ycoord = ycoord;
    myPlot.chartLine = chartLines;
    myPlot.chartLine2 = chartLines2;
    myPlot.maxValue = yAxisMax;
    myPlot.midValue = yAxisMid;
    myPlot.percentile25 = yAxis25;
    myPlot.percentile75 = yAxis75;
    myPlot.title = theTitle;
    myPlot.maxXValue = xAxisMax;
    myPlot.midXValue = xAxisMid;
    myPlot.percentile25XValue  = xAxis25;
    myPlot.percentile75XValue = xAxis75;
    myPlot.ylabel = ylabel;

    return myPlot;

}

Plot3 threeLinesPlot(float posX, float posY, std::vector<float>& dataPoints2, std::vector<float>& dataPoints3,
    std::vector<float>& dataPoints4, sf::Font& font, std::string title, float height, float width, int timeSpan) {

    Plot3 myPlot;


    float maxDataPoint = 0.0;
    float minDataPoint = 0.0;
    //initialise lines
    sf::VertexArray xcoord(sf::LineStrip, 2);
    xcoord.setPrimitiveType(sf::LinesStrip);
    xcoord[0].position = sf::Vector2f(posX, posY);
    xcoord[1].position = sf::Vector2f(posX + width, posY);
    xcoord[0].color = sf::Color::White;
    xcoord[1].color = sf::Color::White;


    sf::VertexArray ycoord(sf::LineStrip, 2);
    ycoord.setPrimitiveType(sf::LinesStrip);
    ycoord[0].position = sf::Vector2f(posX, posY);
    ycoord[1].position = sf::Vector2f(posX, posY - height - 30);
    ycoord[0].color = sf::Color::White;
    ycoord[1].color = sf::Color::White;

    sf::VertexArray chartLines(sf::LineStrip, timeSpan);
    chartLines.setPrimitiveType(sf::LinesStrip);

    sf::VertexArray chartLines2(sf::LineStrip, timeSpan);
    chartLines2.setPrimitiveType(sf::LinesStrip);

    sf::VertexArray chartLines3(sf::LineStrip, timeSpan);
    chartLines3.setPrimitiveType(sf::LinesStrip);

    //title
    sf::Text theTitle;
    theTitle.setFont(font);
    theTitle.setCharacterSize(12);
    theTitle.setPosition(posX + width / 2, posY - height - 15);//posX+width/2 , posY - height-20);
    theTitle.setFillColor(sf::Color::White);
    theTitle.setString(title);
    theTitle.setOrigin(theTitle.getGlobalBounds().width / 2, 0);
    theTitle.setStyle(sf::Text::Italic);

    //initialise axes string

        //X-axis
    sf::Text xAxisMax;
    xAxisMax.setFont(font);
    xAxisMax.setCharacterSize(12);
    xAxisMax.setPosition(posX + width, posY + 5);
    xAxisMax.setFillColor(sf::Color::White);
    float maxXDataPoint = timeSpan / 60.0;

    sf::Text xAxisMid;
    xAxisMid.setFont(font);
    xAxisMid.setCharacterSize(12);
    xAxisMid.setPosition(posX + width / 2, posY + 5);
    xAxisMid.setFillColor(sf::Color::White);

    sf::Text xAxis25;
    xAxis25.setFont(font);
    xAxis25.setCharacterSize(12);
    xAxis25.setPosition(posX + width / 4, posY + 5);
    xAxis25.setFillColor(sf::Color::White);

    sf::Text xAxis75;
    xAxis75.setFont(font);
    xAxis75.setCharacterSize(12);
    xAxis75.setPosition(posX + 3 * width / 4, posY + 5);
    xAxis75.setFillColor(sf::Color::White);




    if (dataPoints2.size() >= timeSpan) {
        maxXDataPoint = simulationTime / 60.0;
    }



    std::stringstream streamx;
    streamx << std::fixed << std::setprecision(1) << maxXDataPoint;
    std::string maxX = streamx.str();
    xAxisMax.setString(maxX);


    std::stringstream stream2x;
    stream2x << std::fixed << std::setprecision(1) << (maxXDataPoint / 2.0);
    std::string midX = stream2x.str();
    xAxisMid.setString(midX);


    std::stringstream stream3x;
    stream3x << std::fixed << std::setprecision(1) << (maxXDataPoint / 4.0);
    std::string m25x = stream3x.str();
    xAxis25.setString(m25x);


    std::stringstream stream4x;
    stream4x << std::fixed << std::setprecision(1) << (maxXDataPoint * 3.0 / 4.0);
    std::string m75x = stream4x.str();
    xAxis75.setString(m75x);



    //Y-axis
    sf::Text yAxisMax;
    yAxisMax.setFont(font);
    yAxisMax.setCharacterSize(12);
    yAxisMax.setPosition(posX - 7, posY - height);
    yAxisMax.setFillColor(sf::Color::White);


    sf::Text yAxisMid;
    yAxisMid.setFont(font);
    yAxisMid.setCharacterSize(12);
    yAxisMid.setPosition(posX - 7, posY - height / 2);
    yAxisMid.setFillColor(sf::Color::White);


    sf::Text yAxis75;
    yAxis75.setFont(font);
    yAxis75.setCharacterSize(12);
    yAxis75.setPosition(posX - 7, posY - (height * 3.0 / 4.0));
    yAxis75.setFillColor(sf::Color::White);


    sf::Text yAxis25;
    yAxis25.setFont(font);
    yAxis25.setCharacterSize(12);
    yAxis25.setPosition(posX - 7, posY - (height * 1 / 4.0));
    yAxis25.setFillColor(sf::Color::White);

    if (dataPoints2.size() > timeSpan) {
        for (int i = 0; i < (dataPoints2.size() - 1); i++) {
            dataPoints2[i] = dataPoints2[i + 1];
        }
        dataPoints2.pop_back();
    }


    if (dataPoints3.size() > timeSpan) {
        for (int i = 0; i < (dataPoints3.size() - 1); i++) {
            dataPoints3[i] = dataPoints3[i + 1];
        }
        dataPoints3.pop_back();
    }

    if (dataPoints4.size() > timeSpan) {
        for (int i = 0; i < (dataPoints4.size() - 1); i++) {
            dataPoints4[i] = dataPoints4[i + 1];
        }
        dataPoints4.pop_back();
    }

    for (int i = 0; i < dataPoints2.size(); i++) {
        if (maxDataPoint < std::max(dataPoints2[i], std::max(dataPoints3[i], dataPoints4[i]))) {
            maxDataPoint = std::max(dataPoints2[i], std::max(dataPoints3[i], dataPoints4[i]));
        }
        if (minDataPoint > std::min(dataPoints2[i], std::min(dataPoints3[i], dataPoints4[i]))) {
			minDataPoint = std::min(dataPoints2[i], std::min(dataPoints3[i], dataPoints4[i]));
		}
    }



    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << maxDataPoint;
    std::string max = stream.str();
    yAxisMax.setString(max);


    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(1) << (maxDataPoint / 2.0);
    std::string mid = stream2.str();
    yAxisMid.setString(mid);


    std::stringstream stream3;
    stream3 << std::fixed << std::setprecision(1) << (maxDataPoint * 1 / 4.0);
    std::string m25 = stream3.str();
    yAxis25.setString(m25);


    std::stringstream stream4;
    stream4 << std::fixed << std::setprecision(1) << (maxDataPoint * 3.0 / 4.0);
    std::string m75 = stream4.str();
    yAxis75.setString(m75);


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
    yAxis25.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    yAxis75.setOrigin(yAxisMax.getLocalBounds().width, yAxisMax.getLocalBounds().height);
    xAxisMax.setOrigin(xAxisMax.getLocalBounds().width, xAxisMax.getLocalBounds().height);
    xAxisMid.setOrigin(xAxisMid.getLocalBounds().width, xAxisMid.getLocalBounds().height);
    xAxis25.setOrigin(xAxis25.getLocalBounds().width, xAxis25.getLocalBounds().height);
    xAxis75.setOrigin(xAxis75.getLocalBounds().width, xAxis75.getLocalBounds().height);

    myPlot.xcoord = xcoord;
    myPlot.ycoord = ycoord;
    myPlot.chartLine = chartLines;
    myPlot.chartLine2 = chartLines2;
    myPlot.chartLine3 = chartLines3;
    myPlot.maxValue = yAxisMax;
    myPlot.midValue = yAxisMid;
    myPlot.percentile25 = yAxis25;
    myPlot.percentile75 = yAxis75;
    myPlot.maxXValue = xAxisMax;
    myPlot.midXValue = xAxisMid;
    myPlot.percentile25XValue = xAxis25;
    myPlot.percentile75XValue = xAxis75;
    myPlot.title = theTitle;
    return myPlot;

}

Plot4 pieChart(float posX, float posY,std::vector<float> dataPoints, std::vector<float> dataPoints2
    , sf::Font& font, std::string title, float radius) {
    Plot4 myPlot;

    float percentageOfFemale = dataPoints2[dataPoints2.size()-1]/ dataPoints[dataPoints.size()-1];

    float degrees = 360;

    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(sf::Color(120, 120, 120));
    circle.setOrigin(radius, radius);
    circle.setPosition(posX, posY);
    circle.setOutlineColor(sf::Color(120, 120, 120));

    //Create lines
    std::vector<sf::VertexArray> chartlineVector;
    for (int i = 0; i < degrees; i++) {
        sf::VertexArray chartLine(sf::LineStrip,2);
        chartLine.setPrimitiveType(sf::LineStrip);
        chartLine[0].position = sf::Vector2f(posX, posY);
        chartLine[1].position = sf::Vector2f(posX, posY); //will override in the next loop
        chartlineVector.push_back(chartLine);
    }

    //Title
    sf::Text theTitle;
    theTitle.setFont(font);
    theTitle.setCharacterSize(12);
    theTitle.setPosition(posX-radius, posY - radius - 16);
    theTitle.setFillColor(sf::Color::White);
    theTitle.setString(title);

    //Data Label //TODO: add small rectangles with colors Male Female and with percentages next to them.
    sf::Text theLabel;
    theLabel.setFont(font);
    theLabel.setCharacterSize(12);
    theLabel.setFillColor(sf::Color::White);
    
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << (percentageOfFemale*100.0);
    std::string percentage = stream.str();
    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << (100.0 - (percentageOfFemale * 100.0));
    std::string percentageComplement = stream2.str();
    theLabel.setString( "Female: " +percentage + " %" +"\n"+
                        "Male: " + percentageComplement + " %");
    theLabel.setPosition(posX, posY + radius + 50);
    theLabel.setOrigin(radius, radius);

    //pie charting
if (dataPoints[dataPoints.size() - 1] != 0) {
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
else {
    theLabel.setString("No Data available!");
    theLabel.setPosition(posX, posY + radius + 50);
    theLabel.setOrigin(radius, radius);
}
   

   myPlot.chartlinesVector = chartlineVector;
   myPlot.circle = circle ; 
   //myPlot.title = theTitle;
   myPlot.xlabel = theLabel;
   return myPlot;
}



Plot5 pieChart2(float posX, float posY, std::vector<float> dataPoints, std::vector<float> dataPoints2,
    std::vector<float> dataPoints3, std::vector<float> dataPoints4,
    sf::Font& font, std::string title, float radius) {
    Plot5 myPlot;

    float percentageOfFemale = dataPoints2[dataPoints2.size() - 1] / dataPoints[dataPoints.size() - 1];
    float percentageOfFertileFemale = dataPoints3[dataPoints3.size() - 1] / dataPoints2[dataPoints2.size() - 1];
    float percentageOfFertileMale = dataPoints4[dataPoints4.size() - 1] / (dataPoints[dataPoints.size() - 1] - dataPoints2[dataPoints2.size() - 1]);
    
    float degrees = 360;

    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(sf::Color(120, 120, 120));
    circle.setOrigin(radius, radius);
    circle.setPosition(posX, posY);
    circle.setOutlineColor(sf::Color(120, 120, 120));

    //Create lines
    std::vector<sf::VertexArray> chartlineVector;
    std::vector<sf::VertexArray> chartlineVector2;
    //smaller piechart
    for (int i = 0; i < degrees; i++) {
        sf::VertexArray chartLine(sf::LineStrip, 2);
        chartLine.setPrimitiveType(sf::LineStrip);
        chartLine[0].position = sf::Vector2f(posX, posY);
        chartLine[1].position = sf::Vector2f(posX, posY); //will override in the next loop
        chartlineVector.push_back(chartLine);
        //bigger piechart
        sf::VertexArray chartLine2(sf::LineStrip, 2);
        chartLine2.setPrimitiveType(sf::LineStrip);
        chartLine2[0].position = sf::Vector2f(posX, posY);
        chartLine2[1].position = sf::Vector2f(posX, posY); //will override in the next loop
        chartlineVector2.push_back(chartLine);
    }

    //Title
    sf::Text theTitle;
    theTitle.setFont(font);
    theTitle.setCharacterSize(12);
    theTitle.setPosition(posX - radius, posY - radius - 16);
    theTitle.setFillColor(sf::Color::White);
    theTitle.setString(title);

    //Data Label //TODO: add small rectangles with colors Male Female and with percentages next to them.
    sf::Text theLabel;
    theLabel.setFont(font);
    theLabel.setCharacterSize(12);
    theLabel.setFillColor(sf::Color::White);

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << (percentageOfFemale * 100.0);
    std::string percentage = stream.str();
    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << (100.0 - (percentageOfFemale * 100.0));
    std::string percentageComplement = stream2.str();
    theLabel.setString("     " + title +std::string("\n") + "Female: " + percentage + " % " + "\n" +
        "Male: " + percentageComplement + " %");
    theLabel.setPosition(posX-10, posY + radius + 50);
    theLabel.setOrigin(radius, radius);

    float additionalRadius = 10;
    //pie charting
    if (dataPoints[dataPoints.size() - 1] != 0) {
        for (int i = degrees-1; i >= 0; i--) {
            chartlineVector[i][1].position = sf::Vector2f(posX + radius * cos(2 * M_PI * i / degrees), posY + radius * sin(2 * M_PI * i / degrees));
            chartlineVector2[i][1].position = sf::Vector2f(posX + (radius + additionalRadius) * cos(2 * M_PI * i / degrees), posY + (radius + additionalRadius) * sin(2 * M_PI * i / degrees));
            if (i >= degrees-( percentageOfFemale * degrees)) {
                //chartlineVector[i][1].position = sf::Vector2f(posX + radius * cos(2 * M_PI * i / degrees), posY + radius * sin(2 * M_PI * i / degrees));
                chartlineVector[i][0].color = sf::Color::Magenta;//female colour
                chartlineVector[i][1].color = sf::Color::Magenta;
                //bigger plots
                if (i >= degrees - ( percentageOfFertileFemale * degrees)) {
					chartlineVector2[i][0].color = sf::Color::Color(255, 165, 0);//fertile colour
					chartlineVector2[i][1].color = sf::Color::Color(255, 165, 0);
                }
                else {
                    //chartlineVector2[i][1].position = sf::Vector2f(posX + (radius + additionalRadius) * cos(2 * M_PI * i / degrees), posY + (radius + additionalRadius) * sin(2 * M_PI * i / degrees));
                    chartlineVector2[i][0].color = sf::Color(120, 120, 120);
                    chartlineVector2[i][1].color = sf::Color(120,120,120);
                }
            }
            else {
                //chartlineVector[i][1].position = sf::Vector2f(posX + radius * cos(2 * M_PI * i / degrees), posY + radius * sin(2 * M_PI * i / degrees));
                chartlineVector[i][0].color = sf::Color(173, 216, 230);//male colour
                chartlineVector[i][1].color = sf::Color(173, 216, 230);
                //bigger plots 
                if (i >= degrees -( percentageOfFertileMale * degrees)) {
                    //chartlineVector2[i][1].position = sf::Vector2f(posX + (radius + additionalRadius) * cos(2 * M_PI * i / degrees), posY + (radius + additionalRadius) * sin(2 * M_PI * i / degrees));
                    chartlineVector2[i][0].color = sf::Color::Color(255, 165, 0);
                    chartlineVector2[i][1].color = sf::Color::Color(255, 165, 0);
                }
                else {
                    //chartlineVector2[i][1].position = sf::Vector2f(posX + (radius + additionalRadius) * cos(2 * M_PI * i / degrees), posY + (radius + additionalRadius) * sin(2 * M_PI * i / degrees));
                    chartlineVector2[i][0].color = sf::Color::Color(120, 120, 120);
                    chartlineVector2[i][1].color = sf::Color::Color(120, 120, 120);
                }
            }
        }
    }
    else {
        theLabel.setString("No Data available!");
        theLabel.setPosition(posX, posY + radius + 50);
        theLabel.setOrigin(radius, radius);
    }


    myPlot.chartlinesVector = chartlineVector;
    myPlot.chartlinesVector2 = chartlineVector2;
    myPlot.circle = circle;
    //myPlot.title = theTitle;
    myPlot.xlabel = theLabel;
    return myPlot;
}






TraitSummaryStatistics preySpeedSummaryStatistics = {
    "Speed",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics preyHungerSensitivitySummaryStatistics = {
    "Hunger Sensitivity", 
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics preyMetabolicRateSummaryStatistics = {
    "Metabolic Rate", 
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics preyLustLevelSummaryStatistics = {
    "Lust Level",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics preyVisionRangeSummaryStatistics = {
    "Vision Range",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics preyPredatorAversionSummaryStatistics = {
    "Predator Aversion",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics predatorSpeedSummaryStatistics = {
    "Speed",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics predatorHungerSensitivitySummaryStatistics = {
    "Hunger Sensitivity", 
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics predatorMetabolicRateSummaryStatistics = {
    "Metabolic Rate", 
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics predatorLustLevelSummaryStatistics = {
    "Lust Level",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};
TraitSummaryStatistics predatorVisionRangeSummaryStatistics = {
    "Vision Range",
    {0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }, 
	{0.0 , 0.0, 0.0 }
};

SpeciesSummaryStatistics preySummaryStatistics = {
    "Prey" ,
    {preySpeedSummaryStatistics, preyHungerSensitivitySummaryStatistics, preyMetabolicRateSummaryStatistics, preyLustLevelSummaryStatistics, preyVisionRangeSummaryStatistics, preyPredatorAversionSummaryStatistics }
};

SpeciesSummaryStatistics predatorSummaryStatistics = {
     "Predator",
    {predatorSpeedSummaryStatistics, predatorHungerSensitivitySummaryStatistics, predatorMetabolicRateSummaryStatistics, predatorLustLevelSummaryStatistics, predatorVisionRangeSummaryStatistics }
};

std::vector<SpeciesSummaryStatistics> summaryStatistics = { preySummaryStatistics, predatorSummaryStatistics };