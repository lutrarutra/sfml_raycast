#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Line.h"
#include "Wall.h"

class Beam
{
public:
    Beam(int x, int y, float angle);
    void draw(sf::RenderWindow &window) const;
    void move(int x, int y);
    void checkCollision(const Wall &wall);
    ~Beam();

private:
    Line m_line;
    int m_x, m_y;
    float m_angle;
};
