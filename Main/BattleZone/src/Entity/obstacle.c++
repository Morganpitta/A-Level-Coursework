#include "Entity/obstacle.h++"

Obstacle::Obstacle( sf::Vector2f position ): Entity( position )
{
    this->type = ObstacleType;
    this->model = &obstacleModel;
    this->health = 1000;
}

CollisionRect Obstacle::getCollisionRect() const
{
    return CollisionRect( getPosition(), {1,1}, getRotation() );
}