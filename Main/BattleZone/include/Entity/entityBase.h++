#if !defined( ENTITY_BASE_HPP )
#define ENTITY_BASE_HPP

    class BattleZone;
    #include "SFML/Graphics.hpp"
    #include "Render/model3D.h++"

    typedef int Id;
    extern const Id NullId;

    extern Model3D tankModel;

    enum EntityType
    {
        NoType
    };

    extern bool loadEntityAssets();

    class Entity;
    
#endif /* ENTITY_BASE_HPP */