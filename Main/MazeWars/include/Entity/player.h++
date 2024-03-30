#if !defined( PLAYER_HPP )
#define PLAYER_HPP

    #include "entity.h++"

    namespace MazeWars
    {
        class Player: public Entity
        {
            public:
                Player( sf::Vector2i position = {0,0} );
        };
    }

#endif /* PLAYER_HPP */