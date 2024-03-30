#if !defined( ENTITY_BASE_HPP )
#define ENTITY_BASE_HPP

    #include "direction.h++"
    #include "SFML/Graphics.hpp"
    #include "file.h++"

    namespace MazeWars
    {
        class MazeWarsGame;

        typedef int Id;
        extern const Id NullId;

        enum EntityType
        {
            NoType,
            EnemyType,
            BulletType,
            PlayerType
        };

        extern sf::Texture EnemyTexture;
        extern sf::Texture BulletTexture;

        extern bool loadEntityAssets();

        class Entity;
    }

#endif /* ENTITY_BASE_HPP */