#if !defined( MAZE_GRID_HPP )
#define MAZE_GRID_HPP

    #include <vector>
    #include <SFML/System.hpp>

    class MazeGrid
    {
        sf::Vector2i dimensions;
        std::vector<bool> horizontalWallSegments;
        std::vector<bool> verticalWallSegments;
        int numberOfUsedWallSegments;
        
        public:
            MazeGrid()
            {

            }

            sf::Vector2i getDimensions()
            {
                return this->dimensions;
            }

            bool inBounds( sf::Vector2i position )
            {
                return 0 <= position.x && position.x < this->dimensions.x &&
                       0 <= position.y && position.y < this->dimensions.y;
            }

            int getTotalNumberOfWallSegments()
            {
                return this->dimensions.x * this->dimensions.y;
            }

            int getNumberOfUsedWallSegments()
            {
                return this->numberOfUsedWallSegments;
            }
    };

#endif /* MAZE_GRID_HPP */