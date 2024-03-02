#include "Entity/enemy.h++"
#include "mazeWars.h++"
#include "Entity/bullet.h++"

Enemy::Enemy( sf::Vector2i position ): Entity( position )
{
    this->type = EnemyType;
    this->texture = &EnemyTexture;
    this->movementCooldown = 0;
    this->reactionCooldown = 60;
}

void Enemy::update( MazeWars &game )
{
    if ( isDirectlyInFront( game.getMaze(), this, game.getPlayer()->getPosition() ) )
    {
        if ( this->reactionCooldown > 0 )
        {
            this->reactionCooldown--;
            this->movementCooldown = 10;
        }
        else
        {
            game.addEntity( new Bullet( getId(), getPosition(), getDirection() ) );
            this->reactionCooldown = 60;
            this->movementCooldown = 60;
        }

        return;
    }

    if ( this->movementCooldown > 0 )
    {
        this->movementCooldown--;
        return;
    }

    std::vector<sf::Vector2i> path = PathSolver.solve( game.getMaze(), getPosition(), game.getPlayer()->getPosition() );
    
    this->movementCooldown = 60;

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

            this->movementCooldown = 0;
        }
        else 
        {
            if ( game.getEntitiesAtLocation( transposePosition( getPosition(), direction ) ).size() == 0 )
            {
                moveForward();
                this->movementCooldown = 120/path.size();
            }
            else
            {
                this->movementCooldown = 10;
            }

            this->reactionCooldown = 60;
        }
    }
}