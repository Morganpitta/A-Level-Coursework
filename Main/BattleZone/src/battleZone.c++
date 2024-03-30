#include "battleZone.h++"
#include "Entity/entity.h++"
#include "Entity/player.h++"
#include "Entity/bullet.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"
#include "random.h++"
#include "draw.h++"
#include <iostream>

BattleZone::BattleZone( sf::Vector2u displaySize ): renderer(displaySize)
{
    this->nextId = 0;

    this->playerId = 
        addEntity(
            new Player( { 0,0 } ) 
        );
        
    this->playerKills = 0;
}

BattleZone::~BattleZone()
{
    for ( std::pair<Id, Entity*> idEntityPair : this->entities )
    {
        delete idEntityPair.second;
    }

    this->entities.clear();
}

Camera &BattleZone::getCamera() { return this->renderer.getCamera(); }

Entity *BattleZone::getEntity( Id id ) { return this->entities[id]; }

const std::map<Id, Entity*> &BattleZone::getEntities() { return this->entities; }

Entity *BattleZone::getPlayer() { return getEntity( this->playerId ); }

Id BattleZone::addEntity( Entity* entity )
{
    Id entityId = nextId++;
    this->entities[entityId] = entity;
    entity->setId( entityId );
    return entityId;
}

void BattleZone::addPlayerKill() { this->playerKills++; }

bool BattleZone::canMoveInDirection( Entity *entity, float distance )
{
    std::vector<Entity*> collidingEntities = 
        Entity::getColliding(
            entity, 
            distance * get2DUnitVector( getPlayer()->getRotation() ), 
            getEntities(),
            [ this ]( Entity *entity ) { return entity->getType() != BulletType; } 
        );
    
    return collidingEntities.empty();
}

void BattleZone::cleanUpEntities()
{
    for ( auto iterator = this->entities.begin(); iterator != this->entities.end(); )
    {
        Entity *entity = (*iterator).second;
        sf::Vector2f relativePositionToPlayer = entity->getPosition() - getPlayer()->getPosition();
        float distanceToPlayer = vectorLength( relativePositionToPlayer );
        
        if ( ( entity->isDead() || distanceToPlayer > 30 ) && entity->getType() != PlayerType )
        {
            delete (*iterator).second;
            iterator = this->entities.erase( iterator );
        }
        else
        {
            iterator++;
        }
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
    }
}

void BattleZone::update( sf::RenderWindow &window )
{
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
        getPlayer()->turnLeft( M_PI/100 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
        getPlayer()->turnRight( M_PI/100 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) && canMoveInDirection( getPlayer(), 0.08 ) )
        getPlayer()->moveForward( 0.08 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) && canMoveInDirection( getPlayer(), -0.08 ) )
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

void BattleZone::drawGUI( sf::RenderWindow &window )
{
    renderer.drawCrosshair( window );

    sf::Text text("Health:"+std::to_string(getPlayer()->getHealth())+"\nScore:"+std::to_string(this->playerKills),gameFont,40);
    text.setOrigin( {text.getGlobalBounds().width/2.f,0} );
    text.setPosition( {(3*renderer.getDisplaySize().x)/4.f, 10} );
    window.draw( text );
}

void BattleZone::render( sf::RenderWindow &window )
{
    renderer.clear();
    
    renderer.drawBackground( window );

    for ( std::pair<Id, Entity*> idEntityPair: entities )
    {
        if ( idEntityPair.first != getPlayer()->getId() )
            renderer.drawEntity( idEntityPair.second );
    }

    drawGUI( window );

    renderer.display( window );
}