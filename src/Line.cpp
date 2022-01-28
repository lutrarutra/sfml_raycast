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
    if ( ( point.x >= firstPoint.x  && point.x <= secondPoint.x ||
           point.x >= secondPoint.x && point.x <= firstPoint.x ) &&
         ( point.y >= firstPoint.y  && point.y <= secondPoint.y  ||
           point.y >  secondPoint.y && point.y <  firstPoint.y ) )
    {
        if ( secondPoint.y == firstPoint.y )
        {
            if (point.y == secondPoint.y)
                return true;
            return false;
        }
        if ( secondPoint.x == firstPoint.x )
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

Point Line::FindIntersection( const Line& l2 ) const
{
    Point intercept( INF, INF );

    sf::Vector2f kbThis = FindKBCoeffs();
    float k1 = kbThis.x;
    float b1 = kbThis.y;

    sf::Vector2f kbOther = l2.FindKBCoeffs();
    float k2 = kbOther.x;
    float b2 = kbOther.y;

    // point of interception is found as the solution of the system
    // {y = k1 * x + b1
    // {y = k2 * x + b2
    // 
    // or k1 * x + b1 = k2 * x + b2
    // continue: k1 * x - k2 * x = b2 - b1
    // x = (b2 - b1) / (k1 - k2); y = k1 * (b2 - b1) / (k1 - k2) - b1
    // If some of the lines are vertical, things get more complicated in some sense.
    // if this line is vertical then x coordinate of interception is obviously the x coordinate of this line
    // the y coordinate then is found from y = k2 * x1 + b2,  where x1 - x coordinate of this line.
    // 
    // If lines are parallel then there's no or infinite number of interceptions,
    // which means both of these cases are irrelevant 

    if ( k1 == k2 )
        return intercept;

    if ( k1 != INF )
    {
        if ( k2 == INF )
        {
            intercept.x = l2.firstPoint.x;
            intercept.y = k1 * intercept.x + b1;
        }
        else
        {
            intercept.x = (b2 - b1) / (k1 - k2);
            intercept.y = k1 * intercept.x + b1;
        }       
    }
    else
    {
        intercept.x = firstPoint.x;
        intercept.y = k2 * intercept.x + b2;
    }

    return intercept;
}

sf::Vector2f Line::FindKBCoeffs() const
{
    float k = 0;
    float b = 0;
    if ( (secondPoint.x - firstPoint.x) == 0 ) // if the line is vertical set k to be inf
    {
        k = INF;
        b = -INF;
    }
    else
    {
        // line equation from points is (y-y1)/(y1-y2) = (x-x1)/(x1-x2) 
        // or, which is basically the same (y-y2)/(y2-y1) = (x-x2)/(x2-x1). 
        // That means order of points is irrelevant. You can check it on desmos.com for example.
        // https://www.desmos.com/calculator/woj2nfulgf
        // Choose the first one: (y-y1)/(y1-y2) = (x-x1)/(x1-x2) 
        // therefore y = (x-x1)(y1-y2)/(x1-x2) + y1
        // expand: y = x(y1-y2)/(x1-x2) - x1(y1-y2)/(x1-x2) + y1
        // equation is y = kx+b therefore k = (y1-y2)/(x1-x2); b = y1 - x1(y1-y2)/(x1-x2).

        k = (secondPoint.y - firstPoint.y) / (secondPoint.x - firstPoint.x);
        b = firstPoint.y - k * firstPoint.x;
    }
    return sf::Vector2f(k, b);
}


Line::~Line()
{
}