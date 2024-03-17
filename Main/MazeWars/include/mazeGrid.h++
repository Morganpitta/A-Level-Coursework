#if !defined( MAZE_GRID_HPP )
#define MAZE_GRID_HPP

    #include <vector>
    #include "direction.h++"
    #include "SFML/Graphics.hpp"

    class MazeGrid
    {
        sf::Vector2i dimensions;
        int numberOfWalls;
        std::vector<bool> horizontalSegments;
        std::vector<bool> verticalSegments;
        
        public:
            MazeGrid( sf::Vector2i dimensions );

            ~MazeGrid();

            sf::Vector2i getDimensions() const;

            bool inBounds( sf::Vector2i position )  const;

            std::size_t getNumberOfWalls() const;

            std::size_t getNumberOfHorizontalSegments() const;

            std::size_t getNumberOfVerticalSegments() const;

            std::size_t getNumberOfWallSegments() const;

            bool getHorizontal( sf::Vector2i position ) const;

            bool getVertical( sf::Vector2i position ) const;

            bool getCell( 
                sf::Vector2i position, 
                Direction direction 
            ) const;

            void set( 
                std::vector<bool> horizontalSegments, 
                std::vector<bool> verticalSegments 
            );

            void fill( bool value );

            void resize( sf::Vector2i dimensions );

            void setHorizontal( 
                sf::Vector2i position, 
                bool value 
            );

            void setVertical( 
                sf::Vector2i position, 
                bool value 
            );
            
            void setCell( 
                sf::Vector2i position,
                Direction direction, 
                bool value 
            );
    };

    extern void drawMaze( 
        sf::RenderWindow &window, 
        MazeGrid &maze, 
        sf::Vector2f topLeft, 
        sf::Vector2f bottomRight, 
        std::vector<sf::Vector2i> markers = {} 
    );

#endif /* MAZE_GRID_HPP */