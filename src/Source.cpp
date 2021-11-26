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

Source::Source() : Source( 0, 0, DEFAULT_BEAM_COUNT ) { }

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

void Source::SetBeamCount( int count )
{
    m_beamCount = count;
    m_beams.clear();
    m_beams.reserve( m_beamCount );
    for ( int i = 0; i < m_beamCount; ++i )
    {
        m_beams.emplace_back( m_point.x, m_point.y, (360.f / m_beamCount) * i );
    }
}

void Source::SetBeamColor( sf::Color& color )
{
    for ( auto& beam : m_beams )
    {
        beam.SetColor( color );
    }
}

Source::~Source()
{
}