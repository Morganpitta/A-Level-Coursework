#if !defined( MAZE_WARS_HPP )
#define MAZE_WARS_HPP

    #include "renderer.h++"
    #include "entity.h++"
    #include "mazeGenerator.h++"

    class MazeWars
    {
        Renderer renderer;
        MazeGrid mazeGrid;
        std::map<Id,Entity*> entities;
        std::vector<std::vector<std::vector<Entity*>>> entityGrid;
        Id nextId = 0;

        public:
            MazeWars( sf::Vector2i dimensions ): mazeGrid( dimensions )
            {
                generateMazeDepthFirst( mazeGrid, 1, 0.2 );
                entityGrid.resize( 
                    dimensions.x, 
                    std::vector<std::vector<Entity*>>(
                        dimensions.y,
                        std::vector<Entity*>()
                    )
                );
            }

            Camera &getCamera()
            {
                return this->renderer.getCamera();
            }

            MazeGrid &getMaze()
            {
                return this->mazeGrid;
            }

            Entity *getEntity( Id id )
            {
                return this->entities[id];
            }

            Id addEntity( Entity* entity )
            {
                Id entityId = nextId++;
                this->entities[entityId] = entity;
                entity->setId( entityId );
                return entityId;
            }

            void update()
            {
                for ( std::vector<std::vector<Entity*>> &column: entityGrid )
                {
                    for ( std::vector<Entity*> &cellEntities: column )
                    {
                        cellEntities.clear();
                    }
                }

                for ( std::pair<Id, Entity*> idEntityPair: entities )
                {
                    idEntityPair.second->update();
                    entityGrid[idEntityPair.second->getPosition().x][idEntityPair.second->getPosition().y].push_back( idEntityPair.second );
                }
            }

            void render( sf::RenderWindow &window )
            {
                renderer.render( window, mazeGrid, entityGrid );
            }
    };

#endif /* MAZE_WARS_HPP */