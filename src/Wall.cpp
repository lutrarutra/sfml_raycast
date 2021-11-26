#include <math.h>

#include "Wall.h"

Wall::Wall(int x1, int y1, int x2, int y2) : Line(x1, y1, x2, y2, m_thickness ) {}

Wall::Wall( Point& p1, Point& p2 ) : Line( p1, p2, m_thickness ) { }

float Wall::GetAngle() const
{
    return m_angle; 
}

Wall::~Wall()
{
    
}

