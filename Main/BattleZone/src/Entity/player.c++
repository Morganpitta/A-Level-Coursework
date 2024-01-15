#include "Entity/player.h++"

Player::Player( sf::Vector2f position ): Entity( position )
{
    this->type = PlayerType;
    this->radius = 0.7;
    this->health = 10;
}