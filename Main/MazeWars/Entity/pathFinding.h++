#if !defined( PATH_FINDING_HPP )
#define PATH_FINDING_HPP

    #include "entity.h++"
    #include <set>
    #include <functional>

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

    class AStarSolver
    {
        struct CellData
        {
            sf::Vector2i previousCell = NullPosition;
            int distanceToStart = 0;
            int minDistanceToEnd = 0;
        };
        std::vector<std::vector<CellData>> graphData;
        
        bool comparisonFunction( const sf::Vector2i &position1, const sf::Vector2i &position2) const
        {
            if ( this->graphData[position1.x][position1.y].minDistanceToEnd ==
                 this->graphData[position2.x][position2.y].minDistanceToEnd )
            {
                return std::tie( position1.x, position1.y ) < std::tie( position2.x, position2.y );
            }

            return this->graphData[position1.x][position1.y].minDistanceToEnd <
                   this->graphData[position2.x][position2.y].minDistanceToEnd;
        }
        std::set<sf::Vector2i,std::function<bool(const sf::Vector2i&, const sf::Vector2i&)>> cellsToVisit;


        void reset( sf::Vector2i dimensions )
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

        CellData &getCellData( sf::Vector2i position )
        {
            return this->graphData[position.x][position.y];
        }

        void addCellToVisit( sf::Vector2i currentCell, sf::Vector2i nextCell, sf::Vector2i finalPosition )
        {
            if ( 
                getCellData(nextCell).previousCell == NullPosition || 
                getCellData(nextCell).distanceToStart > 
                getCellData(currentCell).distanceToStart + 1 
            )
            { 

                getCellData(nextCell).previousCell = currentCell;
                getCellData(nextCell).distanceToStart = 
                    getCellData(currentCell).distanceToStart + 1;

                getCellData(nextCell).minDistanceToEnd = 
                    getCellData(nextCell).distanceToStart +
                    manhattanDistance(nextCell, finalPosition);
                
                cellsToVisit.insert( nextCell );
            }
        }

        std::vector<sf::Vector2i> getReturnPath( sf::Vector2i startPosition, sf::Vector2i finalPosition )
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

        public:
            AStarSolver(): cellsToVisit(std::bind(&comparisonFunction,this, std::placeholders::_1, std::placeholders::_2))
            {
                
            }

            std::vector<sf::Vector2i> solve( MazeGrid &mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition )
            {
                reset( mazeGrid.getDimensions() );

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

                            addCellToVisit( currentCell, nextCell, finalPosition );
                        }
                    }
                }

                return getReturnPath( startPosition, finalPosition );
            }
    } PathSolver;

#endif /* PATH_FINDING_HPP */