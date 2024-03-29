#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "Entity/bullet.h++"

const float targetWidth = 1600;
const float targetHeight = 900;

void handleResize( 
    sf::RenderWindow &window,
    float windowWidth, 
    float windowHeight
)
{
    float ratio = windowWidth/windowHeight;
    float targetRatio = targetWidth/targetHeight;
    sf::FloatRect visibleArea(0, 0, targetWidth, targetHeight);
    
    if ( ratio > targetRatio )
    {
        float offset = targetWidth*(ratio/targetRatio-1);
        visibleArea = sf::FloatRect(-offset/2, 0, targetWidth+offset, targetHeight);
    }
    else if ( ratio < targetRatio )
    {
        float offset = targetHeight*(targetRatio/ratio-1);
        visibleArea = sf::FloatRect(0, -offset/2, targetWidth, targetHeight+offset);
    }
    window.setView(sf::View(visibleArea));
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
                game.handleInput(event);
                break;
        }
    }
}

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,900), "BattleZone" );

    if ( !loadEntityAssets() || !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    BattleZone game( {1600,900} );
    
    while (window.isOpen() && !game.getPlayer()->isDead())
    {
        handleInputs( window, game );
        game.update( window );

        window.clear( sf::Color::Black );

        game.render( window );

        window.display();
        fps.restartAndSleep();
    }

    window.clear( sf::Color::Black );
    sf::Text text("GAME OVER",gameFont,60);
    text.setOrigin( {text.getGlobalBounds().width/2.f,text.getGlobalBounds().height/2.f} );
    text.setPosition( {targetWidth/2.f, targetHeight/2.f} );
    text.setFillColor(sf::Color::Green);
    window.draw( text );
    window.display();

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
                
                case sf::Event::Resized:
                    handleResize(window, (float) event.size.width, (float) event.size.height);
                    break;
            }
        }
    }

    return 0;
}