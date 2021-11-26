#pragma once
#include "proj_data.h"
#include "Point.h"
#include "Wall.h"
#include "Source.h"

class Game
{
public:
    Game();

    ~Game();

    void Run();

    void AddWall(Point& start, Point& end);

    void AddWall( Point&& start, Point&& end );

private:
    void Redraw();

    void InitWindow();

private:
    sf::ContextSettings m_settings;
    std::vector<Wall> m_walls;
    std::unique_ptr<sf::RenderWindow> m_window;
    Source m_source;
};

