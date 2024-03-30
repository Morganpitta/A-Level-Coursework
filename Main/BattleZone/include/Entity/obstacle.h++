#if !defined( OBSTACLE_HPP )
#define OBSTACLE_HPP

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

#endif /* OBSTACLE_HPP */