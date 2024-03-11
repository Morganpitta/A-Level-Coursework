#include <SFML/Graphics.hpp>
#include "time.h++"

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
        }
    }
}

    while ( window.isOpen() )
    {
        handleInputs( window );

        window.clear( sf::Color::Black );
