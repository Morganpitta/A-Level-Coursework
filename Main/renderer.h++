#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "camera.h++"
    #include "mazeGrid.h++"
    #include <queue>

    class Renderer
    {
        const float yNear = 0.1;
        const float wallHeight = 200;
        Camera camera;
        std::vector<std::vector<bool>> visitedCells;
        sf::VertexArray vertexArray;
        std::vector<bool> wallSpans;

        bool hasBeenDrawnOn( int position )
        {
            assert( 0 < position && position < wallSpans.size(), "Cannot access position off screen" );
            return this->wallSpans[position];
        }

        void setHasBeenDrawnOn( int position, bool value )
        {
            assert( 0 < position && position < wallSpans.size(), "Cannot access position off screen" );
            this->wallSpans[position] = value;
        }

        public:
            Renderer(): camera(), vertexArray( sf::PrimitiveType::Lines )
            {

            }

            Camera &getCamera()
            {
                return this->camera;
            }

            float getYNear()
            {
                return this->yNear;
            }

            bool onScreen( sf::RenderWindow& window, float xValue )
            {
                return 0 <= xValue && xValue < window.getSize().x;
            }

            sf::Vector2f clipWallSegmentToNearPlane( sf::Vector2f wallStart, sf::Vector2f wallEnd )
            {
                float delta = ( wallStart.y - getYNear() ) / ( wallStart.y - wallEnd.y );
                
                return { wallStart.x + ( wallEnd.x - wallStart.x ) * delta, getYNear() };
            }

            bool projectWall( sf::RenderWindow& window, sf::Vector2f &wallStart, sf::Vector2f &wallEnd )
            {
                //Getting relative position
                wallStart = getCamera().relativePositionOf( wallStart );
                wallEnd = getCamera().relativePositionOf( wallEnd );

                // Clip near
                if ( wallStart.y < getYNear() && wallEnd.y < getYNear() )
                    return false;
                else if ( wallStart.y < getYNear() )
                {
                    wallStart = clipWallSegmentToNearPlane( wallStart, wallEnd );
                }
                else if ( wallEnd.y < getYNear() )
                {
                    wallEnd = clipWallSegmentToNearPlane( wallStart, wallEnd );
                }

                wallStart.x /= wallStart.y;
                wallEnd.x /= wallEnd.y;

                // Making sure its actually start to end not end to start
                if ( wallStart.x > wallEnd.x )
                {
                    std::swap( wallStart, wallEnd );
                }

                wallStart.x *= ( window.getSize().x / 2 ) * camera.getFov();
                wallEnd.x *= ( window.getSize().x / 2 ) * camera.getFov();

                wallStart.x += window.getSize().x / 2.f;
                wallEnd.x += window.getSize().x / 2.f;

                // Test side
                if ( wallEnd.x < 0  || wallStart.x > window.getSize().x )
                    return false;

                return true;
            }

            void drawWallEdge( sf::RenderWindow& window, sf::Vector2f edge )
            {
                float wallHeight = std::floor( this->wallHeight / edge.y );
                
                if ( onScreen( window, std::floor(edge.x) ) && !hasBeenDrawnOn(edge.x) )
                {
                    vertexArray.append( 
                        sf::Vertex( 
                            sf::Vector2f( 
                                std::floor(edge.x), 
                                ( window.getSize().y + wallHeight ) / 2 
                            ), 
                            sf::Color::Green 
                        ) 
                    );
                    vertexArray.append( 
                        sf::Vertex( 
                            sf::Vector2f( 
                                std::floor(edge.x), 
                                ( window.getSize().y - wallHeight ) / 2 
                            ), 
                            sf::Color::Green 
                        ) 
                    );

                    setHasBeenDrawnOn( edge.x, true );
                }
            }

            void drawWallTop( sf::RenderWindow& window, sf::Vector2f &wallStart, sf::Vector2f &wallEnd )
            {
                float wallStartHeight = std::floor( this->wallHeight / wallStart.y );
                float wallEndHeight = std::floor( this->wallHeight / wallEnd.y );

                // The change in y for each change in x 
                float delta = ( wallEndHeight - wallStartHeight ) / float( std::floor(wallEnd.x) - std::floor(wallStart.x) );
                float startHeight = wallStartHeight;
                int startX = std::floor(wallStart.x);

                // If it starts off of the screen, calculate where it would start on the screen
                if ( startX < 0 )
                {
                    startHeight += delta*(-startX);
                    startX = 0;
                }

                float heightIterator = startHeight;
                int xIndex = startX;
                bool wasInWall = hasBeenDrawnOn( startX );

                for ( xIndex; xIndex <= std::floor(wallEnd.x) && xIndex < window.getSize().x-1; xIndex++ )
                {
                    // If it reaches a section that has been drawn on before, 
                    if ( hasBeenDrawnOn( xIndex ) )
                    {
                        // If it was not previously on a section that was drawn on
                        if ( !wasInWall )
                        {
                            // Draw the top and bottom of the wall
                            vertexArray.append( 
                                sf::Vertex( 
                                    sf::Vector2f( 
                                        startX, 
                                        ( window.getSize().y + startHeight ) / 2
                                    ), 
                                    sf::Color::Green 
                                ) 
                            );
                            vertexArray.append( 
                                sf::Vertex( 
                                    sf::Vector2f( 
                                        xIndex, 
                                        ( window.getSize().y + heightIterator ) / 2
                                    ), 
                                    sf::Color::Green 
                                ) 
                            );

                            vertexArray.append( 
                                sf::Vertex( 
                                    sf::Vector2f( 
                                        startX, 
                                        ( window.getSize().y - startHeight ) / 2
                                    ), 
                                    sf::Color::Green
                                ) 
                            );
                            vertexArray.append(
                                sf::Vertex( 
                                    sf::Vector2f( 
                                        xIndex, ( 
                                        window.getSize().y - heightIterator ) / 2
                                    ), 
                                    sf::Color::Green 
                                )
                            );

                            wasInWall = true;
                        }

                        // Else update the start and end of the wall section which you want to draw on
                        startHeight = heightIterator;
                        startX = xIndex;
                    }
                    else
                    {
                        setHasBeenDrawnOn( xIndex, true );
                        if ( wasInWall )
                            wasInWall = false;
                    }

                    heightIterator += delta;
                }

                //If it reached the end but hasn't drawn the walls yet
                if ( startX != std::floor(wallEnd.x) && !wasInWall )
                {
                    vertexArray.append( sf::Vertex( sf::Vector2f( startX, ( window.getSize().y + startHeight ) / 2 ), sf::Color::Green ) );
                    vertexArray.append( sf::Vertex( sf::Vector2f( xIndex, ( window.getSize().y + heightIterator ) / 2 ), sf::Color::Green ) );

                    vertexArray.append( sf::Vertex( sf::Vector2f( startX, ( window.getSize().y - startHeight ) / 2 ), sf::Color::Green ) );
                    vertexArray.append( sf::Vertex( sf::Vector2f( xIndex, ( window.getSize().y - heightIterator ) / 2 ), sf::Color::Green ) );
                    
                    setHasBeenDrawnOn( xIndex, true );
                }
            }

            void drawWall( 
                sf::RenderWindow& window, 
                sf::Vector2f &wallStart, 
                sf::Vector2f &wallEnd 
            )
            {
                drawWallEdge( window, wallStart );

                drawWallEdge( window, wallEnd );

                // If its one or two pixel thin we can stop
                if ( std::floor( wallStart.x+1 ) >= std::floor( wallEnd.x ) )
                    return;

                drawWallTop( window, wallStart, wallEnd );
            }

            void render( 
                sf::RenderWindow &window, 
                MazeGrid &mazeGrid 
            )
            {
                std::queue<sf::Vector2i> cellsToVisitQueue;
                cellsToVisitQueue.push( camera.getPosition() );
                if ( visitedCells.size() != mazeGrid.getDimensions().x )
                {
                    visitedCells.clear();
                    visitedCells.resize( mazeGrid.getDimensions().x );
                    std::fill( visitedCells.begin(), visitedCells.end(), std::vector( mazeGrid.getDimensions().y, false ) );
                }
                std::for_each( visitedCells.begin(), visitedCells.end(), [](std::vector<bool>& vector){
                    std::fill( vector.begin(), vector.end(), false );
                });
                if ( wallSpans.size() != window.getSize().x )
                    wallSpans.resize( window.getSize().x );
                std::fill ( wallSpans.begin(), wallSpans.end(), false );
                vertexArray.clear();

                while ( !cellsToVisitQueue.empty() )
                {
                    sf::Vector2i cellPosition = cellsToVisitQueue.front();
                    cellsToVisitQueue.pop();

                    visitedCells[cellPosition.x][cellPosition.y] = true;
                    for ( int direction = North; direction < NumberOfDirections; direction++ )
                    {
                        bool isWall = mazeGrid.getCell( cellPosition, (Direction) direction );
                        sf::Vector2f wallStart = sf::Vector2f( cellPosition ) + 
                                                 sf::Vector2f( 0.5, 0.5 )  + 
                                                 rotatePosition( { 0.5, 0.5 }, (Direction) direction );
                        sf::Vector2f wallEnd = sf::Vector2f( cellPosition ) + 
                                               sf::Vector2f( 0.5, 0.5 ) + 
                                               rotatePosition( {-0.5, 0.5}, (Direction) direction );

                        if ( !projectWall( window, wallStart, wallEnd ) )
                            continue;

                        if ( isWall )
                        {
                            drawWall( window, wallStart, wallEnd );
                        }
                        else
                        {
                            bool shouldCheckCell = true;
                            for ( int xIndex = std::max( 0, (int) std::floor( wallStart.x ) ); xIndex <= std::floor( wallEnd.x ) && xIndex < window.getSize().x; xIndex++ )
                            {
                                if ( !hasBeenDrawnOn(xIndex) )
                                {
                                    shouldCheckCell = true;
                                    break;
                                }
                            }
                            if ( shouldCheckCell )
                            {
                                sf::Vector2i nextPosition = transposePosition( cellPosition, (Direction) direction );
                                if ( !visitedCells[nextPosition.x][nextPosition.y] )
                                    cellsToVisitQueue.push( nextPosition );
                            }
                        }
                    }
                }

                window.draw( vertexArray );
            }
    };

#endif /* RENDERER_HPP */