#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"
#include "Entity/tank.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,800), "Mazewars" );

    if ( !loadEntityAssets() || !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    BattleZone game;

    game.addEntity( new Tank() );

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