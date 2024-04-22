#if !defined( BZ_ENTITY_BASE_HPP )
#define BZ_ENTITY_BASE_HPP

    #include "SFML/Graphics.hpp"
    #include "Render/model3D.h++"

    namespace BattleZone
    {
        class BattleZoneGame;

        typedef int Id;
        extern const Id NullId;

        extern Model3D tankModel;
        extern Model3D obstacleModel;
        extern Model3D bulletModel;

        extern bool loadEntityAssets();

        enum EntityType
        {
            NoType,
            TankType,
            ObstacleType,
            BulletType,
            PlayerType
        };

        class Entity;
    }
    
#endif /* BZ_ENTITY_BASE_HPP */