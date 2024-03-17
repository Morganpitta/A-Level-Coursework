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

    MazeWars game( {targetWidth,targetHeight}, { 10, 10 } );

    while (window.isOpen() && !game.getPlayer()->isDead())
    {
        handleInputs( window, game );
        game.update( window );

        window.clear( sf::Color::Black );

        game.render( window );

        fps.draw(window, {0,0}, 30, sf::Color::White);

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}