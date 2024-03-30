#if !defined( BULLET_HPP )
#define BULLET_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Bullet: public Entity
        {
            Id ownerId;

            public:
                Bullet( Id ownerId, sf::Vector2f position = {0,0}, float rotation = 0 );

                Id getOwnerId() const;

                virtual CollisionRect getCollisionRect() const override;

                virtual void update( BattleZoneGame &game ) override;
        };
    }

#endif /* BULLET_HPP */