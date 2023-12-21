#include <SFML/Window.hpp>
#include "time.h++"
#include "mazeWars.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,800), "Mazewars" );

    if ( !loadEntityAssets() )
        return 1;

    FpsLimiter fps( 60 );

    MazeWars game( { 10, 10 } );

    game.addEntity( new Entity() );

    while (window.isOpen())
    {
        game.update( window );

        window.clear( sf::Color::Black );

        game.render( window );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}