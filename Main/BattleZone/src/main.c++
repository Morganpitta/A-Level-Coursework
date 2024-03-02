#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "Entity/bullet.h++"

void handleResize( 
    sf::RenderWindow &window,
    float windowWidth, 
    float windowHeight
)
{
    float ratio = float(windowWidth)/windowHeight;
    float targetRatio = 16.f/9.f;
    
    if ( ratio > targetRatio )
    {
        float offset = 1600.f*(ratio/targetRatio-1);
        sf::FloatRect visibleArea(-offset/2, 0, 1600+offset, 900);
        window.setView(sf::View(visibleArea));
    }
    else if ( ratio < targetRatio )
    {
        float offset = 900.f*(targetRatio/ratio-1);
        sf::FloatRect visibleArea(0, -offset/2, 1600, 900+offset);
        window.setView(sf::View(visibleArea));
    }
}

void handleInputs( sf::RenderWindow &window, BattleZone &game )
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
            
            default:
                game.handleInputs(event);
                break;
        }
    }
}

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,900), "Mazewars" );

    if ( !loadEntityAssets() || !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    BattleZone game;

    while (window.isOpen() && !game.getPlayer()->isDead())
    {
        handleInputs( window, game );
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