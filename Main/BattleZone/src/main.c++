#include "mainLoop.h++"

using namespace BattleZone;

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,900), "BattleZone" );
    
    mainLoop( window );

    return 0;
}