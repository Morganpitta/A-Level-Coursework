#if !defined( BZ_TANK_HPP )
#define BZ_TANK_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Tank: public Entity
        {
            int reloadCooldown;

            public:
                Tank( sf::Vector2f position = {0,0} );

                virtual CollisionRect getCollisionRect() const override;

                virtual void update( BattleZoneGame &game ) override;
        };
    }

#endif /* BZ_TANK_HPP */