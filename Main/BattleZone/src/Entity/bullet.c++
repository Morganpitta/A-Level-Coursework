#include "Entity/bullet.h++"
#include "battleZone.h++"

Bullet::Bullet( sf::Vector2f position, float rotation ): Entity( position )
{
    this->type = BulletType;
    this->model = nullptr;
    setRotation( rotation );
}

void Bullet::update( BattleZone &game )
{

}