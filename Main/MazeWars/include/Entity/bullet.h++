#if !defined( MW_BULLET_HPP )
#define MW_BULLET_HPP

    #include "pathFinding.h++"

    namespace MazeWars
    {
        class Bullet: public Entity
        {
            Id ownerId;
            int movementCooldown;

            public:
                Bullet( Id ownerId, sf::Vector2i position = {0,0}, Direction direction = North );
                
                Id getOwnerId() const;

                virtual void update( MazeWarsGame &game ) override;
        };
    }

#endif /* MW_BULLET_HPP */