#include "MazeWars/include/mainLoop.h++"
#include "BattleZone/include/mainLoop.h++"

sf::Texture instructionsTexture;

int main()
{
    sf::RenderWindow window( {1600,900}, "3D Rendering" );
    
    if (!loadBaseAssets())
       return 1;

    if ( !instructionsTexture.loadFromFile("instructions.png") )
        return 1;

    sf::Text instructions = 
        getTextCentered(
            "INSTRUCTIONS", gameFont, 60,
            {800, 250},
            sf::Color::Green
        );

    sf::Text mazeWarTitle = 
        getTextCentered(
            "MAZE WAR", gameFont, 60,
            {400, 550},
            sf::Color::Green
        );

    sf::Text battleZoneTitle = 
        getTextCentered(
            "BATTLEZONE", gameFont, 60,
            {1200,550},
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
                    BattleZone::handleResize( window, (float) event.size.width, (float) event.size.height );
                    break;

                case sf::Event::MouseButtonPressed:
                    if ( mazeWarTitle.getGlobalBounds().contains( window.mapPixelToCoords( sf::Mouse::getPosition(window) ) ) )
                    {
                        MazeWars::mainLoop( window );
                        BattleZone::handleResize( window, window.getSize().x, window.getSize().y );
                    }
                    if ( battleZoneTitle.getGlobalBounds().contains( window.mapPixelToCoords( sf::Mouse::getPosition(window) ) ) )
                    {
                        BattleZone::mainLoop( window );
                        BattleZone::handleResize( window, window.getSize().x, window.getSize().y );
                    }
                    if ( instructions.getGlobalBounds().contains( window.mapPixelToCoords( sf::Mouse::getPosition(window) ) ) )
                    {
                        sf::RectangleShape instructionsRect;
                        instructionsRect.setTexture( &instructionsTexture );
                        instructionsRect.setSize( {1600,900} );

                        bool end = false;
                        while ( !end )
                        {
                            while ( window.pollEvent(event) )
                            {
                                if ( event.type == sf::Event::Closed  )
                                {
                                    end = true;
                                    window.close();
                                }
                                    
                                if ( event.type == sf::Event::KeyPressed )
                                {
                                    end = true;
                                }
                            }

                            window.clear( sf::Color::Black );

                            window.draw( instructionsRect );

                            window.display();
                        }
                        break;
                    }
                    break;

                default:
                    break;
            }
        }

        window.clear( sf::Color::Black );

        window.draw( mazeWarTitle );
        window.draw( battleZoneTitle );
        window.draw( instructions );

        window.display();
    }

    return 0;
}