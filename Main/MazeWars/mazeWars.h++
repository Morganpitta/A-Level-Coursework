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
        const int MiniMapRadius = 3;

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
                            if ( event.key.code == sf::Keyboard::P )
                                std::cout<<"REEEE";
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

            void drawMiniMapEntities( sf::RenderWindow &window, sf::Vector2f topLeft, sf::Vector2f bottomRight )
            {
                sf::VertexArray vertexArray( sf::PrimitiveType::Lines );
                float xSegmentSize = ( bottomRight.x - topLeft.x ) / ( 1 + MiniMapRadius * 2 );
                float ySegmentSize = ( bottomRight.y - topLeft.y ) / ( 1 + MiniMapRadius * 2 );

                for ( int relativeXIndex = 0; 
                      relativeXIndex <= 1 + MiniMapRadius * 2; 
                      relativeXIndex++ 
                )
                {
                    for ( int relativeYIndex = 0; 
                          relativeYIndex <= 1 + MiniMapRadius * 2; 
                          relativeYIndex++
                    )
                    {
                        int xIndex = getPlayer()->getPosition().x + relativeXIndex - ( 1 + MiniMapRadius );
                        int yIndex = getPlayer()->getPosition().y + relativeYIndex - ( 1 + MiniMapRadius );

                        if ( getMaze().inBounds( { xIndex, yIndex } ) )
                        {
                            for ( Id id: getEntitiesAtLocation( { xIndex, yIndex } ) )
                            {
                                sf::RectangleShape markerRectangle = 
                                    sf::RectangleShape( {xSegmentSize/2.f, ySegmentSize/2.f} );

                                markerRectangle.setPosition( 
                                    sf::Vector2f(
                                        relativeXIndex*xSegmentSize,
                                        -relativeYIndex*ySegmentSize
                                    ) + sf::Vector2f(50+xSegmentSize/4.f,750-(3*ySegmentSize)/4.f) 
                                );

                                window.draw( markerRectangle );
                            }
                        }
                    }
                }

                window.draw( vertexArray );
            }

            void render( sf::RenderWindow &window )
            {
                renderer.render( window, mazeGrid, entityGrid, playerId );

                std::vector<sf::Vector2i> entityLocations;
                for ( std::pair<Id,Entity*> idEntityPair: entities )
                {
                    entityLocations.push_back( idEntityPair.second->getPosition() );
                }

                drawMiniMapEntities( window, {50,50}, {750,750} );
            }
    };

#endif /* MAZE_WARS_HPP */