#include <math.h>
#include <iostream>
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
    m_rect.setFillColor(sf::Color(255, 255, 255, 250));
}

Line::Line(int x1, int y1, float angle, int thickness)
    : m_x1(x1), m_y1(y1), m_angle(angle), m_thickness(thickness), m_rect(sf::Vector2f(sqrt(pow(SX, 2) + pow(SY, 2)), thickness))
{
    init();
    calculateEndPoints();
    m_rect.setFillColor(sf::Color(255, 255, 255, 50));
}

void Line::setLength(float len)
{
    m_rect.setSize(sf::Vector2f(len, m_thickness));
}

void Line::setEndPoint(int x, int y)
{
    m_x2 = x;
    m_y2 = y;
    m_rect.setSize(sf::Vector2f(sqrt(pow(float(m_x2 - m_x1), 2) + pow(float(m_y2 - m_y1), 2)), m_thickness));
}

void Line::calculateEndPoints()
{
    float hypo = sqrt(pow(m_rect.getSize().x, 2) + pow(m_rect.getSize().y, 2));
    if (m_angle >= 0 && m_angle <= 90)
    {
        m_x2 = m_x1 + cos(m_angle * RAD) * hypo;
        m_y2 = m_y1 + sin(m_angle * RAD) * hypo;
    }
    else if (m_angle >= 90 && m_angle <= 180)
    {
        m_x2 = m_x1 - cos((180-m_angle) * RAD) * hypo;
        m_y2 = m_y1 + sin((180-m_angle) * RAD) * hypo;
    }
    else if (m_angle >= 180 && m_angle <= 270)
    {
        m_x2 = m_x1 - cos((m_angle-180) * RAD) * hypo;
        m_y2 = m_y1 - sin((m_angle-180) * RAD) * hypo;
    }
    else
    {
        m_x2 = m_x1 + cos((360-m_angle) * RAD) * hypo;
        m_y2 = m_y1 - sin((360-m_angle) * RAD) * hypo;
    }
}

void Line::move(int x, int y)
{
    m_x1 = x;
    m_y1 = y;
    calculateEndPoints();
    //std::cout << m_x2 << " " << m_y2 << std::endl;
    m_rect.setPosition(sf::Vector2f(m_x1, m_y1));
}

void Line::init()
{
    m_rect.setOrigin(0, m_thickness / 2);
    m_rect.setPosition(sf::Vector2f(m_x1, m_y1));
    m_rect.rotate(m_angle);
}

void Line::draw(sf::RenderWindow &window) const
{
    window.draw(m_rect);
}

Line::~Line()
{
}