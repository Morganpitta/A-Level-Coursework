#if !defined( PATH_FINDING_HPP )
#define PATH_FINDING_HPP

    #include "entity.h++"
    #include "mazeGrid.h++"
    #include <set>
    #include <functional>

    extern bool isDirectlyInFront( MazeGrid &mazeGrid, Entity *entity1, sf::Vector2i entity2Position );

    extern float manhattanDistance( sf::Vector2i startPosition, sf::Vector2i finalPosition );

    class AStarSolver
    {
        struct CellData
        {
            sf::Vector2i previousCell = NullPosition;
            int distanceToStart = 0;
            int predictedDistanceToEnd = 0;
        };
        std::vector<std::vector<CellData>> graphData;
        std::set<sf::Vector2i,std::function<bool(const sf::Vector2i&, const sf::Vector2i&)>> cellsToVisit;
        
        bool comparisonFunction( const sf::Vector2i &position1, const sf::Vector2i &position2) const;

        void reset( sf::Vector2i dimensions );

        CellData &getCellData( sf::Vector2i position );

        CellData getCellData( sf::Vector2i position ) const;

        void addCellToVisit( sf::Vector2i currentCell, sf::Vector2i nextCell, sf::Vector2i finalPosition );

        std::vector<sf::Vector2i> getReturnPath( sf::Vector2i startPosition, sf::Vector2i finalPosition );

        public:
            AStarSolver();

            std::vector<sf::Vector2i> solve( MazeGrid &mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition );
    };

    extern AStarSolver PathSolver;

#endif /* PATH_FINDING_HPP */