#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"

#define _USE_MATH_DEFINES

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#endif 

class Line
{
public:
    Line(int x1, int y1, int x2, int y2, int thickness);
    Line(int x1, int y1, float angle, int thickness);
    Line(Point& p1, Point& p2, int thickness);
    virtual void Draw(sf::RenderWindow &window) const;
    void Move(Point& destination);
    void SetLength(float len);
    void SetEndPoint(Point& point);
    bool Contains(const Point& point) const;
    void UpdateAngle();
    virtual ~Line();
    
private:
    void InitRectangle(sf::Color color);
    void CalculateEndPoint();
private:
    sf::RectangleShape m_rect;
protected:
    int m_thickness;
    float m_angle;
public:
    Point firstPoint;
    Point secondPoint;
};



