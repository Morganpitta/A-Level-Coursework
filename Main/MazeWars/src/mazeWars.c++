#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "Entity/bullet.h++"
#include "Entity/player.h++"
#include "Entity/enemy.h++"
#include "random.h++"

MazeWars::MazeWars( sf::Vector2i dimensions ): mazeGrid( dimensions ), MiniMapRadius(3)
{
    this->nextId = 0;
    generateMazeDepthFirst( mazeGrid, 1 );
    entityGrid.resize(
        dimensions.x,
        std::vector<std::vector<Entity*>>(
            dimensions.y,
            std::vector<Entity*>()
        )
    );

    this->playerId = 
        addEntity(
            new Player( 
                {
                    std::floor( dimensions.x/2 ),
                    std::floor( dimensions.y/2 )
                }
            ) 
        );
}

Camera &MazeWars::getCamera()
{
    return this->renderer.getCamera();
}

MazeGrid &MazeWars::getMaze()
{
    return this->mazeGrid;
}

Entity *MazeWars::getEntity( Id id )
{
    return this->entities[id];
}

Entity *MazeWars::getPlayer()
{
    return getEntity( this->playerId );
}

std::vector<Id> MazeWars::getEntitiesAtLocation( sf::Vector2i position ) const
{
    std::vector<Id> entities;

    for ( const Entity* entity: entityGrid[position.x][position.y] )
    {
        entities.push_back( entity->getId() );
    }

    return entities;
}

Id MazeWars::addEntity( Entity* entity )
{
    Id entityId = nextId++;
    this->entities[entityId] = entity;
    entity->setId( entityId );
    return entityId;
}

void MazeWars::cleanUpEntities()
{
    for ( auto iterator = this->entities.begin(); iterator != this->entities.end(); )
    {
        Entity *entity = (*iterator).second; 
        if ( entity->isDead() && entity->getType() != PlayerType )
            iterator = this->entities.erase( iterator );
        else
            iterator++;
    }
}

void MazeWars::attemptToSpawnEntities()
{
    int numberOfEnemies = 
        std::count_if(
            this->entities.begin(),
            this->entities.end(),
            []( const std::pair<Id, Entity*> idEntityPair )
            {
                return idEntityPair.second->getType() == EnemyType;
            }
        );

    int spawnDistance = 10;

    while ( numberOfEnemies < 30 )
    {
        float spawnAngle = randomFloat( 0, 2 * M_PI );
        sf::Vector2i spawnLocation = getPlayer()->getPosition() + 
            sf::Vector2i(
                std::floor( spawnDistance * cos( spawnAngle ) ),
                std::floor( spawnDistance * sin( spawnAngle ) )
            );
        if ( getMaze().inBounds( spawnLocation ) )
        {
            addEntity( new Enemy( spawnLocation ) );
            spawnDistance = 10;
            numberOfEnemies++;
        }
        else 
        {
            spawnDistance--;
        }
    }
}

void MazeWars::update( sf::RenderWindow &window )
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
                if ( event.key.code == sf::Keyboard::S &&
                    !getMaze().getCell( 
                        getPlayer()->getPosition(), 
                        reverseDirection( getPlayer()->getDirection() ) 
                    )
                )
                    getPlayer()->moveBackward();
                if ( event.key.code == sf::Keyboard::Space )
                    addEntity( new Bullet( getPlayer()->getId(), getPlayer()->getPosition(), getPlayer()->getDirection() ) );
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
        if ( !idEntityPair.second->isDead() )
        {
            idEntityPair.second->update( *this );
            sf::Vector2i position = idEntityPair.second->getPosition();
            entityGrid[position.x][position.y].push_back( idEntityPair.second );
        }
    }

    cleanUpEntities();
    attemptToSpawnEntities();
}

// Not going to use this
void MazeWars::drawMiniMapEntities( sf::RenderWindow &window, sf::Vector2f topLeft, sf::Vector2f bottomRight )
{
    sf::VertexArray vertexArray( sf::PrimitiveType::Lines );
    float width = ( bottomRight.x - topLeft.x );
    float height = ( bottomRight.y - topLeft.y );
    float xSegmentSize = width / ( 1 + MiniMapRadius * 2 );
    float ySegmentSize = height / ( 1 + MiniMapRadius * 2 );
    sf::RenderStates states;
    states.transform.rotate( 90*getPlayer()->getDirection(), topLeft.x + width/2.f, topLeft.y + height/2.f );

    for ( int relativeXIndex = 0; 
            relativeXIndex <= MiniMapRadius * 2; 
            relativeXIndex++ 
    )
    {
        for ( int relativeYIndex = 0; 
                relativeYIndex <= MiniMapRadius * 2; 
                relativeYIndex++
        )
        {
            int xIndex = getPlayer()->getPosition().x + relativeXIndex - MiniMapRadius;
            int yIndex = getPlayer()->getPosition().y + relativeYIndex - MiniMapRadius;

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

                    window.draw( markerRectangle, states );
                }
            }
        }
    }

    window.draw( vertexArray );
}

void MazeWars::render( sf::RenderWindow &window )
{
    renderer.render( window, mazeGrid, entityGrid, playerId );
}