#include "Entity/entity.h++"
#include "battleZone.h++"
#include "file.h++"

const Id NullId = -1;

Model3D tankModel;
Model3D obstacleModel;
Model3D bulletModel;

bool loadEntityAssets()
{
    setWorkingDirectoryToDefault();

    tankModel.importFromFile( "BattleZone/tank.obj" );
    obstacleModel.importFromFile( "BattleZone/pyramid.obj" );
    bulletModel.importFromFile( "BattleZone/bullet.obj" );

    return true;
}

Entity::Entity( sf::Vector2f position )
{
    this->position = position;
    this->rotation = 0;
    this->health = 1;
    this->id = NullId;
    this->dead = false;
    this->type = NoType;
    this->model = nullptr;
}

sf::Vector2f Entity::getPosition() const { return this->position; }

float Entity::getRotation() const { return this->rotation; }

int Entity::getHealth() const { return this->health; }

Id Entity::getId() const { return this->id; }

bool Entity::isDead() const { return this->dead; }

EntityType Entity::getType() const { return this->type; }

Model3D *Entity::getModel() { return this->model; }

CollisionRect Entity::getCollisionRect() const
{
    return CollisionRect( getPosition(), {0,0}, getRotation() );
}

void Entity::setPosition( sf::Vector2f position ) { this->position = position; }

void Entity::setRotation( float rotation ) { this->rotation = normaliseAngle( rotation ); }

void Entity::setHealth( int health ) { this->health = health; }

void Entity::setId( Id id ) { this->id = id; }

void Entity::moveForward( float distance )
{
    setPosition(
        getPosition() + distance * get2DUnitVector( getRotation() )
    );
}

void Entity::turnLeft( float angle )
{
    setRotation( getRotation() - angle );
}

void Entity::turnRight( float angle )
{
    setRotation( getRotation() + angle );
}

void Entity::damage( int amount )
{
    setHealth( std::max( getHealth() - amount, 0 ) );

    if ( getHealth() <= 0 )
        kill();
}

void Entity::kill()
{
    this->dead = true;
}

sf::Vector2f Entity::relativePositionOf( sf::Vector2f position )
{
    return rotatePosition( 
        position - getPosition(),
        normaliseAngle( -getRotation() )
    );
}

std::vector<Entity*> Entity::getColliding( Entity *entity, sf::Vector2f offset, const std::map<Id,Entity*> &entities, std::function<bool(Entity*)> filter )
{
    CollisionRect collisionRect = entity->getCollisionRect();
    collisionRect.setCenter( collisionRect.getCenter() + offset );
    
    std::vector<Entity*> collidingEntities;
    for ( const std::pair<const Id, Entity*> &idEntityPair: entities )
    {
        if ( !idEntityPair.second->isDead() && idEntityPair.first != entity->getId() && filter( idEntityPair.second ) )
        {
            if ( CollisionRect::isColliding( collisionRect, idEntityPair.second->getCollisionRect() ) )
            {
                collidingEntities.push_back( idEntityPair.second );
            }
        }
    }

    return collidingEntities;
}

void Entity::update( BattleZone &game )
{

}