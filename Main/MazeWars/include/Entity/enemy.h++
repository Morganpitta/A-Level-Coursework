#if !defined( ENEMY_HPP )
#define ENEMY_HPP

    #include "pathFinding.h++"

    class Enemy: public Entity
    {
        int movementCooldown;
        int reactionCooldown;

        public:
            Enemy( sf::Vector2i position = {0,0} );

            virtual void update( MazeWars &game ) override;
    };

#endif /* ENEMY_HPP */