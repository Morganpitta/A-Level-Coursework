#include "Entity/player.h++"

namespace MazeWars
{
    Player::Player( sf::Vector2i position ): Entity( position )
    {
        this->type = PlayerType;
    }
}