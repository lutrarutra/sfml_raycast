#include "Game.h"

int main()
{
    Game game;

    game.AddWall( { 300, 50 }, { 800, 600 } );
    game.AddWall( { 700, 500 }, { 1200, 850 } );
    game.AddWall( { 1000, 50 }, { 800, 120 } );
    game.AddWall( { 600, 700 }, { 300, 550 } );
    //ImGui::Button
    game.Run();



}