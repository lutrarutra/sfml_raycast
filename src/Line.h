#pragma once
#include "proj_data.h"
#include "Point.h"

#define _USE_MATH_DEFINES
#define INF INT32_MAX

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
    void SetColor( sf::Color& color );
    bool Contains(const Point& point) const;

    Point FindIntersection( const Line& l2 ) const;

    sf::Vector2f FindKBCoeffs() const;

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
protected:
    Point firstPoint;
    Point secondPoint;
};



