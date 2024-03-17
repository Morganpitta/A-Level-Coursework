#include "renderer.h++"
#include "Entity/entity.h++"

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