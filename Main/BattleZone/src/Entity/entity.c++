#include "Entity/entity.h++"
#include "battleZone.h++"
#include "file.h++"

const Id NullId = -1;

Model3D tankModel;
Model3D obstacleModel;

bool loadEntityAssets()
{
    setWorkingDirectoryToDefault();

    tankModel.importFromFile( "BattleZone/tank.obj" );
    obstacleModel.importFromFile( "BattleZone/obstacle.obj" );

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

sf::Vector2f Entity::getPosition() const
{
    return this->position;
}

float Entity::getRotation() const
{
    return this->rotation;
}

int Entity::getHealth() const
{
    return this->health;
}

Id Entity::getId() const
{
    return this->id;
}

bool Entity::isDead() const
{
    return this->dead;
}

EntityType Entity::getType() const
{
    return this->type;
}

Model3D *Entity::getModel()
{
    return this->model;
}

void Entity::setPosition( sf::Vector2f position )
{
    this->position = position;
}

void Entity::setRotation( float rotation )
{
    this->rotation = normaliseAngle( rotation );
}

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

sf::Vector2f Entity::relativePositionOf( sf::Vector2f position )
{
    return rotatePosition( 
        position - getPosition(),
        normaliseAngle( -getRotation() )
    );
}

void Entity::setHealth( int health )
{
    this->health = health;
}

void Entity::damage( int amount )
{
    setHealth( std::max( getHealth() - amount, 0 ) );

    if ( getHealth() <= 0 )
        kill();
}

void Entity::setId( Id id )
{
    this->id = id;
}

void Entity::kill()
{
    this->dead = true;
}

void Entity::update( BattleZone &game )
{

}