#include <SFML/Graphics.hpp>
#include "time.h++"
#include "renderer.h++"
#include "mazeGenerator.h++"

const float targetWidth = 900;
const float targetHeight = 900;

void handleResize( 
    sf::RenderWindow &window,
    float windowWidth, 
    float windowHeight
)
{
    float ratio = windowWidth/windowHeight;
    float targetRatio = targetWidth/targetHeight;
    
    if ( ratio > targetRatio )
    {
        float offset = targetWidth*(ratio/targetRatio-1);
        sf::FloatRect visibleArea(-offset/2, 0, targetWidth+offset, targetHeight);
        window.setView(sf::View(visibleArea));
    }
    else if ( ratio < targetRatio )
    {
        float offset = targetHeight*(targetRatio/ratio-1);
        sf::FloatRect visibleArea(0, -offset/2, targetWidth, targetHeight+offset);
        window.setView(sf::View(visibleArea));
    }
}

void handleInputs( sf::RenderWindow &window )
{
    sf::Event event;
    // For each event
    while ( window.pollEvent(event) )
    {
        // Handle appropriately
        switch ( event.type )
        {
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::Resized:
                handleResize(window, (float) event.size.width, (float) event.size.height);
                break;
        }
    }
}

int main()
{
    // Create window instance
    sf::RenderWindow window( sf::VideoMode(1600,900), "Mazewars" );

    // Load base assets like a default font and etc
    if ( !loadBaseAssets() )
        return 1; // If unable, end the program and return one to represent an error

    
    FpsLimiter fps( 60 );

    MazeGrid mazeGrid( { 10, 10 } );

    generateMazeDepthFirst( mazeGrid, 0 );

    Renderer renderer( { targetWidth, targetHeight } );

    renderer.getCamera().setPosition( {5,5} );

    while ( window.isOpen() )
    {
        handleInputs( window );

        window.clear( sf::Color::Black );

        // Things will be drawn here
        renderer.render( window, mazeGrid );

        // Display the frames per second in the top left
        fps.draw(window, {0,0}, 30, sf::Color::White);

        window.display();
        fps.restartAndSleep();
    }

    return 0; // Program ran successfully! return 0 to represent no errors
}