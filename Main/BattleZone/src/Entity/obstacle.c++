#include "Entity/obstacle.h++"

Obstacle::Obstacle( sf::Vector2f position ): Entity( position )
{
    this->type = ObstacleType;
    this->model = &obstacleModel;
}