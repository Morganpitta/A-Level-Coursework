#if !defined ( DIRECTIONS_HPP )
#define DIRECTIONS_HPP

    #include <SFML/System.hpp>
    #include <iostream>
    #define _USE_MATH_DEFINES
    #include <cmath>

    enum Direction
    {
        North,
        East,
        South,
        West,
        NumberOfDirections,
        NoDirection
    };

    std::string directionToString( Direction direction )
    {
        switch ( direction )
        {
            case ( North ):
                return "North";
                break;
            case ( East ):
                return "East";
                break;
            case ( South ):
                return "South";
                break;
            case ( West ):
                return "West";
                break;
            default:
                return "Unkown";
                break;
        }
    }

    sf::Vector2i transposePosition( 
        sf::Vector2i position,
        Direction direction 
    )
    {
        switch ( direction )
        {
            case North:
                return { position.x, position.y-1 };
                break;

            case East:
                return { position.x+1, position.y };
                break;

            case South:
                return { position.x, position.y+1 };
                break;

            case West:
                return { position.x-1, position.y };
                break;
            
            default:
                return position;
                break;
        }
    }

    sf::Vector2f rotatePosition( 
        sf::Vector2f position, 
        Direction direction 
    )
    {
        float angle = (M_PI / 2) * ( ( direction ) % NumberOfDirections );

        return {
            static_cast<float>( 
                position.x*cos( angle ) - position.y*sin( angle ) 
            ),
            static_cast<float>( 
                position.x*sin( angle ) + position.y*cos( angle )
            ) 
        };
    }

#endif /* DIRECTIONS_HPP */