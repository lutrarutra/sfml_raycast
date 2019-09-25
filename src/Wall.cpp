#include <math.h>

#include "Wall.h"

Wall::Wall(int x1, int y1, int x2, int y2) : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_line(m_x1, m_y1, m_x2, m_y2, 3)
{

}

void Wall::draw(sf::RenderWindow &window) const
{
    m_line.draw(window);
}

Wall::~Wall()
{
    
}

