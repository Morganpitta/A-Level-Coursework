#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "Entity/bullet.h++"
#include "Entity/player.h++"
#include "Entity/enemy.h++"
#include "random.h++"


MazeWars::MazeWars( sf::Vector2u displaySize, sf::Vector2i dimensions ): renderer(displaySize), mazeGrid( dimensions )
{
    this->nextId = 0;
    generateMazeDepthFirst( mazeGrid, 1 );
    entityGrid.resize(
        dimensions.x,
        std::vector<std::vector<Entity*>>(
            dimensions.y,
            std::vector<Entity*>()
        )
    );

    this->playerId = 
        addEntity(
            new Player( 
                {
                    dimensions.x/2,
                    dimensions.y/2
                }
            ) 
        );
}

Camera &MazeWars::getCamera()
{
    return this->renderer.getCamera();
}

MazeGrid &MazeWars::getMaze()
{
    return this->mazeGrid;
}

Entity *MazeWars::getEntity( Id id )
{
    return this->entities[id];
}

Entity *MazeWars::getPlayer()
{
    return getEntity( this->playerId );
}

std::vector<Id> MazeWars::getEntitiesAtLocation( sf::Vector2i position ) const
{
    // I need to convert arrays of Id's to arrays of pointers
    std::vector<Id> entities;

    for ( const Entity* entity: entityGrid[position.x][position.y] )
    {
        entities.push_back( entity->getId() );
    }

    return entities;
}

bool MazeWars::playerCanMove( Direction direction )
{
    return getMaze().getCell( 
            getPlayer()->getPosition(),
            direction
        ) != true;
}

Id MazeWars::addEntity( Entity* entity )
{
    Id entityId = nextId++;
    this->entities[entityId] = entity;
    entity->setId( entityId );
    return entityId;
}