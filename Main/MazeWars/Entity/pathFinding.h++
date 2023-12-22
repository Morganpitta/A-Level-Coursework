#if !defined( PATH_FINDING_HPP )
#define PATH_FINDING_HPP

    #include "entity.h++"

    const sf::Vector2i NullPosition = {-1,-1};

    bool isDirectlyInFront( MazeGrid &mazeGrid, Entity entity1, sf::Vector2i entity2Position )
    {
        sf::Vector2i relativePosition = entity1.relativePositionOf( entity2Position );
        if ( relativePosition.x == 0 and relativePosition.y > 0 )
        {
            sf::Vector2i position = entity1.getPosition();
            while ( position != entity2Position )
            {
                if ( mazeGrid.getCell( position, entity1.getDirection() ) )
                    return false;
                position = transposePosition( position, entity1.getDirection() );
            }

            return true;
        }

        return false;
    } 

    float manhattanDistance( sf::Vector2i startPosition, sf::Vector2i finalPosition ) 
    {
        return abs( startPosition.x - finalPosition.x ) + abs( startPosition.y - finalPosition.y );
    }

    std::vector<sf::Vector2i> AStarPath( MazeGrid mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition )
    {
        // A 2d array of tuples representing specific graph data about each cell. 
        // The first value represents the previous connected cell, the second value represents the distance to the start 
        // and the final value represents the minimum predicted distance to the end
        struct CellData
        {
            sf::Vector2i previousCell = NullPosition;
            int distanceToStart = 0;
            int minDistanceToEnd = 0;
        };

        std::vector<std::vector<CellData>> graphData;
        graphData.resize(
            mazeGrid.getDimensions().x,
            std::vector<CellData>(
                mazeGrid.getDimensions().y
            )
        );

        std::vector<sf::Vector2i> cellsToVisit;
        cellsToVisit.push_back( startPosition );

        while ( cellsToVisit.size() > 0 ) 
        {
            sf::Vector2i currentCell = cellsToVisit.front();
            cellsToVisit.erase(cellsToVisit.begin());

            if ( currentCell == finalPosition )
                break;

            for ( int direction = North; direction < NumberOfDirections; direction++ )
            {
                bool isWall = mazeGrid.getCell( currentCell, (Direction) direction );

                if ( !isWall ) 
                {
                    sf::Vector2i nextCell = transposePosition( currentCell, (Direction) direction );
                    if ( nextCell == startPosition || !mazeGrid.inBounds( nextCell ) )
                        continue;

                    if ( graphData[nextCell.x][nextCell.y].previousCell == NullPosition || 
                         graphData[nextCell.x][nextCell.y].distanceToStart > graphData[currentCell.x][currentCell.y].distanceToStart + 1 )
                    { 

                        graphData[nextCell.x][nextCell.y].previousCell = currentCell;
                        graphData[nextCell.x][nextCell.y].distanceToStart = graphData[currentCell.x][currentCell.y].distanceToStart + 1;
                        graphData[nextCell.x][nextCell.y].minDistanceToEnd = graphData[nextCell.x][nextCell.y].distanceToStart + 
                                                                            manhattanDistance(nextCell, finalPosition);
                        
                        if ( std::count( cellsToVisit.begin(), cellsToVisit.end(), nextCell ) == 0 )
                            cellsToVisit.push_back( nextCell );
                    }
                }
            }

            std::sort( 
                cellsToVisit.begin(), 
                cellsToVisit.end(), 
                [graphData](sf::Vector2i position1, sf::Vector2i position2)
                {
                    return graphData[position1.x][position1.y].minDistanceToEnd <
                            graphData[position2.x][position2.y].minDistanceToEnd;
                } 
            );
        }

        if ( graphData[finalPosition.x][finalPosition.y].previousCell == NullPosition )
            return {};
        
        std::vector<sf::Vector2i> path = {};
        sf::Vector2i cell = finalPosition;
        while ( cell != NullPosition ) 
        {
            path.insert( path.begin(), cell );
            cell = graphData[cell.x][cell.y].previousCell;
        }

        return path;
    }


#endif /* PATH_FINDING_HPP */