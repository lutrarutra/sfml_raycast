#include "Line.h"

#define RAD M_PI / 180.0


Line::Line(int x1, int y1, int x2, int y2, int thickness) : 
    firstPoint(x1, y1),
    secondPoint(x2, y2),
    m_thickness(thickness),
    m_rect(sf::Vector2f(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)), thickness))
{
    UpdateAngle();
    InitRectangle(sf::Color(255, 255, 255, 250));
}

Line::Line(int x1, int y1, float angle, int thickness)
    : firstPoint(x1, y1), m_angle(angle), m_thickness(thickness),
      m_rect(sf::Vector2f(sqrt(pow(WINDOW_WIDTH, 2) + pow(WINDOW_HEIGHT, 2)), thickness))
{
    InitRectangle(sf::Color(255, 255, 255, 50));
    CalculateEndPoint();
}

Line::Line(Point& p1, Point& p2, int thickness)
    : firstPoint(p1), secondPoint(p2),
    m_thickness(thickness),
    m_rect( sf::Vector2f( p1.DistanceTo(p2), thickness ) )
{
    UpdateAngle();
    InitRectangle(sf::Color::White);
}

void Line::Move(Point& destination)
{
    secondPoint += destination - firstPoint;
    firstPoint = destination;
    m_rect.setPosition(firstPoint);
}

void Line::InitRectangle(sf::Color color)
{
    m_rect.setFillColor(color);
    m_rect.setOrigin(0, m_thickness / 2);
    m_rect.setPosition(firstPoint.x, firstPoint.y);
    m_rect.setRotation(m_angle);
}

void Line::Draw(sf::RenderWindow& window) const
{
    window.draw(m_rect);
}

void Line::UpdateAngle()
{
    m_angle = atan((secondPoint.y - firstPoint.y) / (secondPoint.x - firstPoint.x)) * 180 / M_PI + 180 * (secondPoint.x < firstPoint.x); // adding 180 degrees if the second point is in II or III quarters
    m_rect.setRotation(m_angle);
}

void Line::SetLength(float length)
{
    secondPoint.x = firstPoint.x + cos(m_angle * RAD) * length;
    secondPoint.y = firstPoint.y + sin(m_angle * RAD) * length;
    m_rect.setSize(sf::Vector2f(length, m_thickness));
}

void Line::SetEndPoint(Point& point)
{
    secondPoint = point;
    UpdateAngle();
    SetLength(Point::DistanceBetween(firstPoint, secondPoint));
}

void Line::SetColor( sf::Color& color )
{
    m_rect.setFillColor( color );
}

void Line::CalculateEndPoint()
{
    float length = sqrt(pow(m_rect.getSize().x, 2) + pow(m_rect.getSize().y, 2));
    secondPoint.x = firstPoint.x + cos(m_angle * RAD) * length;
    secondPoint.y = firstPoint.y + sin(m_angle * RAD) * length;
}

bool Line::Contains(const Point& point) const
{
    static const float epsilon = 0.01;
    if (((point.x >= firstPoint.x && point.x <= secondPoint.x) || (point.x > secondPoint.x && point.x < firstPoint.x)) &&
          point.y >= firstPoint.y && point.y <= secondPoint.y  ||  point.y > secondPoint.y && point.y < firstPoint.y)
    {
        if (secondPoint.y - firstPoint.y == 0)
        {
            if (point.y == secondPoint.y)
                return true;
            return false;
        }
        if (secondPoint.x - firstPoint.x == 0)
        {
            if (point.x == secondPoint.x)
                return true;
            return false;
        }
        if(abs( (point.y - firstPoint.y) / (secondPoint.y - firstPoint.y) - 
                (point.x - firstPoint.x) / (secondPoint.x - firstPoint.x) ) < epsilon)
            return true;
    }
    return false;
}


Line::~Line()
{
}