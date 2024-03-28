#include "Entity/player.h++"

Player::Player( sf::Vector2f position ): Entity( position )
{
    this->type = PlayerType;
    this->health = 10;
}

CollisionRect Player::getCollisionRect() const
{
    return CollisionRect( getPosition(), {1,1}, getRotation() );
}