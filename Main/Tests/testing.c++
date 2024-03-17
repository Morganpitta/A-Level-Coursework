#include "renderer.h++"
#include "Entity/entity.h++"

void Renderer::render(
    sf::RenderWindow& window,
    MazeGrid &mazeGrid,
    const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
    Id playerId
)
{
    this->entityRectangles.clear();

    // Code removed for brevity 

    while ( !cellsToVisit.empty() )
    {
        sf::Vector2i currentCell = cellsToVisit.front(); cellsToVisit.pop();
        visitedCells[currentCell.x][currentCell.y] = true;

        std::vector<Entity*> entitiesInCell = entityGrid[currentCell.x][currentCell.y];

        for ( Entity *entity: entitiesInCell )
        {
            if ( entity->getId() != playerId && !entity->isDead() )
                drawEntity( entity );
        }

        forEachDirection( direction )
    }
}