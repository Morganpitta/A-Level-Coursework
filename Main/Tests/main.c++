#include "time.h++"
#include "battleZone.h++"
#include "entity.h++"

const float targetWidth = 1600;
const float targetHeight = 900;

void handleResize( 
    sf::RenderWindow &window,
    float windowWidth, 
    float windowHeight
);

void handleInputs( sf::RenderWindow &window );

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,900), "BattleZone" );
    window.setKeyRepeatEnabled(false);

    if ( !loadEntityAssets() || !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    BattleZone game( {1600,900} );
    
    while (window.isOpen() && !game.getPlayer()->isDead())
    {
        handleInputs( window );
        game.update( window );

        window.clear( sf::Color::Black );

        game.render( window );

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}