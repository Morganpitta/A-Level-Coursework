#if !defined( BZ_OBSTACLE_HPP )
#define BZ_OBSTACLE_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Obstacle: public Entity
        {
            public:
                Obstacle( sf::Vector2f position = {0,0} );
        
                virtual CollisionRect getCollisionRect() const override;
        };
    }

#endif /* BZ_OBSTACLE_HPP */