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

        public:
            MazeWars( sf::Vector2i dimensions ): mazeGrid( dimensions )
            {
                generateMazeDepthFirst( mazeGrid, 1, 0 );
                entityGrid.resize( 
                    dimensions.x, 
                    std::vector<std::vector<Entity*>>(
                        dimensions.y,
                        {}
                    )
                );
            }

            Entity *getEntity( Id id )
            {
                return entities[id];
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