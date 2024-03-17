#include "renderer.h++"
#include "Entity/entity.h++"

bool Renderer::hasBeenDrawnOn( int xIndex ) const
{
    assert(
        xIndex >= 0 &&
        std::size_t(xIndex) < drawnOn.size(),
        "Index out of range"
    );

    return this->drawnOn[xIndex];
}

bool Renderer::canDrawInRange(
    float startIndex,
    float endIndex
) const
{
    assert(
        startIndex <= endIndex,
        "Start index must be less than the end index"
    );
    for ( int index = std::max( 0.f, std::floor( startIndex ) ); index <= std::min( std::floor( endIndex ), getDisplaySize().x - 1.f ); index++ )
    {
        if ( !hasBeenDrawnOn(index) )
            return true;
    }

    return false;
}

void Renderer::setHasBeenDrawnOn(
    int xIndex,
    bool value
)
{
    assert(
        xIndex >= 0 &&
        std::size_t(xIndex) < drawnOn.size(),
        "Index out of range"
    );

    this->drawnOn[xIndex] = value;
}

Renderer::Renderer( sf::Vector2u displaySize ): displaySize( displaySize ), 
                                                yNear(0.1),
                                                wallHeight(300),
                                                camera(), 
                                                wallVertices( sf::PrimitiveType::Lines )
{

}

Camera &Renderer::getCamera()
{
    return this->camera;
}

float Renderer::getYNear() const
{
    return this->yNear;
}

sf::Vector2u Renderer::getDisplaySize() const
{
    return this->displaySize;
}

bool Renderer::onScreen( float xValue ) const
{
    return 0 <= xValue && xValue < getDisplaySize().x;
}

sf::Vector2f Renderer::clipLineToNearPlane( sf::Vector2f lineStart, sf::Vector2f lineEnd )
{
    // A linear interpolation
    float delta = ( lineStart.y - getYNear() ) / ( lineStart.y - lineEnd.y );
    
    return { lineStart.x + ( lineEnd.x - lineStart.x ) * delta, getYNear() };
}

bool Renderer::projectPoint(
    sf::Vector2f &position,
    float &size
)
{
    //Getting relative position
    position = getCamera().relativePositionOf( position );

    // Clip near
    if ( position.y < getYNear() )
        return false;
    
    // Divide by distance to camera
    position.x /= position.y;

    // Stretch to match screen size and center on screen
    position.x *= ( getDisplaySize().x / 2 ) / tan( camera.getFov() / 2 );
    position.x += getDisplaySize().x / 2.f;

    size /= position.y * 2;

    // Test if off screen
    if ( position.x + size < 0  || position.x - size > getDisplaySize().x )
        return false;

    return true;
}

bool Renderer::projectLine(
    sf::Vector2f &lineStart,
    sf::Vector2f &lineEnd
)
{
    //Getting relative position
    lineStart = getCamera().relativePositionOf( lineStart );
    lineEnd = getCamera().relativePositionOf( lineEnd );

    // Clip near
    if ( lineStart.y < getYNear() && lineEnd.y < getYNear() )
        return false;
    else if ( lineStart.y < getYNear() )
    {
        lineStart = clipLineToNearPlane( lineStart, lineEnd );
    }
    else if ( lineEnd.y < getYNear() )
    {
        lineEnd = clipLineToNearPlane( lineStart, lineEnd );
    }

    // Divide by distance to camera
    lineStart.x /= lineStart.y;
    lineEnd.x /= lineEnd.y;

    // Making sure it's start to end not end to start
    if ( lineStart.x > lineEnd.x )
    {
        std::swap( lineStart, lineEnd );
    }

    // Stretch to match screen size and center on screen
    lineStart.x *= ( getDisplaySize().x / 2 ) / tan( camera.getFov() / 2 );
    lineStart.x += getDisplaySize().x / 2.f;
    lineEnd.x *= ( getDisplaySize().x / 2 ) / tan( camera.getFov() / 2 );
    lineEnd.x += getDisplaySize().x / 2.f;

    // Test if off screen
    if ( lineEnd.x < 0  || lineStart.x > getDisplaySize().x )
        return false;

    return true;
}

void Renderer::drawWallVertical(
    sf::Vector2f position
)
{
    if ( onScreen( position.x ) &&
            !hasBeenDrawnOn( std::floor( position.x ) ) )
    {
        float wallHeight = std::floor( this->wallHeight / position.y );
        
        appendLineToArray(
            wallVertices,
            sf::Vector2f(
                std::floor(position.x),
                ( getDisplaySize().y + wallHeight ) / 2
            ),
            sf::Vector2f(
                std::floor(position.x),
                ( getDisplaySize().y - wallHeight ) / 2
            ),
            sf::Color::Green
        );

        setHasBeenDrawnOn( position.x, true );
    }
}

