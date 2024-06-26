#include "mainLoop.h++"

namespace BattleZone
{
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

    void handleInputs( sf::RenderWindow &window, BattleZoneGame &game )
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

    void mainLoop( sf::RenderWindow &window )
    {
        handleResize( window, window.getSize().x, window.getSize().y );
        window.setTitle( "BattleZone" );
        window.setKeyRepeatEnabled(false);

        if ( !loadEntityAssets() || !loadAssets() )
            return;

        FpsLimiter fps( 60 );

        BattleZoneGame game( {1600,900} );
        
        while (window.isOpen() && !game.getPlayer()->isDead())
        {
            handleInputs( window, game );
            game.update( window );

            window.clear( sf::Color::Black );

            game.render( window );

            window.display();
            fps.restartAndSleep();
        }

        BattleZone::deathScreenLoop( window );
    }

    void deathScreenLoop( sf::RenderWindow &window )
    {
        bool keyPressed = false;
        while (window.isOpen() && !keyPressed)
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

                    case sf::Event::KeyPressed:
                        keyPressed = true;
                        break;
                    
                    default:
                        break;
                }
            }

            window.clear( sf::Color::Black );
            drawTextCentered(
                window,
                "GAME OVER", gameFont, 60,
                {targetWidth/2.f, targetHeight/2.f - 60},
                sf::Color::Green
            );
            drawTextCentered(
                window,
                "PRESS ANY KEY TO CONTINUE", gameFont, 30,
                {targetWidth/2.f, targetHeight/2.f + 60},
                sf::Color::Green
            );
            window.display();
        }
    }
}