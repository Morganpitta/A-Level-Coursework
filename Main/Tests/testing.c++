#include "renderer.h++"
#include "Entity/entity.h++"

void Renderer::render(
    sf::RenderWindow& window,
    MazeGrid &mazeGrid,
    const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
    Id playerId
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