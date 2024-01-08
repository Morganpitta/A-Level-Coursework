#include "SFML/Graphics.hpp"
#include "time.h++"
#include "render/camera.h++"
#include "render/model3D.h++"

int main()
{
    sf::RenderWindow window( sf::VideoMode(800,800), "Mazewars" );

    FpsLimiter fps( 60 );

    while (window.isOpen())
    {
        window.clear( sf::Color::Black );

        fps.draw(window, {0,0}, 30, sf::Color::White);

        window.display();
        fps.restartAndSleep();
    }

    return 0;
}