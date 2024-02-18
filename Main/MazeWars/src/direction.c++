#include "direction.h++"

const sf::Vector2i NullPosition = {-1,-1};

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
            return "Unknown";
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
            return { position.x, position.y+1 };
            break;

        case East:
            return { position.x+1, position.y };
            break;

        case South:
            return { position.x, position.y-1 };
            break;

        case West:
            return { position.x-1, position.y };
            break;
        
        default:
            return position;
            break;
    }
}

Direction getDirectionOf( 
    sf::Vector2i position1, 
    sf::Vector2i position2 
)
{
    if ( position2 == sf::Vector2i( position1.x, position1.y+1 ) )
        return North;

    if ( position2 == sf::Vector2i( position1.x+1, position1.y ) )
        return East;

    if ( position2 == sf::Vector2i( position1.x, position1.y-1 ) )
        return South;

    if ( position2 == sf::Vector2i( position1.x-1, position1.y ) )
        return West;

    return NoDirection;
}

sf::Vector2f rotatePosition( 
    sf::Vector2f position, 
    Direction direction 
)
{
    // Converting the direction into an angle 
    // North -> 0 degrees, East -> 90 degrees, 
    // South -> 180 degrees, West -> 270 degrees.
    float angle = (M_PI / 2) * ( ( direction ) % NumberOfDirections );

    
    // The 2D rotation matrix
    return {
        static_cast<float>( 
            position.x*cos( angle ) + position.y*sin( angle ) 
        ),
        static_cast<float>( 
            - position.x*sin( angle ) + position.y*cos( angle )
        ) 
    };
}

Direction normaliseDirection( int direction )
{
    direction = ( direction ) % NumberOfDirections;
    if ( direction < 0 )
        direction += NumberOfDirections;
    return Direction( direction );
}

Direction reverseDirection( int direction )
{
    return normaliseDirection( direction + South );
}