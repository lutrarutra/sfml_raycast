#include <math.h>
#include <iostream>
#include "Beam.h"

#define SX 1280
#define SY 720
#define RAD 3.14159265 / 180.0

Beam::Beam(int x, int y, float angle) : m_x(x), m_y(y), m_angle(angle), m_line(x, y, angle, 2)
{
}

void Beam::draw(sf::RenderWindow &window) const
{
    m_line.draw(window);
}

void Beam::checkCollision(const Wall &wall)
{
    float x1 = m_line.getX1();
    float y1 = m_line.getY1();
    float x2 = m_line.getX2();
    float y2 = m_line.getY2();
    float hypo = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));

    float x3 = wall.getX1();
    float y3 = wall.getY1();
    float x4 = wall.getX2();
    float y4 = wall.getY2();

    float numerator1 = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4);
    float numerator2 = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3));
    float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (denominator != 0)
    {
        const float t = numerator1 / denominator;
        const float u = numerator2 / denominator;
        if (0 < u && 0 < t && u < 1)
        {
            //std::cout << t << " " << u << std::endl;
            float intersection_x = x1 + t * (x2 - x1);
            float intersection_y = y1 + t * (y2 - y1);
            //std::cout << intersection_x << " " << intersection_y << std::endl;
            //m_line.setLength(sqrt(pow(m_x - intersection_x, 2) + pow(m_y - intersection_y, 2)));
            m_line.setEndPoint(intersection_x, intersection_y);
        }
        else
        {
            m_line.setLength(sqrt(pow(SX, 2) + pow(SY, 2)));
        }
    }
    else
    {
        m_line.setLength(sqrt(pow(SX, 2) + pow(SY, 2)));
    }
}

void Beam::move(int x, int y)
{
    m_x = x;
    m_y = y;
    m_line.move(x, y);
}

Beam::~Beam()
{
}