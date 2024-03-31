#include "SFML/Graphics.hpp"
#include "time.h++"
#include "battleZone.h++"
#include "Entity/entity.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "Entity/bullet.h++"

namespace BattleZone
{
    extern const float targetWidth;
    extern const float targetHeight;

    void handleResize( 
        sf::RenderWindow &window,
        float windowWidth, 
        float windowHeight
    );

    void handleInputs( sf::RenderWindow &window, BattleZoneGame &game );
    
    void mainLoop( sf::RenderWindow &window );
    void deathScreenLoop( sf::RenderWindow &window );
}