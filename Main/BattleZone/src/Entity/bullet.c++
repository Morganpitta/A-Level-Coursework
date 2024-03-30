#include "Entity/bullet.h++"
#include "battleZone.h++"

namespace BattleZone
{
    Bullet::Bullet( Id ownerId, sf::Vector2f position, float rotation ): Entity( position )
    {
        this->type = BulletType;
        this->model = &bulletModel;
        this->ownerId = ownerId;
        setRotation( rotation );
    }

    Id Bullet::getOwnerId() const
    {
        return this->ownerId;
    }

    CollisionRect Bullet::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {0.1,0.3}, getRotation() );
    }

    void Bullet::update( BattleZoneGame &game )
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
                if ( entity->isDead() && entity->getType() == TankType && getOwnerId() == game.getPlayer()->getId() )
                    game.addPlayerKill();
            }
            kill();
            return;
        }

        moveForward( 0.1 );
    }
}