#include "mazeGenerator.h++"
#include "random.h++"

void randomlyRemoveWall( 
    sf::Vector2i position,
    MazeGrid &mazeGrid,
    float randomness
)
{
    if ( randomFloat(0,1) < randomness )
    {
        Direction direction = Direction( randomInt( North, West ) );

        if ( mazeGrid.inBounds( transposePosition( position, direction ) ) )
        {
            mazeGrid.setCell( 
                position, 
                direction, 
                false 
            );
        }
    }
}

Direction getRandomValidDirection( 
    sf::Vector2i position, 
    MazeGrid &mazeGrid, 
    const std::vector<std::vector<bool>> &isSearched 
)
{
    std::vector<Direction> directions = { North, East, South, West };

    for ( int index = 0; index < directions.size(); index++ )
    {
        sf::Vector2i transposedPosition = transposePosition( position, directions[index] );

        if ( !mazeGrid.inBounds( transposedPosition ) || isSearched[ transposedPosition.x ][ transposedPosition.y ] )
        {
            directions.erase(directions.begin()+index--);
        }
    }

    if ( directions.size() == 0 )
        return NoDirection;
    
    return directions[ randomInt( 0, directions.size() - 1 ) ];
}

void generateMazeDepthFirst( 
    MazeGrid &mazeGrid, 
    float randomness, 
    std::size_t seed
)
{
    sf::Vector2i position = {0,0};
    std::vector<sf::Vector2i> positionStack = {{0,0}};
    std::vector<std::vector<bool>> isSearched;

    isSearched.resize( mazeGrid.getDimensions().x, std::vector<bool>( mazeGrid.getDimensions().y, false ) );
    positionStack.reserve(mazeGrid.getDimensions().x*mazeGrid.getDimensions().y);

    while ( true )
    {
        Direction direction = getRandomValidDirection( position, mazeGrid, isSearched );
        isSearched[position.x][position.y] = true;

        if ( direction == NoDirection )
        {
            positionStack.pop_back();

            if ( positionStack.size() == 0 )
                break;
            
            position = positionStack[positionStack.size()-1];
        }
        else
        {
            mazeGrid.setCell( position, direction, false );
            position = transposePosition( position, direction );
            positionStack.push_back( position );
            randomlyRemoveWall( position, mazeGrid, randomness );
        }
    }
}