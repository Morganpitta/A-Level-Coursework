#include "SFML/Graphics.hpp"
#include "time.h++"
#include "render/camera.h++"
#include "render/model3D.h++"
#include "render/renderer.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    FpsLimiter fps( 60 );

    Model3D model( "BattleZone/tank.obj" );

    Renderer renderer;

    renderer.getCamera().setPosition( {0,1,-2} );

    while (window.isOpen())
    {
        window.clear( sf::Color::Black );

        renderer.clear();
        
        renderer.draw( window, model );

        renderer.display( window );

        fps.draw(window, {0,0}, 30, sf::Color::White);

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}