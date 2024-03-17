#if !defined( MAZE_WARS_HPP )
#define MAZE_WARS_HPP

    #include "Entity/entityBase.h++"
    #include "renderer.h++"
    #include "mazeGenerator.h++"

    class MazeWars
    {
        Renderer renderer;
        MazeGrid mazeGrid;
        std::map<Id,Entity*> entities;
        std::vector<std::vector<std::vector<Entity*>>> entityGrid;
        Id playerId;
        Id nextId;
        //const int MiniMapRadius;

        public:
            MazeWars( sf::Vector2u displaySize, sf::Vector2i dimensions );
            
            ~MazeWars();

            Camera &getCamera();

            MazeGrid &getMaze();

            Entity *getEntity( Id id );

            Entity *getPlayer();

            std::vector<Id> getEntitiesAtLocation( sf::Vector2i position ) const;

            bool playerCanMove( Direction direction );

            Id addEntity( Entity* entity );

            void cleanUpEntities();

            void attemptToSpawnEntities();

            void handleInput( sf::Event &event );

            void update( sf::RenderWindow &window );

            // Not going to use this
            //void drawMiniMapEntities( sf::RenderWindow &window, sf::Vector2f topLeft, sf::Vector2f bottomRight );

            void render( sf::RenderWindow &window );
    };

#endif /* MAZE_WARS_HPP */