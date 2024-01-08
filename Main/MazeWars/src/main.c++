#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "random.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    if ( !loadEntityAssets() || !loadBaseAssets() )
        return 1;

    FpsLimiter fps( 60 );

    setRandomNumberSeed( timeNow().time_since_epoch().count() );

    MazeWars game( { 50, 50 } );

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