#if !defined( MAZE_GRID_HPP )
#define MAZE_GRID_HPP

    #include <vector>
    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    class MazeGrid
    {
        sf::Vector2i dimensions;
        int numberOfWalls;
        std::vector<bool> horizontalSegments;
        std::vector<bool> verticalSegments;
        
        public:
            MazeGrid( sf::Vector2i dimensions )
            {
                resize( dimensions );
            }

            sf::Vector2i getDimensions()
            {
                return this->dimensions;
            }

            bool inBounds( sf::Vector2i position )
            {
                return 0 <= position.x && position.x < getDimensions().x &&
                       0 <= position.y && position.y < getDimensions().y;
            }

            int getNumberOfWalls()
            {
                return this->numberOfWalls;
            }

            int getNumberOfHorizontalSegments()
            {
                return getDimensions().x * getDimensions().y;
            }

            int getNumberOfVerticalSegments()
            {
                return getDimensions().x * getDimensions().y;
            }

            int getNumberOfWallSegments()
            {
                return getNumberOfHorizontalSegments() + getNumberOfVerticalSegments();
            }

            bool getHorizontal( sf::Vector2i position )
            {
                assert( 
                    position.y+position.x*getDimensions().y < getNumberOfHorizontalSegments(),
                    "Cannot access a horizontal wall segment that doesn't exist"
                );

                return horizontalSegments[position.y+position.x*getDimensions().y];
            }

            bool getVertical( sf::Vector2i position )
            {
                assert( 
                    position.y+position.x*getDimensions().y < getNumberOfVerticalSegments(),
                    "Cannot access a vertical wall segment that doesn't exist"
                );

                return verticalSegments[position.x+position.y*getDimensions().x];
            }

            bool getCell( sf::Vector2i position, Direction direction )
            {
                switch( direction )
                {
                    case North:
                        return getHorizontal( { position.x, position.y+1 } );
                        break;
                        
                    case East:
                        return getVertical( { position.x, position.y } );
                        break;
                        
                    case South:
                        return getHorizontal( { position.x, position.y } );
                        break;
                        
                    case West:
                        return getVertical( { position.x+1, position.y } );
                        break;
                }
            }

            void resize( sf::Vector2i dimensions )
            {
                this->dimensions = dimensions;
                this->numberOfWalls = getNumberOfWallSegments();

                this->horizontalSegments.resize(
                    getNumberOfHorizontalSegments(),
                    true
                );
                this->verticalSegments.resize(
                    getNumberOfVerticalSegments(),
                    true
                );
            }

            void setHorizontal( sf::Vector2i position, bool value )
            {
                if ( getHorizontal(position) != value )
                {
                    // If the value is true, we have just added a wall, therefore we need to add 1 to the number of walls
                    // Else the value is false, and we have just removed a wall, therefore we need to minus 1.
                    numberOfWalls += value == true ? 1 : -1;
                    horizontalSegments[position.y+position.x*getDimensions().y] = value;
                }
            }

            void setVertical( sf::Vector2i position, bool value )
            {
                if ( getVertical(position) != value )
                {
                    // If the value is true, we have just added a wall, therefore we need to add 1 to the number of walls
                    // Else the value is false, and we have just removed a wall, therefore we need to minus 1.
                    numberOfWalls += value == true ? 1 : -1;
                    verticalSegments[position.x+position.y*getDimensions().x] = value;
                }
            }
            
            void setCell( sf::Vector2i position, Direction direction, bool value )
            {
                switch( direction )
                {
                    case North:
                        setHorizontal( { position.x, position.y+1 }, value );
                        break;
                        
                    case East:
                        setVertical( { position.x, position.y }, value );
                        break;
                        
                    case South:
                        setHorizontal( { position.x, position.y }, value );
                        break;
                        
                    case West:
                        setVertical( { position.x+1, position.y }, value );
                        break;
                }
            }
    };

    void drawMaze( sf::RenderWindow &window, MazeGrid &maze, sf::Vector2f topLeft, sf::Vector2f bottomRight  )
    {
        sf::VertexArray vertexArray( sf::PrimitiveType::Lines, maze.getNumberOfWalls()*2 );
        float xSegmentSize = ( bottomRight.x - topLeft.x ) / maze.getDimensions().x;
        float ySegmentSize = ( bottomRight.y - topLeft.y ) / maze.getDimensions().y;
        int vertexIndex = 0;
        for ( int xIndex = 0; xIndex < maze.getDimensions().x; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < ( maze.getDimensions().y + 1 ); yIndex++ )
            {
                if ( maze.getHorizontal( { xIndex, yIndex } ) )
                {
                    vertexArray[vertexIndex++] = sf::Vertex( sf::Vector2f( xIndex * xSegmentSize, yIndex * ySegmentSize ) + topLeft, sf::Color::Green );
                    vertexArray[vertexIndex++] = sf::Vertex( sf::Vector2f( ( xIndex + 1 ) * xSegmentSize, ( yIndex ) * ySegmentSize ) + topLeft, sf::Color::Green );
                }
            }
        }
        for ( int xIndex = 0; xIndex < ( maze.getDimensions().x + 1 ); xIndex++ )
        {
            for ( int yIndex = 0; yIndex < maze.getDimensions().y; yIndex++ )
            {
                if ( maze.getVertical( { xIndex, yIndex } ) )
                {
                    vertexArray[vertexIndex++] = sf::Vertex( sf::Vector2f( xIndex * xSegmentSize, yIndex * ySegmentSize ) + topLeft, sf::Color::Green );
                    vertexArray[vertexIndex++] = sf::Vertex( sf::Vector2f( ( xIndex ) * xSegmentSize, ( yIndex + 1 ) * ySegmentSize ) + topLeft, sf::Color::Green);
                }
            }
        }
        window.draw( vertexArray );
    }

#endif /* MAZE_GRID_HPP */