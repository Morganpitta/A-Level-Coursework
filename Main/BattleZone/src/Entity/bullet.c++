#include "Entity/bullet.h++"
#include "battleZone.h++"

Bullet::Bullet( Id ownerId, sf::Vector2f position, float rotation ): Entity( position )
{
    this->type = BulletType;
    this->model = &bulletModel;
    this->ownerId = ownerId;
    setRotation( rotation );
}

void Bullet::update( BattleZone &game )
{
    if ( isColliding( 
            this, 
            0.1f * get2DUnitVector( getRotation() ), 
            game.getEntities(), 
            [ this ]( Entity *entity) { return entity->getId() != this->ownerId; }
        ) )
    {
        kill();
        return;
    }

    moveForward( 0.1 );
}