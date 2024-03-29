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
        std::size_t playerKills;

        public:
            BattleZone( sf::Vector2u displaySize );

            Camera &getCamera();
            Entity *getEntity( Id id );
            const std::map<Id, Entity*> &getEntities();
            Entity *getPlayer();

            Id addEntity( Entity* entity );
            void addPlayerKill();

            void cleanUpEntities();
            void attemptToSpawnEntities();
            void handleInput( sf::Event &event );
            void update( sf::RenderWindow &window );

            void drawUI( sf::RenderWindow &window );
            void render( sf::RenderWindow &window );
    };

#endif /* BATTLE_ZONE_HPP */