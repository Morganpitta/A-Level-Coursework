#include "renderer.h++"
#include "Entity/entity.h++"

void Renderer::drawWallVertical(
    sf::Vector2f position
)
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
    wallVertices.clear();

    for ( int xIndex = 0; xIndex < mazeGrid.getDimensions().x; xIndex++ )
    {
        for ( int yIndex = 0; yIndex < mazeGrid.getDimensions().x; yIndex++ )
        {
            sf::Vector2i currentCell = { xIndex, yIndex };
            forEachDirection( direction )
            {
                bool isWallInDirection = mazeGrid.getCell( currentCell, direction );

                if ( isWallInDirection )
                {
                    sf::Vector2f wallStart =
                        sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                        rotatePosition({-0.5, 0.5}, direction);
                    sf::Vector2f wallEnd =
                        sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                        rotatePosition({0.5, 0.5}, direction);

                    if ( !projectLine( wallStart, wallEnd ) )
                        continue;

                    drawWall( wallStart, wallEnd );
                }
            }
        }
    }

    window.draw( wallVertices );
}