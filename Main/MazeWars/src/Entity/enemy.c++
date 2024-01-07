#include "Entity\enemy.h++"
#include "mazeWars.h++"

Enemy::Enemy( sf::Vector2i position ): Entity( position )
{
    this->type = EnemyType;
    this->texture = &TriangleTexture;
    this->movementCoolDown = 0;
}

void Enemy::update( MazeWars &game )
{
    if ( this->movementCoolDown > 0 )
    {
        this->movementCoolDown--;
        return;
    }

    std::vector<sf::Vector2i> path = PathSolver.solve( game.getMaze(), getPosition(), game.getPlayer()->getPosition() );

    if ( !path.empty() )
    {
        Direction direction = getDirectionOf( path[0], path[1] );
        if ( direction != getDirection() )
        {
            // If the relative direction is west, then you need to turn left
            // if it's to your right or behind you, you need to turn right
            if ( direction - getDirection() == West )
                turnLeft();
            else
                turnRight();
        }
        else 
        { 
            moveForward();
            this->movementCoolDown = 120/path.size();
        }
    }
}