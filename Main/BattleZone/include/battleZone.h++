#if !defined( BATTLE_ZONE_HPP )
#define BATTLE_ZONE_HPP

    #include "Render/renderer.h++"
    #include "Entity/entityBase.h++"
    #include <map>

    class BattleZone
    {
        Renderer renderer;
        std::map<Id,Entity*> entities;
        Id playerId;
        Id nextId;

        public:
            BattleZone();

            Camera &getCamera();

            Entity *getEntity( Id id );

            Entity *getPlayer();

            Id addEntity( Entity* entity );

            void cleanUpEntities();

            void update( sf::RenderWindow &window );

            void render( sf::RenderWindow &window );
    };

#endif /* BATTLE_ZONE_HPP */