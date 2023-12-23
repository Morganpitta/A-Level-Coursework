#if !defined( ENEMY_HPP )
#define ENEMY_HPP

    #include "entity.h++"
    #include "pathFinding.h++"

    class Enemy: public Entity
    {
        int movementCoolDown = 0;

        public:
            Enemy( sf::Vector2i position = {0,0} ): Entity( position )
            {
                this->type = EnemyType;
                this->texture = &TriangleTexture;
            }

            virtual void update( MazeWars &game ) override
            {
                if ( movementCoolDown > 0 )
                {
                    movementCoolDown--;
                    return;
                }

                std::vector<sf::Vector2i> path = AStarPath( game.getMaze(), getPosition(), game.getPlayer()->getPosition() );

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
                        movementCoolDown = 60/path.size();
                    }
                }
            }
    };

#endif /* ENEMY_HPP */