void Renderer::drawWallHorizontals(
    sf::Vector2f &wallStart,
    sf::Vector2f &wallEnd
)
{
    int wallStartX = std::floor( wallStart.x + 1 );
    float wallStartHeight = std::floor( this->wallHeight / wallStart.y );

    float wallHeightDelta = ( std::floor( this->wallHeight / wallEnd.y ) - wallStartHeight ) / ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) );
    
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

        float wallHeight = wallStartHeight + wallHeightDelta * ( index - wallStartX + 1 );

        //aka its hit a section where its turned into a wall
        if ( wasDrawnOn == false )
        {
            appendLineToArray(
                wallVertices,
                sf::Vector2f(
                    wallStartX - 1,
                    ( getDisplaySize().y + std::floor( wallStartHeight ) ) / 2
                ),
                sf::Vector2f(
                    index,
                    ( getDisplaySize().y + std::floor( wallHeight ) ) / 2
                ),
                sf::Color::Green
            );

            appendLineToArray(
                wallVertices,
                sf::Vector2f(
                    wallStartX - 1,
                    ( getDisplaySize().y - std::floor( wallStartHeight ) ) / 2
                ),
                sf::Vector2f(
                    index,
                    ( getDisplaySize().y - std::floor( wallHeight ) ) / 2
                ),
                sf::Color::Green
            );
            
            std::fill( drawnOn.begin() + wallStartX, drawnOn.begin() + index, true );
        }

        if ( index >= wallEndX )
            return;

        wallStartX = index;
        wallStartHeight = wallHeight;
    }
}

void Renderer::drawWall(
    sf::Vector2f &wallStart,
    sf::Vector2f &wallEnd
)
{
    drawWallVertical(  wallStart );

    drawWallVertical( wallEnd );

    // If it's one or two pixels thin we can stop
    if ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) <= 1 )
        return;

    drawWallHorizontals( wallStart, wallEnd );
}

void Renderer::drawEntity(
    Entity *entity
)
{
    sf::Vector2f position =
        sf::Vector2f( entity->getPosition() ) +
        sf::Vector2f(0.5,0.5);

    float size = entity->getSize();

    if ( projectPoint( position, size ) )
    {
        int entityImageStartX = std::floor( position.x - size );
        float entityTextureStartX = 0;
        float entityTextureDelta = entity->getTexture()->getSize().x / ( size * 2 );

        if ( entityImageStartX < 0 )
        {
            entityTextureStartX += -( entityImageStartX ) * entityTextureDelta;
            entityImageStartX = 0;
        }
    
        int entityImageEndX = std::min<int>( std::floor( position.x + size ), this->drawnOn.size() - 1 );

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

            if ( wasDrawnOn == false )
            {
                sf::RectangleShape entityRectangle(
                    {
                        float( index -  entityImageStartX ),
                        size * 2
                    }
                );
                entityRectangle.setPosition(
                    {
                        float( entityImageStartX ),
                        ( getDisplaySize().y ) / 2 - size
                    }
                );
                entityRectangle.setTexture( entity->getTexture() );
                entityRectangle.setTextureRect(
                    sf::IntRect(
                        {
                            int( entityTextureStartX ),
                            0
                        },
                        {
                            int( entityTextureEndX - entityTextureStartX ),
                            int( entity->getTexture()->getSize().y )
                        }
                    )
                );
                this->entityRectangles.push_back(entityRectangle);
            }

            if ( index >= entityImageEndX )
                return;

            entityImageStartX = index;
            entityTextureStartX = entityTextureEndX;
        }
    }
}

void Renderer::render(
    sf::RenderWindow& window,
    MazeGrid &mazeGrid,
    const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
    Id playerId
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
    this->entityRectangles.clear();

    drawnOn.resize( getDisplaySize().x );
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

        std::vector<Entity*> entitiesInCell = entityGrid[currentCell.x][currentCell.y];

        for ( Entity *entity: entitiesInCell )
        {
            if ( entity->getId() != playerId && !entity->isDead() )
                drawEntity( entity );
        }

        forEachDirection( direction )
        {
            bool isWallInDirection = mazeGrid.getCell( currentCell, direction );

            sf::Vector2f wallStart =
                sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                rotatePosition({-0.5, 0.5}, direction);
            sf::Vector2f wallEnd =
                sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                rotatePosition({0.5, 0.5}, direction);

            if ( !projectLine( wallStart, wallEnd ) )
                continue;

            // If theres no space to draw anything why are we going to bother with any other checks
            if ( !canDrawInRange( wallStart.x, wallEnd.x ) )
                continue;

            if ( isWallInDirection )
            {
                drawWall( wallStart, wallEnd );
            }
            else
            {
                sf::Vector2i connectedCell =
                    transposePosition(
                        currentCell,
                        direction
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
    std::reverse( this->entityRectangles.begin(), this->entityRectangles.end() );
    for ( sf::RectangleShape &entityRectangle: this->entityRectangles )
    {
        window.draw( entityRectangle );
    }
}