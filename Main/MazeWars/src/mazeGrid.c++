#include "mazeGrid.h++"
#include "assert.h++"
#include "draw.h++"

namespace MazeWars
{
    MazeGrid::MazeGrid( sf::Vector2i dimensions )
    {
        resize( dimensions );
    }

    MazeGrid::~MazeGrid()
    {
        horizontalSegments.clear();
        verticalSegments.clear();
    }

    sf::Vector2i MazeGrid::getDimensions() const
    {
        return this->dimensions;
    }

    bool MazeGrid::inBounds( sf::Vector2i position )  const
    {
        return 0 <= position.x && position.x < getDimensions().x &&
            0 <= position.y && position.y < getDimensions().y;
    }

    std::size_t MazeGrid::getNumberOfWalls() const
    {
        return this->numberOfWalls;
    }

    std::size_t MazeGrid::getNumberOfHorizontalSegments() const
    {
        return getDimensions().x * (getDimensions().y+1);
    }

    std::size_t MazeGrid::getNumberOfVerticalSegments() const
    {
        return (getDimensions().x+1) * getDimensions().y;
    }

    std::size_t MazeGrid::getNumberOfWallSegments() const
    {
        return getNumberOfHorizontalSegments() + getNumberOfVerticalSegments();
    }

    bool MazeGrid::getHorizontal( sf::Vector2i position ) const
    {
        assert( 
            std::size_t(position.x+position.y*getDimensions().x) < getNumberOfHorizontalSegments(),
            "Cannot access a horizontal wall segment that doesn't exist"
        );

        return this->horizontalSegments[position.x+position.y*getDimensions().x];
    }

    bool MazeGrid::getVertical( sf::Vector2i position ) const
    {
        assert( 
            std::size_t(position.x+position.y*getDimensions().x) < getNumberOfVerticalSegments(),
            "Cannot access a vertical wall segment that doesn't exist"
        );

        return this->verticalSegments[position.x+position.y*(getDimensions().x+1)];
    }

    bool MazeGrid::getCell( 
        sf::Vector2i position, 
        Direction direction 
    ) const
    {
        switch( direction )
        {
            case North:
                return getHorizontal( { position.x, position.y+1 } );
                break;
                
            case East:
                return getVertical( { position.x+1, position.y } );
                break;
                
            case South:
                return getHorizontal( { position.x, position.y } );
                break;
                
            case West:
                return getVertical( { position.x, position.y } );
                break;

            default:
                throw std::runtime_error( "Direction can only be: North, East, South, West" );
                break;
        }
    }

    void MazeGrid::set( 
        std::vector<bool> horizontalSegments, 
        std::vector<bool> verticalSegments 
    )
    {
        assert( 
            horizontalSegments.size() == getNumberOfHorizontalSegments() &&
            verticalSegments.size() == getNumberOfVerticalSegments(),
            "Dimensions do not match" 
        );

        // The passed in parameters will be inverted on the y axis, and thus needs to be reversed.
        this->horizontalSegments.clear();

        for ( int horizontalIndex = 0; horizontalIndex < ( getDimensions().y + 1 ); horizontalIndex++ )
        {
            this->horizontalSegments.insert(
                this->horizontalSegments.begin(), 
                horizontalSegments.begin() + ( horizontalIndex ) * getDimensions().x, 
                horizontalSegments.begin() + ( horizontalIndex + 1 ) * getDimensions().x
            );
        }

        this->verticalSegments.clear();

        for ( int verticalIndex = 0; verticalIndex < getDimensions().y; verticalIndex++ )
        {
            this->verticalSegments.insert(
                this->verticalSegments.begin(), 
                verticalSegments.begin() + verticalIndex * ( getDimensions().x + 1 ), 
                verticalSegments.begin() + ( verticalIndex + 1 ) * ( getDimensions().x + 1)
            );
        }

        this->numberOfWalls =
            std::count(
                this->horizontalSegments.begin(),
                this->horizontalSegments.end(), 
                true
            ) + 
            std::count(
                this->verticalSegments.begin(),
                this->verticalSegments.end(), 
                true
            );
    }

    void MazeGrid::fill( bool value )
    {
        std::fill( 
            this->horizontalSegments.begin(), 
            this->horizontalSegments.end(),
            value            
        );
        std::fill( 
            this->verticalSegments.begin(), 
            this->verticalSegments.end(),
            value            
        );

        this->numberOfWalls = value ? getNumberOfWallSegments() : 0;
    }

