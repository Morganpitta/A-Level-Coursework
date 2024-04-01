#include "mazeGenerator.h++"
#include "random.h++"

namespace MazeWars
{
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
        std::vector<Direction> validDirections = {};

        forEachDirection( direction )
        {
            sf::Vector2i transposedPosition = transposePosition( position, direction );

            // If the position is in bounds, and it hasn't been searched, add it to our list.
            if ( mazeGrid.inBounds( transposedPosition ) && !isSearched[ transposedPosition.x ][ transposedPosition.y ] )
                validDirections.push_back( direction );
        }

        // If theres no valid directions, return NoDirection
        if ( validDirections.empty() )
            return NoDirection;
        
        // Select a random direction from the list.
        return validDirections[ randomInt( 0, validDirections.size() - 1 ) ];
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
            isSearched[position.x][position.y] = true;
            Direction direction = getRandomValidDirection( position, mazeGrid, isSearched );

            if ( direction == NoDirection )
            {
                // No direction to go, need to backtrack
                positionStack.pop_back();

                if ( positionStack.empty() )
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
}