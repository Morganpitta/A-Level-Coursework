#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "Entity/bullet.h++"
#include "Entity/player.h++"
#include "Entity/enemy.h++"
#include "random.h++"

void MazeWars::update( sf::RenderWindow &window )
{
    getCamera().setPosition( getPlayer()->getPosition() );
    getCamera().setDirection( getPlayer()->getDirection() );
    
    for ( std::vector<std::vector<Entity*>> &column: this->entityGrid )
    {
        for ( std::vector<Entity*> &cellEntities: column )
        {
            cellEntities.clear();
        }
    }

    for ( std::pair<Id, Entity*> idEntityPair: this->entities )
    {
        Entity *entity = idEntityPair.second;
        if ( !entity->isDead() )
        {
            entity->update( *this );
            sf::Vector2i position = entity->getPosition();
            entityGrid[position.x][position.y].push_back( entity );
        }
    }

    cleanUpEntities();
}