    void MazeGrid::resize( sf::Vector2i dimensions )
    {
        assert( 
            dimensions.x > 0 &&
            dimensions.y > 0,
            "Dimensions must be positive" 
        );

        this->dimensions = dimensions;
        this->numberOfWalls = getNumberOfWallSegments();

        this->horizontalSegments.resize(
            getNumberOfHorizontalSegments()
        );
        this->verticalSegments.resize(
            getNumberOfVerticalSegments()
        );

        fill( true );
    }

    void MazeGrid::setHorizontal( 
        sf::Vector2i position, 
        bool value 
    )
    {
        if ( getHorizontal(position) != value )
        {
            // If the value is true, we have just added a wall, therefore we need to add 1 to the number of walls
            // Else the value is false, and we have just removed a wall, therefore we need to minus 1.
            this->numberOfWalls += value == true ? 1 : -1;
            this->horizontalSegments[position.x+position.y*getDimensions().x] = value;
        }
    }

    void MazeGrid::setVertical( 
        sf::Vector2i position, 
        bool value 
    )
    {
        if ( getVertical(position) != value )
        {
            // If the value is true, we have just added a wall, therefore we need to add 1 to the number of walls
            // Else the value is false, and we have just removed a wall, therefore we need to minus 1.
            this->numberOfWalls += value == true ? 1 : -1;
            this->verticalSegments[position.x+position.y*(getDimensions().x+1)] = value;
        }
    }

    void MazeGrid::setCell( 
        sf::Vector2i position,
        Direction direction, 
        bool value 
    )
    {
        switch( direction )
        {
            case North:
                setHorizontal( { position.x, position.y+1 }, value );
                break;
                
            case East:
                setVertical( { position.x+1, position.y }, value );
                break;
                
            case South:
                setHorizontal( { position.x, position.y }, value );
                break;
                
            case West:
                setVertical( { position.x, position.y }, value );
                break;

            default:
                throw std::runtime_error( "Direction can only be: North, East, South, West" );
                break;
        }
    }

    void drawMaze( 
        sf::RenderWindow &window, 
        MazeGrid &maze, 
        sf::Vector2f topLeft, 
        sf::Vector2f bottomRight, 
        std::vector<sf::Vector2i> markers
    )
    {
        // Create a vertex array with double the number of vertices as the number of walls
        // ( As each wall is comprised of two vertices )
        sf::VertexArray vertexArray( sf::PrimitiveType::Lines, maze.getNumberOfWalls()*2 );
        float xSegmentSize = ( bottomRight.x - topLeft.x ) / maze.getDimensions().x;
        float ySegmentSize = ( bottomRight.y - topLeft.y ) / maze.getDimensions().y;

        // Loop through each horizontal wall
        for ( int xIndex = 0; xIndex < maze.getDimensions().x; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < (maze.getDimensions().y+1); yIndex++ )
            {
                if ( maze.getHorizontal( { xIndex, yIndex } ) )
                {
                    appendLineToArray( vertexArray,
                        sf::Vector2f( 
                            topLeft.x + xIndex * xSegmentSize,
                            bottomRight.y - yIndex * ySegmentSize
                        ), 
                        sf::Vector2f( 
                            topLeft.x + ( xIndex + 1 ) * xSegmentSize,
                            bottomRight.y - ( yIndex ) * ySegmentSize
                        ),
                        sf::Color::Green
                    );
                }
            }
        }

        // Loop through each vertical wall
        for ( int xIndex = 0; xIndex < (maze.getDimensions().x+1); xIndex++ )
        {
            for ( int yIndex = 0; yIndex < maze.getDimensions().y; yIndex++ )
            {
                if ( maze.getVertical( { xIndex, yIndex } ) )
                {
                    appendLineToArray( vertexArray,
                        sf::Vector2f( 
                            topLeft.x + xIndex * xSegmentSize,
                            bottomRight.y - yIndex * ySegmentSize
                        ), 
                        sf::Vector2f( 
                            topLeft.x + ( xIndex ) * xSegmentSize,
                            bottomRight.y - ( yIndex + 1 ) * ySegmentSize
                        ),
                        sf::Color::Green
                    );
                }
            }
        }
        
        window.draw( vertexArray );
        
        for ( sf::Vector2i marker: markers )
        {
            sf::RectangleShape markerRectangle = sf::RectangleShape({xSegmentSize/2.f,ySegmentSize/2.f});

            markerRectangle.setPosition( 
                sf::Vector2f(marker.x*xSegmentSize,-marker.y*ySegmentSize) + sf::Vector2f(50+xSegmentSize/4.f,750-(3*ySegmentSize)/4.f) 
            );

            window.draw( markerRectangle );
        }
    }
}