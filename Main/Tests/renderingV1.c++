#include "renderer.h++"
#include "Entity/entity.h++"

void Renderer::drawWallVertical(
    sf::Vector2f position
)
{
    if ( onScreen( position.x ) )
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
    }
}

void Renderer::drawWallHorizontals(
    sf::Vector2f &wallStart,
    sf::Vector2f &wallEnd
)
{
    float wallStartHeight = std::floor( this->wallHeight / wallStart.y );
    float wallEndHeight = std::floor( this->wallHeight / wallEnd.y );

    appendLineToArray(
        wallVertices,
        sf::Vector2f(
            wallStart.x,
            ( getDisplaySize().y + std::floor( wallStartHeight ) ) / 2
        ),
        sf::Vector2f(
            wallEnd.x,
            ( getDisplaySize().y + std::floor( wallEndHeight ) ) / 2
        ),
        sf::Color::Green
    );

    appendLineToArray(
        wallVertices,
        sf::Vector2f(
            wallStart.x,
            ( getDisplaySize().y - std::floor( wallStartHeight ) ) / 2
        ),
        sf::Vector2f(
            wallEnd.x,
            ( getDisplaySize().y - std::floor( wallEndHeight ) ) / 2
        ),
        sf::Color::Green
    );
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

void Renderer::render(
    sf::RenderWindow& window,
    MazeGrid &mazeGrid
)
{
    std::queue<sf::Vector2i> cellsToVisit;
    cellsToVisit.push( camera.getPosition() );

    std::vector<std::vector<bool>> visitedCells;
    visitedCells.assign(
        mazeGrid.getDimensions().x,
        std::vector<bool>(
            mazeGrid.getDimensions().y, 
            false
        )
    );

    wallVertices.clear();

    while ( !cellsToVisit.empty() )
    {
        // Dequeue the first item and store it. Mark the current cell as visited
        sf::Vector2i currentCell = cellsToVisit.front(); cellsToVisit.pop();
        visitedCells[currentCell.x][currentCell.y] = true;

        forEachDirection( direction )
        {
            bool isWallInDirection = mazeGrid.getCell( currentCell, (Direction) direction );

            sf::Vector2f wallStart = 
                sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) + 
                rotatePosition({-0.5, 0.5}, (Direction) direction);
            sf::Vector2f wallEnd = 
                sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                rotatePosition({0.5, 0.5}, (Direction) direction);

            if ( !projectLine( wallStart, wallEnd ) )
                continue;

            if ( isWallInDirection )
            {
                // If there's a wall, just draw it and continue with next loop.
                drawWall(  wallStart, wallEnd );
            }
            else
            {
                // Else try to add the connected cell to the cellsToVisit
                sf::Vector2i connectedCell = 
                    transposePosition( 
                        currentCell, 
                        (Direction) direction
                    );
                
                if ( mazeGrid.inBounds( connectedCell ) && 
                     !visitedCells[connectedCell.x][connectedCell.y] )
                {
                    cellsToVisit.push( connectedCell );
                }
            }
        }
    }

    window.draw( wallVertices );
}