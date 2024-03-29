#if !defined( DRAW_HPP )
#define DRAW_HPP

    #include <SFML/Graphics.hpp>
    #include "math.h"
    #include "file.h++"

    inline sf::Font defaultFont;
    inline sf::Font gameFont;

    inline bool loadBaseAssets()
    {
        setWorkingDirectoryToDefault();

        if ( !defaultFont.loadFromFile("georgia.ttf") )
        {
            return false;
        }

        if ( !gameFont.loadFromFile("joystix monospace.otf") )
        {
            return false;
        }


        return true;
    }

    inline void drawTextCentered(
        sf::RenderWindow &window,
        std::string string,
        sf::Font &font,
        unsigned int size,
        sf::Vector2f position,
        sf::Color colour
    )
    {
        sf::Text text(string,font,size);
        text.setOrigin( {text.getGlobalBounds().width/2.f,text.getGlobalBounds().height/2.f} );
        text.setPosition( position );
        text.setFillColor(colour);
        window.draw( text );
    }

    inline void appendLineToArray(
        sf::VertexArray &vertices, 
        sf::Vector2f startPosition, 
        sf::Vector2f endPosition, 
        sf::Color colour
    )
    {
        vertices.append( 
            sf::Vertex( 
                startPosition,
                colour
            ) 
        );
        vertices.append( 
            sf::Vertex( 
                endPosition, 
                colour
            ) 
        );
    }

#endif /* DRAW_HPP */