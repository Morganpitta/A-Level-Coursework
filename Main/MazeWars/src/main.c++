#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "random.h++"

void handleResize( 
    sf::RenderWindow &window,
    float windowWidth, 
    float windowHeight
)
{
    float ratio = float(windowWidth)/windowHeight;
    float targetRatio = 9.f/9.f;
    
    if ( ratio > targetRatio )
    {
        int offset = 900.f*(ratio/targetRatio-1);
        sf::FloatRect visibleArea(-offset/2, 0, 900+offset, 900);
        window.setView(sf::View(visibleArea));
    }
    else if ( ratio < targetRatio )
    {
        int offset = 900.f*(targetRatio/ratio-1);
        sf::FloatRect visibleArea(0, -offset/2, 900, 900+offset);
        window.setView(sf::View(visibleArea));
    }
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

    MazeWars game( {900,900}, { 50, 50 } );

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