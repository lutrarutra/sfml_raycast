#define _USE_MATH_DEFINES

#include "math.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Source.h"


#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#endif 

int main()
{
    std::cout << "Hello" << std::endl;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "project_name", sf::Style::Close, settings);
    Source s(200, 650, 1080);

    std::vector<Wall> walls;
    walls.reserve(4);
    walls.emplace_back(300, 50, 800, 600);
    walls.emplace_back(700, 500, 1200, 850);
    walls.emplace_back(1000, 50, 800, 120);
    walls.emplace_back(600, 700, 300, 550);
    
    while (window.isOpen())
    {
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                window.close();
            if (Event.type == sf::Event::MouseMoved)
            {           
                s.Move({(float)sf::Mouse::getPosition(window).x , (float)sf::Mouse::getPosition(window).y});
            }
        }
        window.clear(sf::Color::Black);
        s.checkWalls(walls);
        s.Draw(window);
        for (int i = 0; i < walls.size(); ++i)
        {
            walls[i].Draw(window);
        }
        window.display();
    }
}