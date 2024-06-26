#include "Entity/entity.h++"
#include "mazeWars.h++"

namespace MazeWars
{
    const Id NullId = -1;
    sf::Texture EnemyTexture;
    sf::Texture BulletTexture;

    bool loadEntityAssets()
    {
        setWorkingDirectoryToDefault();

        if ( !EnemyTexture.loadFromFile( "MazeWars/eye.png" ) )
            return false;

        if ( !BulletTexture.loadFromFile( "MazeWars/circle.png" ) )
            return false;

        return true;
    }

    Entity::Entity( sf::Vector2i position )
    {
        this->position = position;
        this->direction = North;
        this->health = 1;
        this->id = NullId;
        this->dead = false;
        this->type = NoType;
        this->texture = nullptr;
        this->size = 75;
    }

    sf::Vector2i Entity::getPosition() const
    {
        return this->position;
    }

    Direction Entity::getDirection() const { return this->direction; }

    int Entity::getHealth() const { return this->health; }

    Id Entity::getId() const { return this->id; }

    bool Entity::isDead() const { return this->dead; }

    EntityType Entity::getType() const { return this->type; }

    sf::Texture *Entity::getTexture() const { return this->texture; }

    float Entity::getSize() const { return this->size; }

    void Entity::setPosition( sf::Vector2i position ) { this->position = position; }

    void Entity::setDirection( Direction direction ) { this->direction = direction; }

    void Entity::setHealth( int health ) { this->health = health; }

    void Entity::setId( Id id ) { this->id = id; }

    void Entity::moveForward()
    {
        setPosition( 
            transposePosition( 
                getPosition(), 
                getDirection() 
            )
        );
    }

    void Entity::moveBackward()
    {
        setPosition( 
            transposePosition( 
                getPosition(), 
                reverseDirection( getDirection() ) 
            )
        );
    }

    void Entity::turnLeft()
    {
        setDirection( normaliseDirection( int(getDirection()) - 1 ) );
    }

    void Entity::turnRight()
    {
        setDirection( normaliseDirection( int(getDirection()) + 1 ) );
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

    sf::Vector2i Entity::relativePositionOf( sf::Vector2i position )
    {
        return sf::Vector2i( rotatePosition( 
            sf::Vector2f( position - getPosition() ),
            normaliseDirection( -getDirection() )
        ) );
    }

    void Entity::update( MazeWarsGame &game ) {}
}