#if !defined( MW_ENEMY_HPP )
#define MW_ENEMY_HPP

    #include "pathFinding.h++"
    
    namespace MazeWars
    {
        class Enemy: public Entity
        {
            int movementCooldown;
            int reactionCooldown;

            public:
                Enemy( sf::Vector2i position = {0,0} );

                virtual void update( MazeWarsGame &game ) override;
        };
    }

#endif /* MW_ENEMY_HPP */