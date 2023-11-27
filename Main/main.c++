#include "direction.h++"
#include "string.h++"
#include <iostream>

int main()
{
    Direction direction = North;
    sf::Vector2i position = {0,0};

    for ( int index = North; index < NumberOfDirections; index++ )
    {
        std::cout << format( "Currently at %s", directionToString( Direction( index ) ) );
        transposePosition( position, Direction( index ) );
    }

    return 0;
}