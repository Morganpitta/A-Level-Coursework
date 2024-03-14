#include "mazeGrid.h++"
#include "assert.h++"
#include "draw.h++"

void drawMaze( 
    sf::RenderWindow &window, 
    MazeGrid &maze, 
    sf::Vector2f topLeft, 
    sf::Vector2f bottomRight, 
    sf::Vector2i marker
)
{
    // Create a vertex array with double the number of vertices as the number of walls
    // ( As each wall is comprised of two vertices )
    sf::VertexArray vertexArray( sf::PrimitiveType::Lines, maze.getNumberOfWalls()*2 );
    float xSegmentSize = ( bottomRight.x - topLeft.x ) / maze.getDimensions().x;
    float ySegmentSize = ( bottomRight.y - topLeft.y ) / maze.getDimensions().y;

    // Loop through each wall
    for ( int xIndex = 0; xIndex < maze.getDimensions().x; xIndex++ )
    {
        for ( int yIndex = 0; yIndex < maze.getDimensions().y; yIndex++ )
        {
            if ( maze.getHorizontal( { xIndex, yIndex } ) )
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

            if ( maze.getVertical( { xIndex, yIndex } ) )
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
    
    window.draw( vertexArray );
    
    // If the marker position isn't null, then draw it
    if ( marker != NullPosition )
    {
        sf::RectangleShape markerRectangle = sf::RectangleShape({xSegmentSize/2.f,ySegmentSize/2.f});

        markerRectangle.setPosition( 
            sf::Vector2f(marker.x*xSegmentSize,-marker.y*ySegmentSize) + sf::Vector2f(50+xSegmentSize/4.f,750-(3*ySegmentSize)/4.f) 
        );

        window.draw( markerRectangle );
    }
}