#include "Entity/bullet.h++"
#include "battleZone.h++"

Bullet::Bullet( Id ownerId, sf::Vector2f position, float rotation ): Entity( position )
{
    this->type = BulletType;
    this->model = &bulletModel;
    this->ownerId = ownerId;
    this->radius = 0.15;
    setRotation( rotation );
}

Id Bullet::getOwnerId() const
{
    return this->ownerId;
}

void Bullet::update( BattleZone &game )
{
    std::vector<Entity *> collidingEntities = 
        getColliding( 
            this, 
            0.1f * get2DUnitVector( getRotation() ), 
            game.getEntities(), 
            [ this ]( Entity *entity) { 
                if ( entity->getType() == BulletType )
                    return static_cast<Bullet*>( entity )->getOwnerId() != getOwnerId();
                return entity->getId() != getOwnerId();
            }
        );
    if ( !collidingEntities.empty() )
    {
        for ( Entity* entity: collidingEntities )
        {
            entity->damage( 1 );
        }
        kill();
        return;
    }

    moveForward( 0.1 );
}