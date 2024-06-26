#if !defined( MW_MAZE_WARS_HPP )
#define MW_MAZE_WARS_HPP

    #include "Entity/entityBase.h++"
    #include "renderer.h++"
    #include "mazeGenerator.h++"
    #include "time.h++"

    namespace MazeWars
    {
        class MazeWarsGame
        {
            Renderer renderer;
            MazeGrid mazeGrid;
            std::map<Id,Entity*> entities;
            std::vector<std::vector<std::vector<Entity*>>> entityGrid;
            Id playerId;
            Id nextId;
            std::size_t playerKills;

            public:
                MazeWarsGame( sf::Vector2u displaySize, sf::Vector2i dimensions );
                
                ~MazeWarsGame();

                Camera &getCamera();
                MazeGrid &getMaze();
                Entity *getEntity( Id id );
                Entity *getPlayer();
                std::vector<Id> getEntitiesAtLocation( sf::Vector2i position ) const;

                bool playerCanMove( Direction direction );

                Id addEntity( Entity* entity );
                void addPlayerKill();

                void cleanUpEntities();
                void attemptToSpawnEntities();
                void handleInput( sf::Event &event );
                void update();

                void drawGUI( sf::RenderWindow &window );
                void render( sf::RenderWindow &window );
        };
    }

#endif /* MW_MAZE_WARS_HPP */