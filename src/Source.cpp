#include "Source.h"

Source::Source(int x, int y, int beamCount) : m_x(x), m_y(y), m_beamCount(beamCount)
{
    m_beams = std::vector<Beam>();
    m_beams.reserve(m_beamCount);
    for (int i = 0; i < m_beamCount; ++i)
    {
        m_beams.emplace_back(x, y, (360 / m_beamCount) * i);
    }
}

void Source::move(int x, int y)
{
    for (int i = 0; i < m_beamCount; ++i)
    {
        m_beams.at(i).move(x, y);
    }
}

void Source::draw(sf::RenderWindow &window) const
{
    for (int i = 0; i < m_beamCount; ++i)
    {
        m_beams.at(i).draw(window);
    }
}

void Source::checkWalls(const std::vector<Wall> &walls)
{
    for(const auto& wall : walls)
    {
        for(auto& beam : m_beams)
        {
            beam.checkCollision(wall);
        }
    }
}

Source::~Source()
{
}