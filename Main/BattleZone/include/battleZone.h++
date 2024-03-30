#if !defined( BATTLE_ZONE_HPP )
#define BATTLE_ZONE_HPP

    #include "Render/renderer.h++"
    #include "Entity/entityBase.h++"
    #include <map>

    namespace BattleZone
    {
        class BattleZoneGame
        {
            Renderer renderer;
            std::map<Id,Entity*> entities;
            Id playerId;
            Id nextId;
            std::size_t playerKills;

            public:
                BattleZoneGame( sf::Vector2u displaySize );
                ~BattleZoneGame();

                Camera &getCamera();
                Entity *getEntity( Id id );
                const std::map<Id, Entity*> &getEntities();
                Entity *getPlayer();

                Id addEntity( Entity* entity );
                void addPlayerKill();
                bool canMoveInDirection( Entity *entity, float distance );

                void cleanUpEntities();
                void attemptToSpawnEntities();
                void handleInput( sf::Event &event );
                void update( sf::RenderWindow &window );

                void drawGUI( sf::RenderWindow &window );
                void render( sf::RenderWindow &window );
        };
    }

#endif /* BATTLE_ZONE_HPP */