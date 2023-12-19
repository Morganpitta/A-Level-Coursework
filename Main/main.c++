#include <SFML/Window.hpp>
#include "time.h++"
#include "mazeWars.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,800), "Mazewars" );

    FpsLimiter fps( 60 );

    MazeWars game( { 10, 10 } );

    game.addEntity( new Entity() );

    while (window.isOpen())
    {
        game.update();
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if ( event.key.code == sf::Keyboard::A )
                        game.getCamera().turnLeft();
                    if ( event.key.code == sf::Keyboard::D )
                        game.getCamera().turnRight();
                    if ( event.key.code == sf::Keyboard::W &&
                         !game.getMaze().getCell( 
                            game.getCamera().getPosition(), 
                            game.getCamera().getDirection() 
                         )
                        )
                        game.getCamera().moveForward();
                    break;
            }
        }

        window.clear( sf::Color::Black );

        game.render( window );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}