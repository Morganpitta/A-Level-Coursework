#if !defined( MW_PLAYER_HPP )
#define MW_PLAYER_HPP

    #include "entity.h++"

    namespace MazeWars
    {
        class Player: public Entity
        {
            public:
                Player( sf::Vector2i position = {0,0} );
        };
    }

#endif /* MW_PLAYER_HPP */