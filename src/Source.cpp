#include "Source.h"

Source::Source(int x, int y, int beamCount) : m_point(x, y), m_beamCount(beamCount)
{
    m_beams = std::vector<Beam>();
    m_beams.reserve(m_beamCount);
    for (int i = 0; i < m_beamCount; ++i)
    {
        m_beams.emplace_back(x, y, (360.f / m_beamCount) * i);
    }
}

void Source::Move(Point destination)
{
    for (int i = 0; i < m_beamCount; ++i)
    {
        m_beams.at(i).Move(destination);
    }
}

void Source::Draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < m_beamCount; ++i)
    {
        m_beams.at(i).Draw(window);
    }
}

void Source::checkWalls(const std::vector<Wall> &walls)
{  
    for(auto& beam : m_beams)
    {
        beam.checkCollision(walls);
    } 
}

Source::~Source()
{
}