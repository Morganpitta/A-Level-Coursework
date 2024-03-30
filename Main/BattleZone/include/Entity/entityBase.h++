#if !defined( ENTITY_BASE_HPP )
#define ENTITY_BASE_HPP

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

        enum EntityType
        {
            NoType,
            TankType,
            ObstacleType,
            BulletType,
            PlayerType
        };

        extern bool loadEntityAssets();

        class Entity;
    }
    
#endif /* ENTITY_BASE_HPP */