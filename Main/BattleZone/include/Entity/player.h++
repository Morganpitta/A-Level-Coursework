#if !defined( PLAYER_HPP )
#define PLAYER_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Player: public Entity
        {
            public:
                Player( sf::Vector2f position = {0,0} );
                
                virtual CollisionRect getCollisionRect() const override;
        };
    }

#endif /* PLAYER_HPP */