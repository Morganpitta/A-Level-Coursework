#if !defined( PLAYER_HPP )
#define PLAYER_HPP

    #include "Entity/entity.h++"

    class Player: public Entity
    {
        public:
            Player( sf::Vector2f position = {0,0} );
    };

#endif /* PLAYER_HPP */