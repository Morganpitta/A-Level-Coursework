#if !defined( MAZE_WARS_HPP )
#define MAZE_WARS_HPP

    class Entity;
    #include "renderer.h++"
    #include "Entity/entity.h++"
    #include "mazeGenerator.h++"

    class MazeWars
    {
        Renderer renderer;
        MazeGrid mazeGrid;
        Id playerId;
        std::map<Id,Entity*> entities;
        std::vector<std::vector<std::vector<Entity*>>> entityGrid;
        Id nextId = 0;

        public:
            MazeWars( sf::Vector2i dimensions ): mazeGrid( dimensions )
            {
                generateMazeDepthFirst( mazeGrid, 1 );
                entityGrid.resize( 
                    dimensions.x, 
                    std::vector<std::vector<Entity*>>(
                        dimensions.y,
                        std::vector<Entity*>()
                    )
                );

                this->playerId = addEntity( new Entity() );
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

            Entity *getPlayer()
            {
                return getEntity( this->playerId );
            }

            std::vector<Id> getEntitiesAtLocation( sf::Vector2i position ) const
            {
                std::vector<Id> entities;

                for ( const Entity* entity: entityGrid[position.x][position.y] )
                {
                    entities.push_back( entity->getId() );
                }

                return entities;
            }

            Id addEntity( Entity* entity )
            {
                Id entityId = nextId++;
                this->entities[entityId] = entity;
                entity->setId( entityId );
                return entityId;
            }

            void update( sf::RenderWindow &window )
            {
                sf::Event event;
                while ( window.pollEvent(event) )
                {
                    switch ( event.type )
                    {
                        case sf::Event::Closed:
                            window.close();
                            break;

                        case sf::Event::KeyPressed:
                            if ( event.key.code == sf::Keyboard::A )
                                getPlayer()->turnLeft();
                            if ( event.key.code == sf::Keyboard::D )
                                getPlayer()->turnRight();
                            if ( event.key.code == sf::Keyboard::W &&
                                !getMaze().getCell( 
                                    getPlayer()->getPosition(), 
                                    getPlayer()->getDirection() 
                                )
                                )
                                getPlayer()->moveForward();
                            break;
                    }
                }

                getCamera().setPosition( getPlayer()->getPosition() );
                getCamera().setDirection( getPlayer()->getDirection() );
                
                for ( std::vector<std::vector<Entity*>> &column: entityGrid )
                {
                    for ( std::vector<Entity*> &cellEntities: column )
                    {
                        cellEntities.clear();
                    }
                }

                for ( std::pair<Id, Entity*> idEntityPair: entities )
                {
                    idEntityPair.second->update( *this );
                    sf::Vector2i position = idEntityPair.second->getPosition();
                    entityGrid[position.x][position.y].push_back( idEntityPair.second );
                }
            }

            void render( sf::RenderWindow &window )
            {
                renderer.render( window, mazeGrid, entityGrid, playerId );
            }
    };

#endif /* MAZE_WARS_HPP */