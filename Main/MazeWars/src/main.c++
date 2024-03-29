#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "random.h++"

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

void handleInputs( sf::RenderWindow &window, MazeWars &game )
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
    sf::RenderWindow window( sf::VideoMode(900,900), "Mazewars" );

    if ( !loadEntityAssets() || !loadBaseAssets() )
        return 1;

    FpsLimiter fps( 60 );

    setRandomNumberSeed( timeNow().time_since_epoch().count() );

    MazeWars game( sf::Vector2u(targetWidth,targetHeight), { 50, 50 } );

    while (window.isOpen() && !game.getPlayer()->isDead())
    {
        handleInputs( window, game );
        game.update();

        window.clear( sf::Color::Black );

        game.render( window );

        // fps.draw(window, {0,0}, 30, sf::Color::White);

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