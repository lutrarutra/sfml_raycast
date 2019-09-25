#include <iostream>
#include <SFML/Graphics.hpp>

#include "Wall.h"
#include "Source.h"

int main()
{
    std::cout << "Hello" << std::endl;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "project_name", sf::Style::Close, settings);
    Wall wall(100, 50, 800, 600);
    Source s(window.getSize().x / 2, window.getSize().y / 2, 36);
    while (window.isOpen())
    {
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                window.close();
            if (Event.type == sf::Event::MouseMoved)
            {
                s.move(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            }
        }
        window.clear(sf::Color::White);
        s.draw(window);
        //wall.draw(window);
        window.display();
    }
}