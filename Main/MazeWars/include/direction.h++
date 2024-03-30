#if !defined ( DIRECTIONS_HPP )
#define DIRECTIONS_HPP

    #include <SFML/System.hpp>
    #include <iostream>
    #define _USE_MATH_DEFINES
    #include <cmath>

    namespace MazeWars
    {
        extern const sf::Vector2i NullPosition;

        enum Direction
        {
            North,
            East,
            South,
            West,
            NumberOfDirections,
            NoDirection
        };

        std::string directionToString( Direction direction );

        sf::Vector2i transposePosition( 
            sf::Vector2i position,
            Direction direction
        );

        Direction getDirectionOf( 
            sf::Vector2i position1, 
            sf::Vector2i position2 
        );

        sf::Vector2f rotatePosition( 
            sf::Vector2f position, 
            Direction direction 
        );

        Direction normaliseDirection( int direction );

        Direction reverseDirection( int direction );

        #define forEachDirection( direction )   \
            for ( Direction direction = North; direction < NumberOfDirections; direction = Direction( direction + 1 ) )
    }

#endif /* DIRECTIONS_HPP */