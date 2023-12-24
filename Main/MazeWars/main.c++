#include <SFML/Window.hpp>
#include "time.h++"
#include "mazeWars.h++"
#include "Entity\enemy.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,800), "Mazewars" );

    if ( !loadEntityAssets() || !loadBaseAssets() )
        return 1;

    FpsLimiter fps( 60 );

    MazeWars game( { 500, 500 } );

    game.addEntity( new Enemy() );

    game.getPlayer()->setPosition({499,499});

    while (window.isOpen())
    {
        game.update( window );

        window.clear( sf::Color::Black );

        game.render( window );

        fps.draw(window, {0,0}, 30, sf::Color::White);

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}