#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "camera.h++"
    #include "mazeGrid.h++"
    #include "entity.h++"
    #include <queue>
    #include <map>

    class Renderer
    {
        const float yNear = 0.1;
        const float wallHeight = 200;
        const float entityHeight = 75;
        Camera camera;
        sf::VertexArray wallVertices;
        sf::VertexArray entityVertices;
        std::vector<bool> drawnOn;

        bool hasBeenDrawnOn( int xIndex )
        {
            assert( 
                xIndex >= 0 &&
                xIndex < drawnOn.size(),
                "Index out of range"
            );

            return this->drawnOn[xIndex];
        }

        bool canDrawInRange( sf::RenderWindow &window, float startIndex, float endIndex )
        {
            for ( int index = std::max( 0.f, std::floor( startIndex ) ); index <= std::min( std::floor( endIndex ), window.getSize().x - 1.f ); index++ )
            {
                if ( !hasBeenDrawnOn(index) )
                    return true;
            }

            return false;
        }

        void setHasBeenDrawnOn( int xIndex, bool value )
        {
            assert( 
                xIndex >= 0 &&
                xIndex < drawnOn.size(),
                "Index out of range"
            );

            this->drawnOn[xIndex] = value;
        }

        public:
            Renderer(): camera(), wallVertices( sf::PrimitiveType::Lines ), entityVertices( sf::PrimitiveType::Quads )
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

                // Making sure it's start to end not end to start
                if ( wallStart.x > wallEnd.x )
                {
                    std::swap( wallStart, wallEnd );
                }

                wallStart.x *= ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 );
                wallEnd.x *= ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 );

                wallStart.x += window.getSize().x / 2.f;
                wallEnd.x += window.getSize().x / 2.f;

                // Test if offscreen
                if ( wallEnd.x < 0  || wallStart.x > window.getSize().x )
                    return false;

                return true;
            }

            void drawWallEdge( sf::RenderWindow& window, sf::Vector2f edge )
            {
                if ( onScreen( window, edge.x ) && !hasBeenDrawnOn( std::floor( edge.x ) ) )
                {
                    float wallHeight = std::floor( this->wallHeight / edge.y );
                    
                    wallVertices.append( 
                        sf::Vertex( 
                            sf::Vector2f( 
                                std::floor(edge.x), 
                                ( window.getSize().y + wallHeight ) / 2 
                            ), 
                            sf::Color::Green 
                        ) 
                    );
                    wallVertices.append( 
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
                int wallStartX = std::floor( wallStart.x + 1 );
                float wallStartHeight = std::floor( this->wallHeight / wallStart.y );

                float wallHeightDelta = ( std::floor( this->wallHeight / wallEnd.y ) - wallStartHeight ) / ( wallEnd.x - wallStart.x );
                
                if ( wallStartX < 0 )
                {
                    wallStartHeight += wallHeightDelta * -( wallStartX );
                    wallStartX = 0;
                }

                int wallEndX = std::min<int>( std::floor( wallEnd.x ), this->drawnOn.size() - 1 );

                while ( true )
                {
                    bool wasDrawnOn = hasBeenDrawnOn( wallStartX );
                    int index = 
                        std::min<int>(
                            std::distance(
                                drawnOn.begin(),
                                std::find(
                                    drawnOn.begin() + wallStartX,
                                    drawnOn.end() + wallEndX,
                                    !wasDrawnOn
                                )
                            ),
                            wallEndX
                        );

                    float wallHeight = wallStartHeight + wallHeightDelta * ( index - wallStartX );

                    //aka its hit a section where its turned into a wall
                    if ( wasDrawnOn == false )
                    {
                        wallVertices.append(
                            sf::Vertex(
                                sf::Vector2f(
                                    wallStartX - 1,
                                    ( window.getSize().y + wallStartHeight ) / 2
                                ),
                                sf::Color::Green
                            )
                        );
                        wallVertices.append( 
                            sf::Vertex( 
                                sf::Vector2f( 
                                    index, 
                                    ( window.getSize().y + wallHeight ) / 2
                                ), 
                                sf::Color::Green 
                            ) 
                        );

                        wallVertices.append( 
                            sf::Vertex( 
                                sf::Vector2f(
                                    wallStartX - 1, 
                                    ( window.getSize().y - wallStartHeight ) / 2
                                ), 
                                sf::Color::Green
                            )
                        );
                        wallVertices.append(
                            sf::Vertex( 
                                sf::Vector2f( 
                                    index, 
                                    ( window.getSize().y - wallHeight ) / 2
                                ), 
                                sf::Color::Green 
                            )
                        );

                        std::fill( drawnOn.begin() + wallStartX, drawnOn.begin() + index, true );
                    }

                    if ( index >= wallEndX )
                        return;

                    wallStartX = index;
                    wallStartHeight = wallHeight;
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

                // If it's one or two pixels thin we can stop
                if ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) <= 1 )
                    return;

                drawWallTop( window, wallStart, wallEnd );
            }

            void drawEntity(
                sf::RenderWindow &window, 
                Entity *entity
            )
            {
                sf::Vector2f relativePosition = getCamera().relativePositionOf( sf::Vector2f( entity->getPosition() ) + sf::Vector2f(0.5,0.5) );
                
                if ( relativePosition.y > this->yNear )
                {
                    relativePosition.x /= relativePosition.y;
                    relativePosition.x *= ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 );
                    relativePosition.x += window.getSize().x / 2.f;

                    float radius = entityHeight/relativePosition.y;

                    int entityImageStartX = std::max<int>( 0, std::floor( relativePosition.x - radius/2 ) );
                    float entityTextureStartX = 0;
                    float entityTextureDelta = entity->getTexture()->getSize().x / radius;
                
                    int entityImageEndX = std::min<int>( std::floor( relativePosition.x + radius/2 ), this->drawnOn.size() - 1 );

                    while ( true )
                    {
                        bool wasDrawnOn = hasBeenDrawnOn( entityImageStartX );
                        int index = 
                            std::min<int>(
                                std::distance(
                                    drawnOn.begin(),
                                    std::find(
                                        drawnOn.begin() + entityImageStartX,
                                        drawnOn.end() + entityImageEndX,
                                        !wasDrawnOn
                                    )
                                ),
                                entityImageEndX
                            );
                        float entityTextureEndX = entityTextureStartX + (index - entityImageStartX) * entityTextureDelta;

                        //aka its hit a section where its turned into a wall
                        if ( wasDrawnOn == false )
                        {
                            sf::RectangleShape entityRectangle( {index - entityImageStartX, radius} );
                            entityRectangle.setPosition( { entityImageStartX, ( window.getSize().y - radius ) / 2} );
                            entityRectangle.setTexture( entity->getTexture() );
                            entityRectangle.setTextureRect( sf::IntRect( {entityTextureStartX,0}, {entityTextureEndX - entityTextureStartX,entity->getTexture()->getSize().y} ) );
                            window.draw(entityRectangle);
                        }

                        if ( index >= entityImageEndX )
                            return;

                        entityImageStartX = index;
                        entityTextureStartX = entityTextureEndX;
                    }
                }

            }

            void render( 
                sf::RenderWindow& window, 
                MazeGrid &mazeGrid,
                std::vector<std::vector<std::vector<Entity*>>> entityGrid
            )
            {
                std::queue<sf::Vector2i> cellsToVisitQueue;
                cellsToVisitQueue.push( camera.getPosition() );

                std::vector<std::vector<bool>> visitedCells;
                visitedCells.assign(
                    mazeGrid.getDimensions().x, 
                    std::vector<bool>(
                        mazeGrid.getDimensions().y, 
                        false
                    )
                );

                wallVertices.clear();

                drawnOn.resize( window.getSize().x );
                std::fill(
                    drawnOn.begin(),
                    drawnOn.end(),
                    false
                );


                while ( !cellsToVisitQueue.empty() )
                {
                    sf::Vector2i currentCell = cellsToVisitQueue.front();
                    cellsToVisitQueue.pop();
                    visitedCells[currentCell.x][currentCell.y] = true;

                    if ( !entityGrid.empty() )
                    {
                        std::vector<Entity*> entitiesInCell = entityGrid[currentCell.x][currentCell.y];

                        for ( Entity *entity: entitiesInCell )
                        {
                            drawEntity( window, entity );
                        }
                    }

                    for ( int direction = North; direction < NumberOfDirections; direction++ )
                    {
                        bool isWallInDirection = mazeGrid.getCell( currentCell, (Direction) direction );

                        sf::Vector2f wallStart = 
                            sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) + 
                            rotatePosition({-0.5, 0.5}, (Direction) direction);
                        sf::Vector2f wallEnd = 
                            sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                            rotatePosition({0.5, 0.5}, (Direction) direction);

                        if ( !projectWall( window, wallStart, wallEnd ) )
                            continue;

                        // If theres no space to draw anything why are we going to bother with any other checks
                        if ( !canDrawInRange( window, wallStart.x, wallEnd.x ) )
                            continue;

                        if ( isWallInDirection )
                        {
                            drawWall( window, wallStart, wallEnd );
                        }
                        else
                        {
                            sf::Vector2i connectedCell = 
                                transposePosition( 
                                    currentCell, 
                                    (Direction) direction 
                                );
                            
                            if ( mazeGrid.inBounds( connectedCell ) && 
                                 !visitedCells[connectedCell.x][connectedCell.y] )
                            {
                                cellsToVisitQueue.push( connectedCell );
                            }
                        }
                    }
                }

                window.draw( wallVertices );
            }
    };

#endif /* RENDERER_HPP */