#include "battleZone.h++"
#include "Entity/entity.h++"
#include "Entity/player.h++"
#include "Entity/bullet.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "random.h++"
#include <iostream>

BattleZone::BattleZone( sf::Vector2u displaySize ): renderer(displaySize)
{
    this->nextId = 0;

    this->playerId = 
        addEntity(
            new Player( { 0,0 } ) 
        );
}

Camera &BattleZone::getCamera()
{
    return this->renderer.getCamera();
}

Entity *BattleZone::getEntity( Id id )
{
    return this->entities[id];
}

const std::map<Id, Entity*> &BattleZone::getEntities()
{
    return this->entities;
}

Entity *BattleZone::getPlayer()
{
    return getEntity( this->playerId );
}

Id BattleZone::addEntity( Entity* entity )
{
    Id entityId = nextId++;
    this->entities[entityId] = entity;
    entity->setId( entityId );
    return entityId;
}

void BattleZone::cleanUpEntities()
{
    for ( auto iterator = this->entities.begin(); iterator != this->entities.end(); )
    {
        Entity *entity = (*iterator).second;
        sf::Vector2f relativePositionToPlayer = entity->getPosition() - getPlayer()->getPosition();
        float distanceToPlayer = sqrt( relativePositionToPlayer.x * relativePositionToPlayer.x + relativePositionToPlayer.y * relativePositionToPlayer.y );
        if ( ( entity->isDead() || distanceToPlayer > 30 ) && entity->getType() != PlayerType )
            iterator = this->entities.erase( iterator );
        else
            iterator++;
    }
}

void BattleZone::attemptToSpawnEntities()
{
    int numberOfTanks =
        std::count_if(
            this->entities.begin(),
            this->entities.end(),
            []( const std::pair<Id, Entity*> idEntityPair )
            {
                return idEntityPair.second->getType() == TankType;
            }
        );

    while ( numberOfTanks < 4 )
    {
        float spawnAngle = randomFloat( 0, 2 * M_PI );
        sf::Vector2f spawnLocation = getPlayer()->getPosition() + 
            20.f * get2DUnitVector( spawnAngle );
        addEntity( new Tank( spawnLocation ) );
        numberOfTanks++;
    }

    int numberOfObstacles = 
        std::count_if(
            this->entities.begin(),
            this->entities.end(),
            []( const std::pair<Id, Entity*> idEntityPair )
            {
                return idEntityPair.second->getType() == ObstacleType;
            }
        );

    while ( numberOfObstacles < 10 )
    {
        float spawnAngle = randomFloat( 0, 2 * M_PI );
        sf::Vector2f spawnLocation = getPlayer()->getPosition() + 
            20.f * get2DUnitVector( spawnAngle );
        addEntity( new Obstacle( spawnLocation ) );
        numberOfObstacles++;
    }
}

void BattleZone::handleInput( sf::Event &event )
{
    if ( event.type == sf::Event::KeyPressed )
    {
        if ( event.key.code == sf::Keyboard::Space )
            addEntity( new Bullet( getPlayer()->getId(), getPlayer()->getPosition(), getPlayer()->getRotation() ) );
        if ( event.key.code == sf::Keyboard::P )
            std::cout<<"REEEE";
    }
}

void BattleZone::update( sf::RenderWindow &window )
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
        getPlayer()->turnLeft( M_PI/100 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
        getPlayer()->turnRight( M_PI/100 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) &&
         Entity::getColliding(
            getPlayer(), 
            0.08f * get2DUnitVector( getPlayer()->getRotation() ), 
            getEntities(),
            [ this ]( Entity *entity) { return entity->getType() != BulletType; }
         ).empty() )
        getPlayer()->moveForward( 0.08 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) &&
         Entity::getColliding(
            getPlayer(), 
            -0.08f * get2DUnitVector( getPlayer()->getRotation() ), 
            getEntities(),
            [ this ]( Entity *entity) { return entity->getType() != BulletType; } 
         ).empty() )
        getPlayer()->moveForward( -0.08 );

    getCamera().setPosition( { getPlayer()->getPosition().x, 0.85, getPlayer()->getPosition().y } );
    getCamera().setYaw( getPlayer()->getRotation() );

    for ( std::pair<Id, Entity*> idEntityPair: entities )
    {
        if ( !idEntityPair.second->isDead() )
        {
            idEntityPair.second->update( *this );
        }
    }

    cleanUpEntities();
    attemptToSpawnEntities();
}

void BattleZone::render( sf::RenderWindow &window )
{
    renderer.clear();
    
    // Things will be renderered at a later date

    renderer.drawBackground( window );

    for ( std::pair<Id, Entity*> idEntityPair: entities )
    {
        if ( idEntityPair.first != getPlayer()->getId() )
            renderer.drawEntity( window, idEntityPair.second );
    }

    renderer.display( window );
}