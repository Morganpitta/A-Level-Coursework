#include "Entity/bullet.h++"
#include "battleZone.h++"

Bullet::Bullet( sf::Vector2f position, float rotation ): Entity( position )
{
    this->type = BulletType;
    this->model = &bulletModel;
    setRotation( rotation );
}

void Bullet::update( BattleZone &game )
{
    moveForward( 0.1 );
}