#include "Entity/player.h++"

Player::Player( sf::Vector2i position ): Entity( position )
{
    this->type = PlayerType;
}