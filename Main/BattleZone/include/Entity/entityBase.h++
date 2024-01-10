#if !defined( ENTITY_BASE_HPP )
#define ENTITY_BASE_HPP

    class BattleZone;
    #include "SFML/Graphics.hpp"
    #include "file.h++"

    typedef int Id;
    extern const Id NullId;

    enum EntityType
    {
        NoType
    };

    extern bool loadEntityAssets();

    class Entity;
    
#endif /* ENTITY_BASE_HPP */