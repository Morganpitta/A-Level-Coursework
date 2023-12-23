#if !defined( PATH_FINDING_HPP )
#define PATH_FINDING_HPP

    #include "entity.h++"
    #include <set>

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

    struct CellData
    {
        sf::Vector2i previousCell = NullPosition;
        int distanceToStart = 0;
        int minDistanceToEnd = 0;
    };
    std::vector<std::vector<CellData>> graphData;
    struct SortBy
    {
        bool operator()(sf::Vector2i position1, sf::Vector2i position2) const
        {
            if ( graphData[position1.x][position1.y].minDistanceToEnd ==
                 graphData[position2.x][position2.y].minDistanceToEnd )
            {
                return std::tie( position1.x, position1.y ) < std::tie( position2.x, position2.y );
            }

            return graphData[position1.x][position1.y].minDistanceToEnd <
                    graphData[position2.x][position2.y].minDistanceToEnd;
        }
    };
    std::vector<sf::Vector2i> AStarPath( MazeGrid &mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition )
    {
        graphData.resize(
            mazeGrid.getDimensions().x,
            std::vector<CellData>(
                mazeGrid.getDimensions().y
            )
        );

        for ( int xIndex = 0; xIndex < mazeGrid.getDimensions().x; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < mazeGrid.getDimensions().x; yIndex++ )
            {
                graphData[xIndex][yIndex].previousCell = NullPosition;
            }
        }

        std::set<sf::Vector2i,SortBy> cellsToVisit;
        cellsToVisit.insert( startPosition );

        while ( cellsToVisit.size() > 0 ) 
        {
            sf::Vector2i currentCell = *cellsToVisit.begin();
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
                        
                        cellsToVisit.insert( nextCell );
                    }
                }
            }
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