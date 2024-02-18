#include <SFML/Graphics.hpp>
#include "time.h++"

void handleInputs( sf::RenderWindow &window )
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
                float ratio = float(event.size.width)/event.size.height;
                std::cout << "width: " << event.size.width << " height: " << event.size.height << " ratio: " << ratio << std::endl;
                
                if ( ratio > 16.f/9.f )
                {
                    sf::FloatRect visibleArea(0, 0, 1600.f*(float(event.size.width)/event.size.height), 900);
                    window.setView(sf::View(visibleArea));
                }
                else if ( ratio < 16.f/9.f )
                {
                    sf::FloatRect visibleArea(0, 0, 1600, 900.f*(float(event.size.width)/1600));
                    window.setView(sf::View(visibleArea));
                }
                break;
        }
    }
}

int main()
{
    // Create window instance
    sf::RenderWindow window( sf::VideoMode(1600,900), "Mazewars" );

    // Load base assets like a default font and etc
    if ( !loadBaseAssets() )
        return 1; // If unable, end the program and return one to represent an error

    sf::Texture texture;

    if ( !texture.loadFromFile("MazeWars/triangle.png") )
        return 1;
    
    FpsLimiter fps( 60 );

    while ( window.isOpen() )
    {
        handleInputs( window );

        window.clear( sf::Color::Black );

        // Things will be drawn here

        sf::RectangleShape rect({1600,900});
        rect.setTexture(&texture);
        window.draw(rect);

        // Display the frames per second in the top left
        fps.draw(window, {0,0}, 30, sf::Color::White);

        window.display();
        fps.restartAndSleep();
    }

    return 0; // Program ran successfully! return 0 to represent no errors
}