#include <SFML/Window.hpp>
#include "time.h++"
#include "mazeGrid.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,800), "Mazewars" );
    std::cout << "started\n";

    FpsLimiter fps( 60 );

    MazeGrid mazeGrid( { 1000, 1000 } );
    
    while (window.isOpen())
    {
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                
                    break;
            }
        }

        window.clear( sf::Color::Black );

        drawMaze( window, mazeGrid, {10,10}, {790,790} );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}