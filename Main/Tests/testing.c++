#include "time.h++"
#include "Render/renderer.h++"

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
    sf::RenderWindow window( sf::VideoMode(targetWidth,targetHeight), "BattleZone" );

    if ( !loadAssets() )
        return 1;

    FpsLimiter fps( 60 );

    Renderer renderer( {targetWidth,targetHeight} );

    Model3D model("BattleZone/pyramid.obj");

    while (window.isOpen())
    {
        handleInputs( window );

        window.clear( sf::Color::Black );
        renderer.clear();

        renderer.draw(&model);

        renderer.display(window);
        window.display();
        fps.restartAndSleep();
    }

    return 0;
}