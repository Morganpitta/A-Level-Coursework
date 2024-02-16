#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "Entity/bullet.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,900), "Mazewars" );

    if ( !loadEntityAssets() || !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    BattleZone game;

    while (window.isOpen() && !game.getPlayer()->isDead())
    {
        game.update( window );

        window.clear( sf::Color::Black );

        game.render( window );

        sf::Text health( std::to_string( game.getPlayer()->getHealth() ), defaultFont );
        window.draw( health );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}