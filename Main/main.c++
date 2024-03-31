#include "MazeWars\include\mainLoop.h++"
#include "BattleZone\include\mainLoop.h++"


int main()
{
    sf::RenderWindow window( {1600,900}, "3D Rendering" );
    
    if (!loadBaseAssets())
       return 1;

    sf::Text mazeWarTitle = 
        getTextCentered(
            "MAZE WAR", gameFont, 60,
            {800, 200},
            sf::Color::Green
        );
    sf::Text battleZoneTitle = 
        getTextCentered(
            "BATTLEZONE", gameFont, 60,
            {800,600},
            sf::Color::Green
        );

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
                    BattleZone::handleResize(window, (float) event.size.width, (float) event.size.height);
                    break;

                case sf::Event::MouseButtonPressed:
                    if ( mazeWarTitle.getGlobalBounds().contains( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y ) )
                        MazeWars::mainLoop( window );
                    if ( battleZoneTitle.getGlobalBounds().contains( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y ) )
                        MazeWars::mainLoop( window );
                    break;

                default:
                    break;
            }
        }

        window.clear( sf::Color::Black );

        window.draw( mazeWarTitle );
        window.draw( battleZoneTitle );

        window.display();
    }

    BattleZone::mainLoop( window );

    return 0;
}