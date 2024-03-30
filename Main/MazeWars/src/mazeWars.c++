#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "Entity/bullet.h++"
#include "Entity/player.h++"
#include "Entity/enemy.h++"
#include "random.h++"

namespace MazeWars
{
    MazeWarsGame::MazeWarsGame( sf::Vector2u displaySize, sf::Vector2i dimensions ): renderer(displaySize), mazeGrid( dimensions )//, MiniMapRadius(3)
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
                        dimensions.x/2,
                        dimensions.y/2
                    }
                ) 
            );

        this->playerKills = 0;
    }

    MazeWarsGame::~MazeWarsGame()
    {
        for ( std::pair<Id,Entity*> idEntityPair : this->entities )
        {
            delete idEntityPair.second;
        }

        this->entities.clear();
    }

    Camera &MazeWarsGame::getCamera() { return this->renderer.getCamera(); }

    MazeGrid &MazeWarsGame::getMaze() { return this->mazeGrid; }

    Entity *MazeWarsGame::getEntity( Id id ) { return this->entities[id]; }

    Entity *MazeWarsGame::getPlayer() { return getEntity( this->playerId ); }

    std::vector<Id> MazeWarsGame::getEntitiesAtLocation( sf::Vector2i position ) const
    {
        std::vector<Id> entities;

        for ( const Entity* entity: entityGrid[position.x][position.y] )
        {
            entities.push_back( entity->getId() );
        }

        return entities;
    }

    bool MazeWarsGame::playerCanMove( Direction direction )
    {
        bool isWallInDirection = getMaze().getCell( getPlayer()->getPosition(), direction );
        if ( isWallInDirection) 
            return false;
        
        std::vector<Id> entities = getEntitiesAtLocation( transposePosition( getPlayer()->getPosition(),direction ) );
        for ( Id id : entities )
        {
            if ( getEntity(id)->getType() != BulletType )
                return false;
        }

        return true;
    }

    Id MazeWarsGame::addEntity( Entity* entity )
    {
        Id entityId = nextId++;
        this->entities[entityId] = entity;
        entity->setId( entityId );
        return entityId;
    }

    void MazeWarsGame::addPlayerKill()
    {
        this->playerKills++;
    }

    void MazeWarsGame::cleanUpEntities()
    {
        for ( auto iterator = this->entities.begin(); iterator != this->entities.end(); )
        {
            Entity *entity = (*iterator).second; 
            if ( entity->isDead() && entity->getType() != PlayerType )
            {
                std::vector<Entity*> &entityVector = this->entityGrid[entity->getPosition().x][entity->getPosition().y];
                entityVector.erase(std::remove(entityVector.begin(), entityVector.end(), entity), entityVector.end());
                delete entity;
                iterator = this->entities.erase( iterator );
            }
            else
                iterator++;
        }
    }

    void MazeWarsGame::attemptToSpawnEntities()
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

        int spawnDistance = 20;

        while ( numberOfEnemies < 4 )
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
                spawnDistance = 20;
                numberOfEnemies++;
            }
            else 
            {
                spawnDistance--;
            }
        }
    }

    void MazeWarsGame::handleInput( sf::Event &event )
    {
        if (event.type==sf::Event::KeyPressed)
        {
            switch ( event.key.code )
            {
                case sf::Keyboard::A:
                    getPlayer()->turnLeft();
                    break;
                case sf::Keyboard::D:
                    getPlayer()->turnRight();
                    break;
                case sf::Keyboard::W:
                    if ( playerCanMove( getPlayer()->getDirection() ) )
                        getPlayer()->moveForward();
                    break;
                case sf::Keyboard::S:
                    if ( playerCanMove( reverseDirection( getPlayer()->getDirection() ) ) )
                        getPlayer()->moveBackward();
                    break;
                case sf::Keyboard::Space:
                    addEntity(
                        new Bullet( 
                            getPlayer()->getId(), 
                            getPlayer()->getPosition(), 
                            getPlayer()->getDirection() 
                        )
                    );
                    break;

                default:
                    break;
            }
        }
    }

    void MazeWarsGame::update()
    {
        getCamera().setPosition( getPlayer()->getPosition() );
        getCamera().setDirection( getPlayer()->getDirection() );
        
        for ( std::vector<std::vector<Entity*>> &column: this->entityGrid )
        {
            for ( std::vector<Entity*> &cellEntities: column )
            {
                cellEntities.clear();
            }
        }

        for ( std::pair<Id, Entity*> idEntityPair: this->entities )
        {
            Entity *entity = idEntityPair.second;
            if ( !entity->isDead() )
            {
                entity->update( *this );
                sf::Vector2i position = entity->getPosition();
                entityGrid[position.x][position.y].push_back( entity );
            }
        }

        cleanUpEntities();
        attemptToSpawnEntities();
    }

    void MazeWarsGame::drawGUI( sf::RenderWindow &window )
    {
        sf::Text text("SCORE:"+std::to_string(this->playerKills),gameFont,40);
        text.setOrigin( {text.getGlobalBounds().width/2.f,0} );
        text.setPosition( {renderer.getDisplaySize().x/2.f, 10} );
        window.draw( text );
    }

    void MazeWarsGame::render( sf::RenderWindow &window )
    {
        renderer.render( window, mazeGrid, entityGrid, playerId );
        drawGUI( window );
    }
}