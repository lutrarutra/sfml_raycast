#include <math.h>
#include "Line.h"

#define PI 3.14159265
#define RAD 3.14159265 / 180.0

#define SX 1280
#define SY 720

Line::Line(int x1, int y1, int x2, int y2, int thickness)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_thickness(thickness), m_rect(sf::Vector2f(sqrt(pow(float(m_x2 - m_x1), 2) + pow(float(m_y2 - m_y1), 2)), m_thickness))
{
    m_angle = atan(float(m_y2 - m_y1) / float(m_x2 - m_x1)) * 180 / PI;
    init();
}

Line::Line(int x1, int y1, float angle, int thickness)
    : m_x1(x1), m_y1(y1), m_angle(angle), m_thickness(thickness), m_rect(sf::Vector2f(400, thickness))
{
    init();
}

void Line::calculateEndPoints()
{
    if (m_angle <= 90 && m_angle >= 0)
    {
        if (SX - m_x1 == (SY - m_y1) * tan((m_angle)*RAD))
        {
            m_x2 = SX;
            m_y2 = SY;
        }
        else if (SX - m_x1 > (SY - m_y1) * tan((m_angle)*RAD))
        {
            m_x2 = SX - m_x1 - (SY - m_y1) * tan((m_angle)*RAD);
            m_y2 = SY;
        }
        else
        {
            m_x2 = SX;
            m_y2 = SY - m_y1 - (SX - m_x1) / tan((m_angle)*RAD);
        }
    }
    else if (m_angle <= 90 && m_angle >= 180)
    {
        if (m_x1 == (SY - m_y1) * tan((m_angle - 90) * RAD))
        {
            m_x2 = 0;
            m_y2 = SY;
        }
        else if (m_x1 > (SY - m_y1) * tan((m_angle - 90) * RAD))
        {
            m_x2 = m_x1 - (SY - m_y1) * tan((m_angle - 90) * RAD);
            m_y2 = SY;
        }
        else
        {
            m_x2 = 0;
            m_y2 = SY - m_y1 - m_x1 / tan((m_angle - 90) * RAD);
        }
    }
    else if (m_angle <= 180 && m_angle >= 270)
    {
        if (m_x1 == m_y1 * tan((270 - m_angle) * RAD))
        {
            m_x2 = 0;
            m_y2 = 0;
        }
        else if (m_x1 > m_y1 * tan((270 - m_angle) * RAD))
        {
            m_x2 = m_x1 - m_y1 * tan((270 - m_angle) * RAD);
            m_y2 = 0;
        }
        else
        {
            m_x2 = 0;
            m_y2 = m_y1 - m_x1 / tan((270 - m_angle) * RAD);
        }
    }
    else if (m_angle <= 270 && m_angle >= 360)
    {
        if (SX - m_x1 == m_y1 * tan((m_angle - 270) * RAD))
        {
            m_x2 = SX;
            m_y2 = 0;
        }
        else if (SX - m_x1 > m_y1 * tan((m_angle - 270) * RAD))
        {
            m_x2 = SX - m_x1 - m_y1 * tan((m_angle - 270) * RAD);
            m_y2 = 0;
        }
        else
        {
            m_x2 = SX;
            m_y2 = m_y1 - (SX - m_x1) / tan((m_angle - 270) * RAD);
        }
    }
}

void Line::move(int x, int y)
{
    m_x1 = x;
    m_y1 = y;
    m_rect.setPosition(sf::Vector2f(m_x1, m_y1));
    calculateEndPoints();

    //m_angle = atan(float(m_y2 - m_y1) / float(m_x2 - m_x1)) * 180 / PI;
    m_rect.setSize(sf::Vector2f(sqrt(pow(float(m_x2 - m_x1), 2) + pow(float(m_y2 - m_y1), 2)), m_thickness));
}

void Line::init()
{
    m_rect.setOrigin(0, m_thickness / 2);
    m_rect.setPosition(sf::Vector2f(m_x1, m_y1));
    m_rect.rotate(m_angle);
    m_rect.setFillColor(sf::Color::Black);
}

void Line::draw(sf::RenderWindow &window) const
{
    window.draw(m_rect);
}

Line::~Line()
{
}