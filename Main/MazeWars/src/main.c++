#include "mainLoop.h++"

using namespace MazeWars;

int main()
{
    sf::RenderWindow window( sf::VideoMode(900,900), "Mazewars" );
    
    mainLoop( window );

    return 0;
}