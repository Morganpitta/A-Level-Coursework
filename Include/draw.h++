#if !defined( DRAW_HPP )
#define DRAW_HPP

    #include <SFML/Graphics.hpp>
    #include "math.h"
    #include "file.h++"

    inline sf::Font defaultFont;

    inline bool loadBaseAssets()
    {
        setWorkingDirectoryToDefault();

        if ( !defaultFont.loadFromFile("georgia.ttf") )
        {
            return false;
        }

        return true;
    }

    inline void restrictText( sf::Text &text, sf::Vector2f topLeft, sf::Vector2f bottomRight )
    {
        text.setCharacterSize( 100 );

        sf::Vector2f bounds = { text.getGlobalBounds().width, text.getGlobalBounds().height };

        float size = 100 * std::min(
                ( abs(bottomRight.x-topLeft.x) ) / bounds.x,
                ( abs(bottomRight.y-topLeft.y) ) / bounds.y
            );

        text.setCharacterSize( 
            std::floor( size )
        );
        
        text.setPosition( std::round( topLeft.x ), std::round( topLeft.y ) );
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