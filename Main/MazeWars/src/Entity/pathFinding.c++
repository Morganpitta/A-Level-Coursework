#include "Entity/pathFinding.h++"

namespace MazeWars
{
    AStarSolver PathSolver;

    bool isDirectlyInFront( MazeGrid &mazeGrid, Entity *entity1, sf::Vector2i entity2Position )
    {
        sf::Vector2i relativePosition = entity1->relativePositionOf( entity2Position );
        if ( relativePosition.x == 0 and relativePosition.y > 0 )
        {
            sf::Vector2i position = entity1->getPosition();
            while ( position != entity2Position )
            {
                if ( mazeGrid.getCell( position, entity1->getDirection() ) )
                    return false;
                position = transposePosition( position, entity1->getDirection() );
            }

            return true;
        }

        return false;
    } 

    float manhattanDistance( sf::Vector2i startPosition, sf::Vector2i finalPosition ) 
    {
        return abs( startPosition.x - finalPosition.x ) + abs( startPosition.y - finalPosition.y );
    }

    bool AStarSolver::comparisonFunction( const sf::Vector2i &position1, const sf::Vector2i &position2 ) const
    {
        // If the distances are the same, since its a set comparison function it needs to be consistent.
        // So use the position to calculate a consistent comparison.
        if ( getCellData(position1).predictedDistanceToEnd ==
            getCellData(position2).predictedDistanceToEnd )
        {
            return std::tie( position1.x, position1.y ) < std::tie( position2.x, position2.y );
        }

        return getCellData(position1).predictedDistanceToEnd <
            getCellData(position2).predictedDistanceToEnd;
    }


    void AStarSolver::reset( sf::Vector2i dimensions )
    {
        this->graphData.resize(
            dimensions.x,
            std::vector<CellData>(
                dimensions.y
            )
        );
        
        for ( int xIndex = 0; xIndex < dimensions.x; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < dimensions.y; yIndex++ )
            {
                this->graphData[xIndex][yIndex].previousCell = NullPosition;
            }
        }

        this->cellsToVisit.clear();
    }

    AStarSolver::CellData &AStarSolver::getCellData( sf::Vector2i position )
    {
        return this->graphData[position.x][position.y];
    }

    AStarSolver::CellData AStarSolver::getCellData( sf::Vector2i position ) const
    {
        return this->graphData[position.x][position.y];
    }

    void AStarSolver::addCellToVisit( sf::Vector2i currentCell, sf::Vector2i nextCell, sf::Vector2i finalPosition )
    {
        // If the cell is unvisited or the original path was longer than this path, update to use this path.
        if (
            getCellData(nextCell).previousCell == NullPosition || 
            getCellData(nextCell).distanceToStart > 
            getCellData(currentCell).distanceToStart + 1 
        )
        { 
            getCellData(nextCell).previousCell = currentCell;
            getCellData(nextCell).distanceToStart = getCellData(currentCell).distanceToStart + 1;

            getCellData(nextCell).predictedDistanceToEnd = getCellData(nextCell).distanceToStart + manhattanDistance(nextCell, finalPosition);
            
            cellsToVisit.insert( nextCell );
        }
    }

    std::vector<sf::Vector2i> AStarSolver::getReturnPath( sf::Vector2i startPosition, sf::Vector2i finalPosition )
    {
        std::vector<sf::Vector2i> path = {};
        sf::Vector2i cell = finalPosition;
        while ( cell != startPosition )
        {
            // Somethings gone very wrong if this is true ( or theres just no path back )
            if ( getCellData(cell).previousCell == NullPosition )
                return {};

            path.insert( path.begin(), cell );
            cell = getCellData(cell).previousCell;
        }

        path.insert( path.begin(), startPosition );

        return path;
    }

    AStarSolver::AStarSolver(): cellsToVisit(std::bind(&AStarSolver::comparisonFunction, this, std::placeholders::_1, std::placeholders::_2))
    {
        
    }

    std::vector<sf::Vector2i> AStarSolver::solve( MazeGrid &mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition )
    {
        reset( mazeGrid.getDimensions() );

        cellsToVisit.insert( startPosition );

        while ( cellsToVisit.size() > 0 ) 
        {
            sf::Vector2i currentCell = *cellsToVisit.begin();
            cellsToVisit.erase(cellsToVisit.begin());

            if ( currentCell == finalPosition )
                break;

            forEachDirection( direction )
            {
                bool isWall = mazeGrid.getCell( currentCell, (Direction) direction );

                if ( !isWall )
                {
                    sf::Vector2i nextCell = transposePosition( currentCell, (Direction) direction );
                    if ( nextCell == startPosition || !mazeGrid.inBounds( nextCell ) )
                        continue;

                    addCellToVisit( currentCell, nextCell, finalPosition );
                }
            }
        }

        return getReturnPath( startPosition, finalPosition );
    }
}