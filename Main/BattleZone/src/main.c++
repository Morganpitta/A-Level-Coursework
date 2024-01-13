#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "Entity/bullet.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,800), "Mazewars" );

    if ( !loadEntityAssets() || !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    BattleZone game;

    game.addEntity( new Tank( {-2,2} ) );

    game.addEntity( new Obstacle( {2, 2} ) );

    while (window.isOpen() && !game.getPlayer()->isDead())
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