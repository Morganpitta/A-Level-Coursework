#if !defined( BULLET_HPP )
#define BULLET_HPP

    #include "Entity/entity.h++"

    class Bullet: public Entity
    {
        Id ownerId;

        public:
            Bullet( Id ownerId, sf::Vector2f position = {0,0}, float rotation = 0 );

            virtual void update( BattleZone &game ) override;
    };

#endif /* BULLET_HPP */