#include <SFML/Window.hpp>
#include "direction.h++"
#include "time.h++"
#include "mazeGrid.h++"
#include "mazeGenerator.h++"
#include "renderer.h++"

void directionTestFunction()
{
    sf::Vector2i position = {0,0};

    for ( int index = North; index < NumberOfDirections; index++ )
    {
        std::cout << format( "(%d, %d)\n", position.x, position.y );
        position = transposePosition( position, Direction( index ) );
    }

    std::cout << format( "(%d, %d)\n", position.x, position.y );

    position = {1,0};

    for ( int index = North; index < NumberOfDirections; index++ )
    {
        std::cout << format( "(%d, %d)\n", position.x, position.y );
        position = sf::Vector2i( rotatePosition( sf::Vector2f( position ), Direction( index ) ) );
    }

    std::cout << format( "(%d, %d)\n", position.x, position.y );
}

void mazeGridTestFunction()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    MazeGrid mazeGrid( { 10, 10 } );

    generateMazeDepthFirst( window, mazeGrid, 1 );

    /*
    mazeGrid.set( 
        { 1, 1, 1, 
          1, 0, 0,
          1, 1, 0,
          1, 1, 1 },
        { 1, 0, 1, 1,
          1, 0, 0, 1,
          1, 0, 0, 1 } 
    );
    */
    
    /*
    mazeGrid.set( 
        { 1, 1, 1, 1, 
          1, 0, 0, 0,
          1, 1, 0, 0,
          1, 1, 1, 1 }, 
          
        { 1, 0, 0, 1, 1,
          1, 0, 1, 1, 1,
          1, 0, 0, 0, 1 } 
    );
    */

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
            }
        }

        /*
        sf::Vector2i mousePosition = { (int) floor( ( sf::Mouse::getPosition( window ).x - 50 ) / ( 700.f / mazeGrid.getDimensions().x ) ), (int) floor( ( sf::Mouse::getPosition( window ).y - 50 ) / ( 700.f / mazeGrid.getDimensions().y ) ) };
        
        if ( mazeGrid.inBounds( mousePosition ) )
            std::cout << format( "(%d,%d) -> %d, %d, %d, %d\n", mousePosition.x, mousePosition.y, mazeGrid.getCell(mousePosition,North), mazeGrid.getCell(mousePosition,East), mazeGrid.getCell(mousePosition,South), mazeGrid.getCell(mousePosition,West) );
        */

        window.clear( sf::Color::Black );

        drawMaze( window, mazeGrid, {50,50}, {750,750} );

        window.display();
    }
}

void rendererTestFunction()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    MazeGrid mazeGrid( { 10, 10 } );

    generateMazeDepthFirst( window, mazeGrid, 0 );

    Renderer renderer;

    renderer.getCamera().setPosition( {5,5} );

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
                    if ( event.key.code == sf::Keyboard::D )
                        renderer.getCamera().turnRight();
                    if ( event.key.code == sf::Keyboard::W )
                        renderer.getCamera().moveForward();
                    break;
            }
        }

        window.clear( sf::Color::Black );

        renderer.render( window, mazeGrid );

        window.display();
    }
}

int main()
{
    rendererTestFunction();
    return 0;
}