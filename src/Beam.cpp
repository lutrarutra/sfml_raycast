#include "Beam.h"

Beam::Beam(int x, int y, float angle) : m_x(x), m_y(y), m_angle(angle), m_line(x, y, angle, 3)
{
}

void Beam::draw(sf::RenderWindow &window) const
{
    m_line.draw(window);
}

void Beam::checkCollision(Wall &wall)
{
}

void Beam::move(int x, int y)
{
    m_line.move(x, y);
}

Beam::~Beam()
{
}