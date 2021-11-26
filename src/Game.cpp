#include "Game.h"

Game::Game()
{
    m_settings;
    m_settings.antialiasingLevel = 8;
    m_window = std::make_unique<sf::RenderWindow>( sf::VideoMode( WINDOW_WIDTH, WINDOW_HEIGHT ),
                                                   "raycast", sf::Style::Close, m_settings );

    ImGui::SFML::Init( *m_window.get() );
}

Game::~Game()
{
    ImGui::SFML::Shutdown();
}

void Game::Run()
{
    sf::Clock deltaClock;

    sf::Color bgColor;
    float bgColorArr[3] = { 0.f, 0.f, 0.f };
    sf::Color beamColor;
    float beamColorArr[3] = { 0.f, 0.f, 0.f };

    char windowTitle[255] = "raycast";
    m_window->setTitle( windowTitle );

    while ( m_window->isOpen() )
    {
        sf::Event Event;
        while ( m_window->pollEvent( Event ) )
        {
            ImGui::SFML::ProcessEvent( Event );
            if ( Event.type == sf::Event::Closed )
            {
                m_window->close();
            }
            if ( Event.type == sf::Event::MouseMoved )
            {
                m_source.Move( { (float)sf::Mouse::getPosition( *m_window.get() ).x,
                          (float)sf::Mouse::getPosition( *m_window.get() ).y } );
            }
        }

        ImGui::SFML::Update( *m_window.get(), deltaClock.restart());

        ImGui::Begin( "Background color edit" ); // создаём окно

         // Инструмент выбора цвета
        if ( ImGui::ColorEdit3( "Background color", bgColorArr ) )
        {
            // код вызывается при изменении значения, поэтому всё
            // обновляется автоматически
            bgColor.r = static_cast<sf::Uint8>(bgColorArr[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(bgColorArr[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(bgColorArr[2] * 255.f);
        }
        // Инструмент выбора цвета
        if ( ImGui::ColorEdit3( "Beam color", beamColorArr ) )
        {
            // код вызывается при изменении значения, поэтому всё
            // обновляется автоматически
            beamColor.r = static_cast<sf::Uint8>(beamColorArr[0] * 255.f);
            beamColor.g = static_cast<sf::Uint8>(beamColorArr[1] * 255.f);
            beamColor.b = static_cast<sf::Uint8>(beamColorArr[2] * 255.f);
            beamColor.a = 50;
            m_source.SetBeamColor( beamColor );
        }

        int sliderValue = 0;
        if ( ImGui::SliderInt( "Beam count", &sliderValue, 0, 1080 ) )
        {
            m_source.SetBeamCount( sliderValue );
        }

        ImGui::End(); // end window

        m_window->clear( bgColor ); // заполняем окно заданным цветом
        ImGui::SFML::Render( *m_window.get() );

        m_source.checkWalls( m_walls );
        Redraw();
    }
}

void Game::Redraw()
{
    //m_window->clear( sf::Color::Black );
    m_source.Draw( *m_window.get() );

    for ( int i = 0; i < m_walls.size(); ++i )
    {
        m_walls[i].Draw( *m_window.get() );
    }

    m_window->display();
}

void Game::InitWindow()
{

}

void Game::AddWall( Point& start, Point& end )
{
    m_walls.emplace_back( start, end );
}

void Game::AddWall( Point&& start, Point&& end )
{
    m_walls.emplace_back( start, end );
}
