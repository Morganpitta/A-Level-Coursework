#include "direction.h++"
#include "string.h++"
#include <iostream>

int main()
{
    Direction direction = North;
    sf::Vector2i position = {0,0};

    for ( int index = North; index < NumberOfDirections; index++ )
    {
        std::cout << format( "Currently at %d, %d, Moving %s\n", position.x, position.y, directionToString( Direction( index ) ).c_str() );
        position = transposePosition( position, Direction( index ) );
        std::cout << format( "Now at %d, %d\n", position.x, position.y );
    }

    return 0;
}