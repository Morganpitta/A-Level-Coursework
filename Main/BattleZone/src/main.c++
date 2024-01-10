#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    FpsLimiter fps( 60 );

    Model3D model( "BattleZone/tank.obj" );

    BattleZone game;

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