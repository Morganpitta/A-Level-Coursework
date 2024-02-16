#if !defined( BULLET_HPP )
#define BULLET_HPP

    #include "pathFinding.h++"

    class Bullet: public Entity
    {
        Id ownerId;
        int movementCooldown;

        public:
            Bullet( Id ownerId, sf::Vector2i position = {0,0}, Direction direction = North );
            
            Id getOwnerId() const;

            virtual void update( MazeWars &game ) override;
    };

#endif /* BULLET_HPP */