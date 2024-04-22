// File: Main\MazeWars\include\camera.h++

#if !defined( MW_CAMERA_HPP )
#define MW_CAMERA_HPP

    #include "direction.h++"
    #include "SFML/Graphics.hpp"

    namespace MazeWars
    {
        class Camera
        {
            sf::Vector2i position;
            Direction direction;
            float fov;
            
            public:
                Camera();

                sf::Vector2i getPosition() const;
                Direction getDirection() const;
                float getFov() const;

                void setPosition( sf::Vector2i position );
                void setDirection( Direction direction );
                void setFov( float fov );

                void moveForward();
                void moveBackward();
                void turnLeft();
                void turnRight();

                sf::Vector2f relativePositionOf( sf::Vector2f position );
        };
    }
    
#endif /* MW_CAMERA_HPP */


// File: Main\MazeWars\include\direction.h++

#if !defined ( MW_DIRECTIONS_HPP )
#define MW_DIRECTIONS_HPP

    #include <SFML/System.hpp>
    #include <iostream>
    #define _USE_MATH_DEFINES
    #include <cmath>

    namespace MazeWars
    {
        extern const sf::Vector2i NullPosition;

        enum Direction
        {
            North,
            East,
            South,
            West,
            NumberOfDirections,
            NoDirection
        };

        std::string directionToString( Direction direction );

        sf::Vector2i transposePosition( 
            sf::Vector2i position,
            Direction direction
        );

        Direction getDirectionOf( 
            sf::Vector2i position1, 
            sf::Vector2i position2 
        );

        sf::Vector2f rotatePosition( 
            sf::Vector2f position, 
            Direction direction 
        );

        Direction normaliseDirection( int direction );

        Direction reverseDirection( int direction );

        #define forEachDirection( direction )   \
            for ( Direction direction = North; direction < NumberOfDirections; direction = Direction( direction + 1 ) )
    }

#endif /* MW_DIRECTIONS_HPP */


// File: Main\MazeWars\include\Entity\bullet.h++

#if !defined( MW_BULLET_HPP )
#define MW_BULLET_HPP

    #include "pathFinding.h++"

    namespace MazeWars
    {
        class Bullet: public Entity
        {
            Id ownerId;
            int movementCooldown;

            public:
                Bullet( Id ownerId, sf::Vector2i position = {0,0}, Direction direction = North );
                
                Id getOwnerId() const;

                virtual void update( MazeWarsGame &game ) override;
        };
    }

#endif /* MW_BULLET_HPP */


// File: Main\MazeWars\include\Entity\enemy.h++

#if !defined( MW_ENEMY_HPP )
#define MW_ENEMY_HPP

    #include "pathFinding.h++"
    
    namespace MazeWars
    {
        class Enemy: public Entity
        {
            int movementCooldown;
            int reactionCooldown;

            public:
                Enemy( sf::Vector2i position = {0,0} );

                virtual void update( MazeWarsGame &game ) override;
        };
    }

#endif /* MW_ENEMY_HPP */


// File: Main\MazeWars\include\Entity\entity.h++

#if !defined( MW_ENTITY_HPP )
#define MW_ENTITY_HPP

    #include "direction.h++"
    #include "SFML/Graphics.hpp"
    #include "file.h++"
    #include "Entity/entityBase.h++"

    namespace MazeWars
    {
        class Entity
        {
            protected:
                sf::Vector2i position;
                Direction direction;
                int health;
                Id id;
                bool dead;
                EntityType type;
                sf::Texture *texture;
                float size;
            
            public:
                Entity( sf::Vector2i position = {0,0} );

                sf::Vector2i getPosition() const;
                Direction getDirection() const;
                int getHealth() const;
                Id getId() const;
                bool isDead() const;
                EntityType getType() const;
                sf::Texture *getTexture() const;
                float getSize() const;

                void setPosition( sf::Vector2i position );
                void setDirection( Direction direction );
                void setHealth( int health );
                void setId( Id id );

                void moveForward();
                void moveBackward();
                void turnLeft();
                void turnRight();
                void damage( int amount );
                void kill();

                sf::Vector2i relativePositionOf( sf::Vector2i position );

                virtual void update( MazeWarsGame &game );
        };
    }

#endif /* MW_ENTITY_HPP */


// File: Main\MazeWars\include\Entity\entityBase.h++

#if !defined( MW_ENTITY_BASE_HPP )
#define MW_ENTITY_BASE_HPP

    #include "direction.h++"
    #include "SFML/Graphics.hpp"
    #include "file.h++"

    namespace MazeWars
    {
        class MazeWarsGame;

        typedef int Id;
        extern const Id NullId;

        enum EntityType
        {
            NoType,
            EnemyType,
            BulletType,
            PlayerType
        };

        extern sf::Texture EnemyTexture;
        extern sf::Texture BulletTexture;

        extern bool loadEntityAssets();

        class Entity;
    }

#endif /* MW_ENTITY_BASE_HPP */


// File: Main\MazeWars\include\Entity\pathFinding.h++

#if !defined( MW_PATH_FINDING_HPP )
#define MW_PATH_FINDING_HPP

    #include "entity.h++"
    #include "mazeGrid.h++"
    #include <set>
    #include <functional>

    namespace MazeWars
    {
        extern bool isDirectlyInFront( MazeGrid &mazeGrid, Entity *entity1, sf::Vector2i entity2Position );

        extern float manhattanDistance( sf::Vector2i startPosition, sf::Vector2i finalPosition );

        class AStarSolver
        {
            struct CellData
            {
                sf::Vector2i previousCell = NullPosition;
                int distanceToStart = 0;
                int predictedDistanceToEnd = 0;
            };
            std::vector<std::vector<CellData>> graphData;
            std::set<sf::Vector2i,std::function<bool(const sf::Vector2i&, const sf::Vector2i&)>> cellsToVisit;
            
            bool comparisonFunction( const sf::Vector2i &position1, const sf::Vector2i &position2) const;

            void reset( sf::Vector2i dimensions );

            CellData &getCellData( sf::Vector2i position );

            CellData getCellData( sf::Vector2i position ) const;

            void addCellToVisit( sf::Vector2i currentCell, sf::Vector2i nextCell, sf::Vector2i finalPosition );

            std::vector<sf::Vector2i> getReturnPath( sf::Vector2i startPosition, sf::Vector2i finalPosition );

            public:
                AStarSolver();

                std::vector<sf::Vector2i> solve( MazeGrid &mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition );
        };

        extern AStarSolver PathSolver;
    }

#endif /* MW_PATH_FINDING_HPP */


// File: Main\MazeWars\include\Entity\player.h++

#if !defined( MW_PLAYER_HPP )
#define MW_PLAYER_HPP

    #include "entity.h++"

    namespace MazeWars
    {
        class Player: public Entity
        {
            public:
                Player( sf::Vector2i position = {0,0} );
        };
    }

#endif /* MW_PLAYER_HPP */


// File: Main\MazeWars\include\mainLoop.h++

#if !defined( MW_MAIN_LOOP_HPP )
#define MW_MAIN_LOOP_HPP
    #include "mazeWars.h++"
    #include "Entity/entity.h++"
    #include "random.h++"

    namespace MazeWars
    {
        extern const float targetWidth;
        extern const float targetHeight;

        void handleResize( 
            sf::RenderWindow &window,
            float windowWidth, 
            float windowHeight
        );

        void handleInputs( sf::RenderWindow &window, MazeWarsGame &game );

        void mainLoop( sf::RenderWindow &window );
        void deathScreenLoop( sf::RenderWindow &window );
    }
#endif /* MW_MAIN_LOOP_HPP */


// File: Main\MazeWars\include\mazeGenerator.h++

#if !defined( MW_MAZE_GENERATOR_HPP )
#define MW_MAZE_GENERATOR_HPP

    #include "mazeGrid.h++"
    #include "time.h++"
    #include <array>

    namespace MazeWars
    {
        extern void randomlyRemoveWall( 
            sf::Vector2i position,
            MazeGrid &mazeGrid,
            float randomness
        );

        extern Direction getRandomValidDirection( 
            sf::Vector2i position, 
            MazeGrid &mazeGrid, 
            const std::vector<std::vector<bool>> &isSearched 
        );

        extern void generateMazeDepthFirst( 
            MazeGrid &mazeGrid, 
            float randomness, 
            std::size_t seed = time(NULL)
        );
    }
    
#endif /* MW_MAZE_GENERATOR_HPP */


// File: Main\MazeWars\include\mazeGrid.h++

#if !defined( MW_MAZE_GRID_HPP )
#define MW_MAZE_GRID_HPP

    #include <vector>
    #include "direction.h++"
    #include "SFML/Graphics.hpp"

    namespace MazeWars
    {
        class MazeGrid
        {
            sf::Vector2i dimensions;
            int numberOfWalls;
            std::vector<bool> horizontalSegments;
            std::vector<bool> verticalSegments;
            
            public:
                MazeGrid( sf::Vector2i dimensions );

                ~MazeGrid();

                sf::Vector2i getDimensions() const;
                bool inBounds( sf::Vector2i position )  const;
                std::size_t getNumberOfWalls() const;
                std::size_t getNumberOfHorizontalSegments() const;
                std::size_t getNumberOfVerticalSegments() const;
                std::size_t getNumberOfWallSegments() const;
                bool getHorizontal( sf::Vector2i position ) const;
                bool getVertical( sf::Vector2i position ) const;
                bool getCell( 
                    sf::Vector2i position, 
                    Direction direction 
                ) const;

                void set( 
                    std::vector<bool> horizontalSegments, 
                    std::vector<bool> verticalSegments 
                );
                void fill( bool value );
                void resize( sf::Vector2i dimensions );
                void setHorizontal( 
                    sf::Vector2i position, 
                    bool value 
                );
                void setVertical( 
                    sf::Vector2i position, 
                    bool value 
                );
                void setCell( 
                    sf::Vector2i position,
                    Direction direction, 
                    bool value 
                );
        };

        extern void drawMaze( 
            sf::RenderWindow &window, 
            MazeGrid &maze, 
            sf::Vector2f topLeft, 
            sf::Vector2f bottomRight, 
            std::vector<sf::Vector2i> markers = {} 
        );
    }

#endif /* MW_MAZE_GRID_HPP */


// File: Main\MazeWars\include\mazeWars.h++

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


// File: Main\MazeWars\include\renderer.h++

#if !defined( MW_RENDERER_HPP )
#define MW_RENDERER_HPP

    #include "Entity/entityBase.h++"
    #include "camera.h++"
    #include "mazeGrid.h++"
    #include "draw.h++"
    #include <queue>
    #include <map>
    #include <algorithm>

    namespace MazeWars
    {
        class Renderer
        {
            const sf::Vector2u displaySize;
            const float yNear;
            const float wallHeight;
            Camera camera;
            sf::VertexArray wallVertices;
            std::vector<sf::RectangleShape> entityRectangles;
            std::vector<bool> drawnOn;

            bool hasBeenDrawnOn( int xIndex ) const;
            bool canDrawInRange(
                float startIndex,
                float endIndex
            ) const;
            void setHasBeenDrawnOn(
                int xIndex,
                bool value
            );
            void setHasBeenDrawnOn(
                int startIndex,
                int endIndex,
                bool value
            );

            public:
                Renderer( sf::Vector2u displaySize );

                Camera &getCamera();
                float getYNear() const;
                sf::Vector2u getDisplaySize() const;
                bool onScreen( float xValue ) const;

                sf::Vector2f clipLineToNearPlane( 
                    sf::Vector2f lineStart,
                    sf::Vector2f lineEnd 
                );
                bool projectPoint(
                    sf::Vector2f &position,
                    float &size
                );
                bool projectLine(
                    sf::Vector2f &lineStart,
                    sf::Vector2f &lineEnd
                );

                void drawWallVertical( sf::Vector2f position );
                void drawWallHorizontals(
                    sf::Vector2f &wallStart,
                    sf::Vector2f &wallEnd
                );
                void drawWall(
                    sf::Vector2f &wallStart,
                    sf::Vector2f &wallEnd
                );

                void drawEntity( Entity *entity );

                void render(
                    sf::RenderWindow& window,
                    MazeGrid &mazeGrid,
                    const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
                    Id playerId
                );
        };
    }

#endif /* MW_RENDERER_HPP */


// File: Main\MazeWars\src\camera.c++

#include "camera.h++" 
#include "assert.h++"

namespace MazeWars
{
    Camera::Camera()
    {
        this->position = {0,0};
        this->direction = North;
        this->fov = 2;
    }

    sf::Vector2i Camera::getPosition() const { return this->position; }

    Direction Camera::getDirection() const { return this->direction; }

    float Camera::getFov() const { return this->fov; }

    void Camera::setPosition( sf::Vector2i position ) { this->position = position; }

    void Camera::setDirection( Direction direction ) { this->direction = direction; }

    void Camera::setFov( float fov ) { this->fov = fov; }

    void Camera::moveForward()
    {
        setPosition( transposePosition( getPosition(), getDirection() ) );
    }

    void Camera::moveBackward()
    {
        setPosition( transposePosition( getPosition(), reverseDirection( getDirection() ) ) );
    }

    void Camera::turnLeft()
    {
        setDirection( normaliseDirection( int(getDirection()) - 1 ) );
    }

    void Camera::turnRight()
    {
        setDirection( normaliseDirection( int(getDirection()) + 1 ) );
    }

    sf::Vector2f Camera::relativePositionOf( sf::Vector2f position )
    {
        // The camera is in the center of the cell, whilst cell positions are the top left position.
        // Therefore add {0.5f,0.5f} to the position to center it.
        // Then rotate it in the opposite direction that the camera is facing in ( for reasons explained in my design )
        return rotatePosition( 
            position - sf::Vector2f( getPosition().x+0.5f, getPosition().y+0.5f ),
            normaliseDirection( -getDirection() )
        );
    }
}


// File: Main\MazeWars\src\direction.c++

#include "direction.h++"

namespace MazeWars
{
    const sf::Vector2i NullPosition = {-1,-1};

    std::string directionToString( Direction direction )
    {
        switch ( direction )
        {
            case ( North ):
                return "North";
                break;
            case ( East ):
                return "East";
                break;
            case ( South ):
                return "South";
                break;
            case ( West ):
                return "West";
                break;
            default:
                return "Unknown";
                break;
        }
    }

    sf::Vector2i transposePosition( 
        sf::Vector2i position,
        Direction direction
    )
    {
        switch ( direction )
        {
            case North:
                return { position.x, position.y+1 };
                break;

            case East:
                return { position.x+1, position.y };
                break;

            case South:
                return { position.x, position.y-1 };
                break;

            case West:
                return { position.x-1, position.y };
                break;
            
            default:
                return position;
                break;
        }
    }

    Direction getDirectionOf( 
        sf::Vector2i position1, 
        sf::Vector2i position2 
    )
    {
        if ( position2 == sf::Vector2i( position1.x, position1.y+1 ) )
            return North;

        if ( position2 == sf::Vector2i( position1.x+1, position1.y ) )
            return East;

        if ( position2 == sf::Vector2i( position1.x, position1.y-1 ) )
            return South;

        if ( position2 == sf::Vector2i( position1.x-1, position1.y ) )
            return West;

        return NoDirection;
    }

    sf::Vector2f rotatePosition( 
        sf::Vector2f position, 
        Direction direction 
    )
    {
        // Converting the direction into an angle 
        // North -> 0 degrees, East -> 90 degrees, 
        // South -> 180 degrees, West -> 270 degrees.
        float angle = (M_PI / 2) * ( ( direction ) % NumberOfDirections );

        
        // The 2D rotation matrix
        return {
            static_cast<float>( 
                position.x*cos( angle ) + position.y*sin( angle ) 
            ),
            static_cast<float>( 
                - position.x*sin( angle ) + position.y*cos( angle )
            ) 
        };
    }

    Direction normaliseDirection( int direction )
    {
        direction = ( direction ) % NumberOfDirections;
        if ( direction < 0 )
            direction += NumberOfDirections;
        return Direction( direction );
    }

    Direction reverseDirection( int direction )
    {
        return normaliseDirection( direction + South );
    }
}


// File: Main\MazeWars\src\Entity\bullet.c++

#include "Entity/bullet.h++"
#include "mazeWars.h++"

namespace MazeWars
{
    Bullet::Bullet( Id ownerId, sf::Vector2i position, Direction direction ): Entity( position )
    {
        this->ownerId = ownerId;
        this->type = BulletType;
        this->texture = &BulletTexture;
        this->size = 20;
        this->direction = direction;
        this->movementCooldown = 5;
    }

    Id Bullet::getOwnerId() const { return this->ownerId; }

    void Bullet::update( MazeWarsGame &game )
    {
        // If the bullet is still on movement cooldown, decrement the cooldown and exit.
        if ( this->movementCooldown > 0 )
        {    
            this->movementCooldown--;
            return;
        }

        this->movementCooldown = 5;

        // If there is a wall in front.
        if ( game.getMaze().getCell( getPosition(), getDirection() ) ) 
            kill();
        else
        {
            sf::Vector2i nextPosition = transposePosition( getPosition(), getDirection() );
            if ( game.getMaze().inBounds( nextPosition ) )
            { 
                std::vector<Id> hitEntities = game.getEntitiesAtLocation( nextPosition );
                bool hitEntity = false;
                for ( Id entityId: hitEntities )
                {
                    if ( entityId == getOwnerId() )
                        continue;
                    Entity* entity = game.getEntity( entityId );

                    entity->damage( 1 );
                    if ( entity->isDead() && getOwnerId() == game.getPlayer()->getId() && entity->getType() == EnemyType )
                        game.addPlayerKill();
                    hitEntity = true;
                }

                if ( hitEntity )
                    kill();
                else
                    setPosition( nextPosition );
            }
        }
    }
}


// File: Main\MazeWars\src\Entity\enemy.c++

#include "Entity/enemy.h++"
#include "mazeWars.h++"
#include "Entity/bullet.h++"

namespace MazeWars
{
    Enemy::Enemy( sf::Vector2i position ): Entity( position )
    {
        this->type = EnemyType;
        this->texture = &EnemyTexture;
        this->movementCooldown = 0;
        this->reactionCooldown = 60;
    }

    void Enemy::update( MazeWarsGame &game )
    {
        if ( isDirectlyInFront( game.getMaze(), this, game.getPlayer()->getPosition() ) )
        {
            if ( this->reactionCooldown > 0 )
            {
                this->reactionCooldown--;
                this->movementCooldown = 10;
            }
            else
            {
                game.addEntity( new Bullet( getId(), getPosition(), getDirection() ) );
                this->reactionCooldown = 60;
                this->movementCooldown = 60;
            }

            return;
        }

        if ( this->movementCooldown > 0 )
        {
            this->movementCooldown--;
            return;
        }

        std::vector<sf::Vector2i> path = PathSolver.solve( game.getMaze(), getPosition(), game.getPlayer()->getPosition() );
        
        this->movementCooldown = 60;

        if ( !path.empty() )
        {
            Direction direction = getDirectionOf( path[0], path[1] );
            if ( direction != getDirection() )
            {
                // If the relative direction is west, then you need to turn left
                // if it's to your right or behind you, you need to turn right
                if ( direction - getDirection() == West )
                    turnLeft();
                else
                    turnRight();

                this->movementCooldown = 0;
            }
            else 
            {
                if ( game.getEntitiesAtLocation( transposePosition( getPosition(), direction ) ).empty() )
                {
                    moveForward();
                    this->movementCooldown = 120/path.size();
                }
                else
                {
                    this->movementCooldown = 10;
                }

                this->reactionCooldown = 60;
            }
        }
    }
}


// File: Main\MazeWars\src\Entity\entity.c++

#include "Entity/entity.h++"
#include "mazeWars.h++"

namespace MazeWars
{
    const Id NullId = -1;
    sf::Texture EnemyTexture;
    sf::Texture BulletTexture;

    bool loadEntityAssets()
    {
        setWorkingDirectoryToDefault();

        if ( !EnemyTexture.loadFromFile( "MazeWars/eye.png" ) )
            return false;

        if ( !BulletTexture.loadFromFile( "MazeWars/circle.png" ) )
            return false;

        return true;
    }

    Entity::Entity( sf::Vector2i position )
    {
        this->position = position;
        this->direction = North;
        this->health = 1;
        this->id = NullId;
        this->dead = false;
        this->type = NoType;
        this->texture = nullptr;
        this->size = 75;
    }

    sf::Vector2i Entity::getPosition() const
    {
        return this->position;
    }

    Direction Entity::getDirection() const { return this->direction; }

    int Entity::getHealth() const { return this->health; }

    Id Entity::getId() const { return this->id; }

    bool Entity::isDead() const { return this->dead; }

    EntityType Entity::getType() const { return this->type; }

    sf::Texture *Entity::getTexture() const { return this->texture; }

    float Entity::getSize() const { return this->size; }

    void Entity::setPosition( sf::Vector2i position ) { this->position = position; }

    void Entity::setDirection( Direction direction ) { this->direction = direction; }

    void Entity::setHealth( int health ) { this->health = health; }

    void Entity::setId( Id id ) { this->id = id; }

    void Entity::moveForward()
    {
        setPosition( 
            transposePosition( 
                getPosition(), 
                getDirection() 
            )
        );
    }

    void Entity::moveBackward()
    {
        setPosition( 
            transposePosition( 
                getPosition(), 
                reverseDirection( getDirection() ) 
            )
        );
    }

    void Entity::turnLeft()
    {
        setDirection( normaliseDirection( int(getDirection()) - 1 ) );
    }

    void Entity::turnRight()
    {
        setDirection( normaliseDirection( int(getDirection()) + 1 ) );
    }

    void Entity::damage( int amount )
    {
        setHealth( std::max( getHealth() - amount, 0 ) );

        if ( getHealth() <= 0 )
            kill();
    }

    void Entity::kill()
    {
        this->dead = true;
    }

    sf::Vector2i Entity::relativePositionOf( sf::Vector2i position )
    {
        return sf::Vector2i( rotatePosition( 
            sf::Vector2f( position - getPosition() ),
            normaliseDirection( -getDirection() )
        ) );
    }

    void Entity::update( MazeWarsGame &game ) {}
}


// File: Main\MazeWars\src\Entity\pathFinding.c++

#include "Entity/pathFinding.h++"

namespace MazeWars
{
    AStarSolver PathSolver;

    bool isDirectlyInFront( MazeGrid &mazeGrid, Entity *entity1, sf::Vector2i entity2Position )
    {
        sf::Vector2i relativePosition = entity1->relativePositionOf( entity2Position );
        if ( relativePosition.x == 0 and relativePosition.y > 0 )
        {
            sf::Vector2i position = entity1->getPosition();
            while ( position != entity2Position )
            {
                if ( mazeGrid.getCell( position, entity1->getDirection() ) )
                    return false;
                position = transposePosition( position, entity1->getDirection() );
            }

            return true;
        }

        return false;
    } 

    float manhattanDistance( sf::Vector2i startPosition, sf::Vector2i finalPosition ) 
    {
        return abs( startPosition.x - finalPosition.x ) + abs( startPosition.y - finalPosition.y );
    }

    bool AStarSolver::comparisonFunction( const sf::Vector2i &position1, const sf::Vector2i &position2 ) const
    {
        // If the distances are the same, since its a set comparison function it needs to be consistent.
        // So use the position to calculate a consistent comparison.
        if ( getCellData(position1).predictedDistanceToEnd ==
             getCellData(position2).predictedDistanceToEnd )
        {
            return std::tie( position1.x, position1.y ) < std::tie( position2.x, position2.y );
        }

        return getCellData(position1).predictedDistanceToEnd <
               getCellData(position2).predictedDistanceToEnd;
    }


    void AStarSolver::reset( sf::Vector2i dimensions )
    {
        this->graphData.resize(
            dimensions.x,
            std::vector<CellData>(
                dimensions.y
            )
        );
        
        for ( int xIndex = 0; xIndex < dimensions.x; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < dimensions.y; yIndex++ )
            {
                this->graphData[xIndex][yIndex].previousCell = NullPosition;
            }
        }

        this->cellsToVisit.clear();
    }

    AStarSolver::CellData &AStarSolver::getCellData( sf::Vector2i position )
    {
        return this->graphData[position.x][position.y];
    }

    AStarSolver::CellData AStarSolver::getCellData( sf::Vector2i position ) const
    {
        return this->graphData[position.x][position.y];
    }

    void AStarSolver::addCellToVisit( sf::Vector2i currentCell, sf::Vector2i nextCell, sf::Vector2i finalPosition )
    {
        // If the cell is unvisited or the original path was longer than this path, update to use this path.
        if ( getCellData(nextCell).previousCell == NullPosition || 
             getCellData(nextCell).distanceToStart > getCellData(currentCell).distanceToStart + 1 )
        { 
            getCellData(nextCell).previousCell = currentCell;
            getCellData(nextCell).distanceToStart = getCellData(currentCell).distanceToStart + 1;
            getCellData(nextCell).predictedDistanceToEnd = getCellData(nextCell).distanceToStart + manhattanDistance(nextCell, finalPosition);
            
            cellsToVisit.insert( nextCell );
        }
    }

    std::vector<sf::Vector2i> AStarSolver::getReturnPath( sf::Vector2i startPosition, sf::Vector2i finalPosition )
    {
        std::vector<sf::Vector2i> path = {};
        sf::Vector2i cell = finalPosition;
        while ( cell != startPosition )
        {
            // Somethings gone very wrong if this is true ( or theres just no path back )
            if ( getCellData(cell).previousCell == NullPosition )
                return {};

            path.insert( path.begin(), cell );
            cell = getCellData(cell).previousCell;
        }

        path.insert( path.begin(), startPosition );

        return path;
    }

    // Initialising the cellsToVisit set. 
    // As the comparison function needs a reference to the AStarSolver instance, I bound the two values together.
    AStarSolver::AStarSolver(): cellsToVisit(std::bind(&AStarSolver::comparisonFunction, this, std::placeholders::_1, std::placeholders::_2))
    {
        
    }

    std::vector<sf::Vector2i> AStarSolver::solve( MazeGrid &mazeGrid, sf::Vector2i startPosition, sf::Vector2i finalPosition )
    {
        reset( mazeGrid.getDimensions() );

        cellsToVisit.insert( startPosition );

        while ( cellsToVisit.size() > 0 ) 
        {
            sf::Vector2i currentCell = *cellsToVisit.begin();
            cellsToVisit.erase(cellsToVisit.begin());

            if ( currentCell == finalPosition )
                break;

            forEachDirection( direction )
            {
                bool isWall = mazeGrid.getCell( currentCell, (Direction) direction );

                if ( !isWall )
                {
                    sf::Vector2i nextCell = transposePosition( currentCell, (Direction) direction );
                    if ( nextCell == startPosition || !mazeGrid.inBounds( nextCell ) )
                        continue;

                    addCellToVisit( currentCell, nextCell, finalPosition );
                }
            }
        }

        return getReturnPath( startPosition, finalPosition );
    }
}


// File: Main\MazeWars\src\Entity\player.c++

#include "Entity/player.h++"

namespace MazeWars
{
    Player::Player( sf::Vector2i position ): Entity( position )
    {
        this->type = PlayerType;
    }
}


// File: Main\MazeWars\src\main.c++

#include "mainLoop.h++"

using namespace MazeWars;

int main()
{
    sf::RenderWindow window( sf::VideoMode(900,900), "Mazewars" );
    
    mainLoop( window );

    return 0;
}


// File: Main\MazeWars\src\mainLoop.c++

#include "mainLoop.h++"

namespace MazeWars
{
    const float targetWidth = 900;
    const float targetHeight = 900;

    void handleResize( 
        sf::RenderWindow &window,
        float windowWidth, 
        float windowHeight
    )
    {
        float ratio = windowWidth/windowHeight;
        float targetRatio = targetWidth/targetHeight;
        sf::FloatRect visibleArea(0, 0, targetWidth, targetHeight);
        
        if ( ratio > targetRatio )
        {
            float offset = targetWidth*(ratio/targetRatio-1);
            visibleArea = sf::FloatRect(-offset/2, 0, targetWidth+offset, targetHeight);
        }
        else if ( ratio < targetRatio )
        {
            float offset = targetHeight*(targetRatio/ratio-1);
            visibleArea = sf::FloatRect(0, -offset/2, targetWidth, targetHeight+offset);
        }
        window.setView(sf::View(visibleArea));
    }

    void handleInputs( sf::RenderWindow &window, MazeWarsGame &game )
    {
        sf::Event event;
        // For each event
        while ( window.pollEvent(event) )
        {
            // Handle appropriately
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::Resized:
                    handleResize(window, (float) event.size.width, (float) event.size.height);
                    break;
                
                default:
                    game.handleInput(event);
                    break;
            }
        }
    }

    void mainLoop( sf::RenderWindow &window )
    {
        handleResize( window, window.getSize().x, window.getSize().y );
        window.setTitle( "Mazewars" );
        window.setKeyRepeatEnabled(false);

        if ( !loadEntityAssets() || !loadBaseAssets() )
            return;

        FpsLimiter fps( 60 );

        MazeWarsGame game( sf::Vector2u(targetWidth,targetHeight), { 50, 50 } );

        while (window.isOpen() && !game.getPlayer()->isDead())
        {
            handleInputs( window, game );
            game.update();

            window.clear( sf::Color::Black );

            game.render( window );

            // fps.draw(window, {0,0}, 30, sf::Color::White);

            window.display();
            fps.restartAndSleep();
        }
        
        MazeWars::deathScreenLoop( window );
    }

    void deathScreenLoop( sf::RenderWindow &window )
    {
        bool keyPressed = false;
        while (window.isOpen() && !keyPressed)
        {
            sf::Event event;
            while ( window.pollEvent(event) )
            {
                switch ( event.type )
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    
                    case sf::Event::Resized:
                        handleResize(window, (float) event.size.width, (float) event.size.height);
                        break;

                    case sf::Event::KeyPressed:
                        keyPressed = true;
                        break;
                    
                    default:
                        break;
                }
            }

            window.clear( sf::Color::Black );
            drawTextCentered(
                window,
                "GAME OVER", gameFont, 60,
                {targetWidth/2.f, targetHeight/2.f - 60},
                sf::Color::Green
            );
            drawTextCentered(
                window,
                "PRESS ANY KEY TO CONTINUE", gameFont, 30,
                {targetWidth/2.f, targetHeight/2.f + 60},
                sf::Color::Green
            );
            window.display();
        }
    }
}


// File: Main\MazeWars\src\mazeGenerator.c++

#include "mazeGenerator.h++"
#include "random.h++"

namespace MazeWars
{
    void randomlyRemoveWall( 
        sf::Vector2i position,
        MazeGrid &mazeGrid,
        float randomness
    )
    {
        if ( randomFloat(0,1) < randomness )
        {
            Direction direction = Direction( randomInt( North, West ) );

            if ( mazeGrid.inBounds( transposePosition( position, direction ) ) )
            {
                mazeGrid.setCell( 
                    position, 
                    direction, 
                    false 
                );
            }
        }
    }

    Direction getRandomValidDirection( 
        sf::Vector2i position, 
        MazeGrid &mazeGrid, 
        const std::vector<std::vector<bool>> &isSearched 
    )
    {
        std::vector<Direction> validDirections = {};

        forEachDirection( direction )
        {
            sf::Vector2i transposedPosition = transposePosition( position, direction );

            // If the position is in bounds, and it hasn't been searched, add it to our list.
            if ( mazeGrid.inBounds( transposedPosition ) && !isSearched[ transposedPosition.x ][ transposedPosition.y ] )
                validDirections.push_back( direction );
        }

        // If theres no valid directions, return NoDirection
        if ( validDirections.empty() )
            return NoDirection;
        
        // Select a random direction from the list.
        return validDirections[ randomInt( 0, validDirections.size() - 1 ) ];
    }

    void generateMazeDepthFirst( 
        MazeGrid &mazeGrid, 
        float randomness, 
        std::size_t seed
    )
    {
        sf::Vector2i position = {0,0};
        std::vector<sf::Vector2i> positionStack = {{0,0}};
        std::vector<std::vector<bool>> isSearched;

        isSearched.resize( mazeGrid.getDimensions().x, std::vector<bool>( mazeGrid.getDimensions().y, false ) );
        positionStack.reserve(mazeGrid.getDimensions().x*mazeGrid.getDimensions().y);

        while ( true )
        {
            isSearched[position.x][position.y] = true;
            Direction direction = getRandomValidDirection( position, mazeGrid, isSearched );

            if ( direction == NoDirection )
            {
                // No direction to go, need to backtrack
                positionStack.pop_back();

                if ( positionStack.empty() )
                    break;
                
                position = positionStack[positionStack.size()-1];
            }
            else
            {
                mazeGrid.setCell( position, direction, false );
                position = transposePosition( position, direction );
                positionStack.push_back( position );
                randomlyRemoveWall( position, mazeGrid, randomness );
            }
        }
    }
}


// File: Main\MazeWars\src\mazeGrid.c++

#include "mazeGrid.h++"
#include "assert.h++"
#include "draw.h++"

namespace MazeWars
{
    MazeGrid::MazeGrid( sf::Vector2i dimensions )
    {
        resize( dimensions );
    }

    MazeGrid::~MazeGrid()
    {
        horizontalSegments.clear();
        verticalSegments.clear();
    }

    sf::Vector2i MazeGrid::getDimensions() const
    {
        return this->dimensions;
    }

    bool MazeGrid::inBounds( sf::Vector2i position )  const
    {
        return 0 <= position.x && position.x < getDimensions().x &&
            0 <= position.y && position.y < getDimensions().y;
    }

    std::size_t MazeGrid::getNumberOfWalls() const
    {
        return this->numberOfWalls;
    }

    std::size_t MazeGrid::getNumberOfHorizontalSegments() const
    {
        return getDimensions().x * (getDimensions().y+1);
    }

    std::size_t MazeGrid::getNumberOfVerticalSegments() const
    {
        return (getDimensions().x+1) * getDimensions().y;
    }

    std::size_t MazeGrid::getNumberOfWallSegments() const
    {
        return getNumberOfHorizontalSegments() + getNumberOfVerticalSegments();
    }

    bool MazeGrid::getHorizontal( sf::Vector2i position ) const
    {
        assert( 
            std::size_t(position.x+position.y*getDimensions().x) < getNumberOfHorizontalSegments(),
            "Cannot access a horizontal wall segment that doesn't exist"
        );

        return this->horizontalSegments[position.x+position.y*getDimensions().x];
    }

    bool MazeGrid::getVertical( sf::Vector2i position ) const
    {
        assert( 
            std::size_t(position.x+position.y*getDimensions().x) < getNumberOfVerticalSegments(),
            "Cannot access a vertical wall segment that doesn't exist"
        );

        return this->verticalSegments[position.x+position.y*(getDimensions().x+1)];
    }

    bool MazeGrid::getCell( 
        sf::Vector2i position, 
        Direction direction 
    ) const
    {
        switch( direction )
        {
            case North:
                return getHorizontal( { position.x, position.y+1 } );
                break;
                
            case East:
                return getVertical( { position.x+1, position.y } );
                break;
                
            case South:
                return getHorizontal( { position.x, position.y } );
                break;
                
            case West:
                return getVertical( { position.x, position.y } );
                break;

            default:
                throw std::runtime_error( "Direction can only be: North, East, South, West" );
                break;
        }
    }

    void MazeGrid::set( 
        std::vector<bool> horizontalSegments, 
        std::vector<bool> verticalSegments 
    )
    {
        assert( 
            horizontalSegments.size() == getNumberOfHorizontalSegments() &&
            verticalSegments.size() == getNumberOfVerticalSegments(),
            "Dimensions do not match" 
        );

        // The passed in parameters will be inverted on the y axis, and thus needs to be reversed.
        this->horizontalSegments.clear();

        for ( int horizontalIndex = 0; horizontalIndex < ( getDimensions().y + 1 ); horizontalIndex++ )
        {
            this->horizontalSegments.insert(
                this->horizontalSegments.begin(), 
                horizontalSegments.begin() + ( horizontalIndex ) * getDimensions().x, 
                horizontalSegments.begin() + ( horizontalIndex + 1 ) * getDimensions().x
            );
        }

        this->verticalSegments.clear();

        for ( int verticalIndex = 0; verticalIndex < getDimensions().y; verticalIndex++ )
        {
            this->verticalSegments.insert(
                this->verticalSegments.begin(), 
                verticalSegments.begin() + verticalIndex * ( getDimensions().x + 1 ), 
                verticalSegments.begin() + ( verticalIndex + 1 ) * ( getDimensions().x + 1)
            );
        }

        this->numberOfWalls =
            std::count(
                this->horizontalSegments.begin(),
                this->horizontalSegments.end(), 
                true
            ) + 
            std::count(
                this->verticalSegments.begin(),
                this->verticalSegments.end(), 
                true
            );
    }

    void MazeGrid::fill( bool value )
    {
        std::fill( 
            this->horizontalSegments.begin(), 
            this->horizontalSegments.end(),
            value            
        );
        std::fill( 
            this->verticalSegments.begin(), 
            this->verticalSegments.end(),
            value            
        );

        this->numberOfWalls = value ? getNumberOfWallSegments() : 0;
    }

    void MazeGrid::resize( sf::Vector2i dimensions )
    {
        assert( 
            dimensions.x > 0 &&
            dimensions.y > 0,
            "Dimensions must be positive" 
        );

        this->dimensions = dimensions;
        this->numberOfWalls = getNumberOfWallSegments();

        this->horizontalSegments.resize(
            getNumberOfHorizontalSegments()
        );
        this->verticalSegments.resize(
            getNumberOfVerticalSegments()
        );

        fill( true );
    }

    void MazeGrid::setHorizontal( 
        sf::Vector2i position, 
        bool value 
    )
    {
        if ( getHorizontal(position) != value )
        {
            // If the value is true, we have just added a wall, therefore we need to add 1 to the number of walls
            // Else the value is false, and we have just removed a wall, therefore we need to minus 1.
            this->numberOfWalls += value == true ? 1 : -1;
            this->horizontalSegments[position.x+position.y*getDimensions().x] = value;
        }
    }

    void MazeGrid::setVertical( 
        sf::Vector2i position, 
        bool value 
    )
    {
        if ( getVertical(position) != value )
        {
            // If the value is true, we have just added a wall, therefore we need to add 1 to the number of walls
            // Else the value is false, and we have just removed a wall, therefore we need to minus 1.
            this->numberOfWalls += value == true ? 1 : -1;
            this->verticalSegments[position.x+position.y*(getDimensions().x+1)] = value;
        }
    }

    void MazeGrid::setCell( 
        sf::Vector2i position,
        Direction direction, 
        bool value 
    )
    {
        switch( direction )
        {
            case North:
                setHorizontal( { position.x, position.y+1 }, value );
                break;
                
            case East:
                setVertical( { position.x+1, position.y }, value );
                break;
                
            case South:
                setHorizontal( { position.x, position.y }, value );
                break;
                
            case West:
                setVertical( { position.x, position.y }, value );
                break;

            default:
                throw std::runtime_error( "Direction can only be: North, East, South, West" );
                break;
        }
    }

    void drawMaze( 
        sf::RenderWindow &window, 
        MazeGrid &maze, 
        sf::Vector2f topLeft, 
        sf::Vector2f bottomRight, 
        std::vector<sf::Vector2i> markers
    )
    {
        // Create a vertex array with double the number of vertices as the number of walls
        // ( As each wall is comprised of two vertices )
        sf::VertexArray vertexArray( sf::PrimitiveType::Lines, maze.getNumberOfWalls()*2 );
        float xSegmentSize = ( bottomRight.x - topLeft.x ) / maze.getDimensions().x;
        float ySegmentSize = ( bottomRight.y - topLeft.y ) / maze.getDimensions().y;

        // Loop through each horizontal wall
        for ( int xIndex = 0; xIndex < maze.getDimensions().x; xIndex++ )
        {
            for ( int yIndex = 0; yIndex < (maze.getDimensions().y+1); yIndex++ )
            {
                if ( maze.getHorizontal( { xIndex, yIndex } ) )
                {
                    appendLineToArray( vertexArray,
                        sf::Vector2f( 
                            topLeft.x + xIndex * xSegmentSize,
                            bottomRight.y - yIndex * ySegmentSize
                        ), 
                        sf::Vector2f( 
                            topLeft.x + ( xIndex + 1 ) * xSegmentSize,
                            bottomRight.y - ( yIndex ) * ySegmentSize
                        ),
                        sf::Color::Green
                    );
                }
            }
        }

        // Loop through each vertical wall
        for ( int xIndex = 0; xIndex < (maze.getDimensions().x+1); xIndex++ )
        {
            for ( int yIndex = 0; yIndex < maze.getDimensions().y; yIndex++ )
            {
                if ( maze.getVertical( { xIndex, yIndex } ) )
                {
                    appendLineToArray( vertexArray,
                        sf::Vector2f( 
                            topLeft.x + xIndex * xSegmentSize,
                            bottomRight.y - yIndex * ySegmentSize
                        ), 
                        sf::Vector2f( 
                            topLeft.x + ( xIndex ) * xSegmentSize,
                            bottomRight.y - ( yIndex + 1 ) * ySegmentSize
                        ),
                        sf::Color::Green
                    );
                }
            }
        }
        
        window.draw( vertexArray );
        
        for ( sf::Vector2i marker: markers )
        {
            sf::RectangleShape markerRectangle = sf::RectangleShape({xSegmentSize/2.f,ySegmentSize/2.f});

            markerRectangle.setPosition( 
                sf::Vector2f(marker.x*xSegmentSize,-marker.y*ySegmentSize) + sf::Vector2f(50+xSegmentSize/4.f,750-(3*ySegmentSize)/4.f) 
            );

            window.draw( markerRectangle );
        }
    }
}


// File: Main\MazeWars\src\mazeWars.c++

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
        setRandomNumberSeed( timeNow().time_since_epoch().count() );
        
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

                case sf::Keyboard::Escape:
                    getPlayer()->kill();
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


// File: Main\MazeWars\src\renderer.c++

#include "renderer.h++"
#include "Entity/entity.h++"

namespace MazeWars
{
    bool Renderer::hasBeenDrawnOn( int xIndex ) const
    {
        assert(
            xIndex >= 0 &&
            std::size_t(xIndex) < getDisplaySize().x,
            "Index out of range"
        );

        return this->drawnOn[xIndex];
    }

    bool Renderer::canDrawInRange(
        float startIndex,
        float endIndex
    ) const
    {
        assert(
            startIndex <= endIndex,
            "Start index must be less than the end index"
        );

        startIndex = std::max( 0.f, startIndex );
        endIndex = std::min( endIndex, getDisplaySize().x - 1.f );

        for ( int index = startIndex; index <= endIndex; index++ )
        {
            if ( !hasBeenDrawnOn(index) )
                return true;
        }

        return false;
    }

    void Renderer::setHasBeenDrawnOn(
        int xIndex,
        bool value
    )
    {
        assert(
            xIndex >= 0 &&
            std::size_t(xIndex) < getDisplaySize().x,
            "Index out of range"
        );

        this->drawnOn[xIndex] = value;
    }

    void Renderer::setHasBeenDrawnOn(
        int startIndex,
        int endIndex,
        bool value
    )
    {
        assert(
            startIndex <= endIndex,
            "Start index must be less than the end index"
        );

        startIndex = std::max(0, startIndex);
        endIndex = std::min<int>( endIndex, getDisplaySize().x - 1 );

        if (startIndex <= endIndex)
            std::fill( drawnOn.begin() + startIndex, drawnOn.begin() + endIndex, value );
    }


    Renderer::Renderer( sf::Vector2u displaySize ): displaySize( displaySize ), 
                                                    yNear(0.1),
                                                    wallHeight(300),
                                                    camera(), 
                                                    wallVertices( sf::PrimitiveType::Lines )
    {

    }

    Camera &Renderer::getCamera()
    {
        return this->camera;
    }

    float Renderer::getYNear() const
    {
        return this->yNear;
    }

    sf::Vector2u Renderer::getDisplaySize() const
    {
        return this->displaySize;
    }

    bool Renderer::onScreen( float xValue ) const
    {
        return 0 <= xValue && xValue < getDisplaySize().x;
    }

    sf::Vector2f Renderer::clipLineToNearPlane( sf::Vector2f lineStart, sf::Vector2f lineEnd )
    {
        // A linear interpolation
        float delta = ( lineStart.y - getYNear() ) / ( lineStart.y - lineEnd.y );
        
        return { lineStart.x + ( lineEnd.x - lineStart.x ) * delta, getYNear() };
    }

    bool Renderer::projectPoint(
        sf::Vector2f &position,
        float &size
    )
    {
        //Getting relative position
        position = getCamera().relativePositionOf( position );

        // Clip near
        if ( position.y < getYNear() )
            return false;
        
        // Divide by distance to camera
        position.x /= position.y;

        // Stretch to match screen size and center on screen
        position.x *= ( getDisplaySize().x / 2 ) / tan( camera.getFov() / 2 );
        position.x += getDisplaySize().x / 2.f;

        size /= position.y * 2;

        // Test if off screen
        if ( position.x + size < 0  || position.x - size > getDisplaySize().x )
            return false;

        return true;
    }

    bool Renderer::projectLine(
        sf::Vector2f &lineStart,
        sf::Vector2f &lineEnd
    )
    {
        //Getting relative position
        lineStart = getCamera().relativePositionOf( lineStart );
        lineEnd = getCamera().relativePositionOf( lineEnd );

        // Clip near
        if ( lineStart.y < getYNear() && lineEnd.y < getYNear() )
            return false;
        else if ( lineStart.y < getYNear() )
        {
            lineStart = clipLineToNearPlane( lineStart, lineEnd );
        }
        else if ( lineEnd.y < getYNear() )
        {
            lineEnd = clipLineToNearPlane( lineStart, lineEnd );
        }

        // Divide by distance to camera
        lineStart.x /= lineStart.y;
        lineEnd.x /= lineEnd.y;

        // Making sure it's start to end not end to start
        if ( lineStart.x > lineEnd.x )
        {
            std::swap( lineStart, lineEnd );
        }

        // Stretch to match screen size and center on screen
        lineStart.x *= ( getDisplaySize().x / 2 ) / tan( camera.getFov() / 2 );
        lineStart.x += getDisplaySize().x / 2.f;
        lineEnd.x *= ( getDisplaySize().x / 2 ) / tan( camera.getFov() / 2 );
        lineEnd.x += getDisplaySize().x / 2.f;

        // Test if off screen
        if ( lineEnd.x < 0  || lineStart.x > getDisplaySize().x )
            return false;

        return true;
    }

    void Renderer::drawWallVertical(
        sf::Vector2f position
    )
    {
        if ( onScreen( position.x ) &&
            !hasBeenDrawnOn( std::floor( position.x ) ) )
        {
            float wallHeight = std::floor( this->wallHeight / position.y );
            
            appendLineToArray(
                wallVertices,
                sf::Vector2f(
                    std::floor(position.x),
                    ( getDisplaySize().y + wallHeight ) / 2
                ),
                sf::Vector2f(
                    std::floor(position.x),
                    ( getDisplaySize().y - wallHeight ) / 2
                ),
                sf::Color::Green
            );

            setHasBeenDrawnOn( position.x, true );
        }
    }

    void Renderer::drawWallHorizontals(
        sf::Vector2f &wallStart,
        sf::Vector2f &wallEnd
    )
    {
        float wallHeightDelta = ( std::floor( this->wallHeight / wallEnd.y ) - std::floor( this->wallHeight / wallStart.y ) ) / 
                                ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) );
        
        int wallStartX = std::floor( wallStart.x + 1 );
        float wallStartHeight = std::floor( this->wallHeight / wallStart.y ) + wallHeightDelta;
        
        if ( wallStartX < 0 )
        {
            wallStartHeight += wallHeightDelta * -( wallStartX );
            wallStartX = 0;
        }

        int wallEndX = std::min<int>( std::floor( wallEnd.x ), getDisplaySize().x - 1 );

        while ( true )
        {
            // Find the x value where the drawn on value changes
            bool wasDrawnOn = hasBeenDrawnOn( wallStartX );
            int index =
                std::min<int>(
                    std::distance(
                        drawnOn.begin(),
                        std::find(
                            drawnOn.begin() + wallStartX,
                            drawnOn.end() + wallEndX,
                            !wasDrawnOn
                        )
                    ),
                    wallEndX
                );

            // Get the corresponding height value for the given x.
            float wallHeight = wallStartHeight + wallHeightDelta * ( index - wallStartX );

            // If it was just on an undrawn section, draw the walls
            if ( wasDrawnOn == false )
            {
                appendLineToArray(
                    wallVertices,
                    sf::Vector2f(
                        wallStartX - 1,
                        ( getDisplaySize().y + std::floor( wallStartHeight - wallHeightDelta ) ) / 2
                    ),
                    sf::Vector2f(
                        index,
                        ( getDisplaySize().y + std::floor( wallHeight ) ) / 2
                    ),
                    sf::Color::Green
                );

                appendLineToArray(
                    wallVertices,
                    sf::Vector2f(
                        wallStartX - 1,
                        ( getDisplaySize().y - std::floor( wallStartHeight - wallHeightDelta ) ) / 2
                    ),
                    sf::Vector2f(
                        index,
                        ( getDisplaySize().y - std::floor( wallHeight ) ) / 2
                    ),
                    sf::Color::Green
                );
                
                setHasBeenDrawnOn( wallStartX, index, true );
            }

            if ( index >= wallEndX )
                return;

            wallStartX = index;
            wallStartHeight = wallHeight;
        }
    }

    void Renderer::drawWall(
        sf::Vector2f &wallStart,
        sf::Vector2f &wallEnd
    )
    {
        drawWallVertical(  wallStart );

        drawWallVertical( wallEnd );

        // If it's one or two pixels thin we can stop
        if ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) <= 1 )
            return;

        drawWallHorizontals( wallStart, wallEnd );
    }

    void Renderer::drawEntity(
        Entity *entity
    )
    {
        sf::Vector2f position =
            sf::Vector2f( entity->getPosition() ) +
            sf::Vector2f(0.5,0.5);

        float size = entity->getSize();

        if ( projectPoint( position, size ) )
        {
            int entityImageStartX = std::floor( position.x - size );
            float entityTextureStartX = 0;
            float entityTextureDelta = entity->getTexture()->getSize().x / ( size * 2 );

            if ( entityImageStartX < 0 )
            {
                entityTextureStartX += -( entityImageStartX ) * entityTextureDelta;
                entityImageStartX = 0;
            }
        
            int entityImageEndX = std::min<int>( std::floor( position.x + size ), getDisplaySize().x - 1 );

            while ( true )
            {
                bool wasDrawnOn = hasBeenDrawnOn( entityImageStartX );
                int index =
                    std::min<int>(
                        std::distance(
                            drawnOn.begin(),
                            std::find(
                                drawnOn.begin() + entityImageStartX,
                                drawnOn.end() + entityImageEndX,
                                !wasDrawnOn
                            )
                        ),
                        entityImageEndX
                    );
                float entityTextureEndX = entityTextureStartX + (index - entityImageStartX) * entityTextureDelta;

                if ( wasDrawnOn == false )
                {
                    sf::RectangleShape entityRectangle(
                        {
                            float( index -  entityImageStartX ),
                            size * 2
                        }
                    );
                    entityRectangle.setPosition(
                        {
                            float( entityImageStartX ),
                            ( getDisplaySize().y ) / 2 - size
                        }
                    );
                    entityRectangle.setTexture( entity->getTexture() );
                    entityRectangle.setTextureRect(
                        sf::IntRect(
                            {
                                int( entityTextureStartX ),
                                0
                            },
                            {
                                int( entityTextureEndX - entityTextureStartX ),
                                int( entity->getTexture()->getSize().y )
                            }
                        )
                    );
                    this->entityRectangles.push_back(entityRectangle);
                }

                if ( index >= entityImageEndX )
                    return;

                entityImageStartX = index;
                entityTextureStartX = entityTextureEndX;
            }
        }
    }

    void Renderer::render(
        sf::RenderWindow& window,
        MazeGrid &mazeGrid,
        const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
        Id playerId
    )
    {
        std::queue<sf::Vector2i> cellsToVisit;
        cellsToVisit.push( camera.getPosition() );

        std::vector<std::vector<bool>> visitedCells;
        visitedCells.assign(
            mazeGrid.getDimensions().x,
            std::vector<bool>(
                mazeGrid.getDimensions().y,
                false
            )
        );

        wallVertices.clear();
        this->entityRectangles.clear();

        drawnOn.resize( getDisplaySize().x );
        std::fill(
            drawnOn.begin(),
            drawnOn.end(),
            false
        );


        while ( !cellsToVisit.empty() )
        {
            sf::Vector2i currentCell = cellsToVisit.front(); cellsToVisit.pop();
            visitedCells[currentCell.x][currentCell.y] = true;

            std::vector<Entity*> entitiesInCell = entityGrid[currentCell.x][currentCell.y];

            for ( Entity *entity: entitiesInCell )
            {
                if ( entity->getId() != playerId && !entity->isDead() )
                    drawEntity( entity );
            }

            forEachDirection( direction )
            {
                bool isWallInDirection = mazeGrid.getCell( currentCell, direction );

                sf::Vector2f wallStart =
                    sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                    rotatePosition({-0.5, 0.5}, direction);
                sf::Vector2f wallEnd =
                    sf::Vector2f(currentCell.x + 0.5, currentCell.y + 0.5 ) +
                    rotatePosition({0.5, 0.5}, direction);

                if ( !projectLine( wallStart, wallEnd ) )
                    continue;

                // If theres no space to draw anything why are we going to bother with any other checks
                if ( !canDrawInRange( wallStart.x, wallEnd.x ) )
                    continue;

                if ( isWallInDirection )
                {
                    // If there's a wall, just draw it and continue with next loop.
                    drawWall( wallStart, wallEnd );
                }
                else
                {
                    // Else try to add the connected cell to the cellsToVisit
                    sf::Vector2i connectedCell =
                        transposePosition(
                            currentCell,
                            direction
                        );
                    
                    if ( mazeGrid.inBounds( connectedCell ) &&
                            !visitedCells[connectedCell.x][connectedCell.y] )
                    {
                        cellsToVisit.push( connectedCell );
                    }
                }
            }
        }

        window.draw( wallVertices );
        
        // This ensures that the entities draw in the correct order
        std::reverse( this->entityRectangles.begin(), this->entityRectangles.end() );
        for ( sf::RectangleShape &entityRectangle: this->entityRectangles )
        {
            window.draw( entityRectangle );
        }
    }
}


// File: Main\BattleZone\include\battleZone.h++

#if !defined( BZ_BATTLE_ZONE_HPP )
#define BZ_BATTLE_ZONE_HPP

    #include "Entity/entityBase.h++"
    #include "Render/renderer.h++"
    #include "time.h++"
    #include "random.h++"
    #include "draw.h++"
    #include <iostream>
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

#endif /* BZ_BATTLE_ZONE_HPP */


// File: Main\BattleZone\include\Entity\bullet.h++

#if !defined( BZ_BULLET_HPP )
#define BZ_BULLET_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Bullet: public Entity
        {
            Id ownerId;

            public:
                Bullet( Id ownerId, sf::Vector2f position = {0,0}, float rotation = 0 );

                Id getOwnerId() const;

                virtual CollisionRect getCollisionRect() const override;

                virtual void update( BattleZoneGame &game ) override;
        };
    }

#endif /* BZ_BULLET_HPP */


// File: Main\BattleZone\include\Entity\collisionRect.h++

#if !defined( BZ_COLLISION_RECT_HPP )
#define BZ_COLLISION_RECT_HPP

    #include "vector.h++"
    #include <algorithm>

    namespace BattleZone
    {
        class CollisionRect
        {
            sf::Vector2f center;
            sf::Vector2f dimensions;
            float rotation;

            public:
                typedef std::vector<sf::Vector2f> PolygonPoints;
                struct Projection
                {
                    float min;
                    float max;

                    bool contains( Projection projection2 ) const;
                };

                CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation = 0 );

                sf::Vector2f getCenter() const;
                sf::Vector2f getDimensions() const;
                float getRotation() const;
                PolygonPoints getPoints() const;

                void setCenter( sf::Vector2f position );
                void setDimensions( sf::Vector2f dimensions );
                void setRotation( float rotation );

                static Projection getProjection( 
                    const PolygonPoints &rect, 
                    sf::Vector2f projectionVector
                );

                static bool overlappingOnVector( 
                    const PolygonPoints &rect1, 
                    const PolygonPoints &rect2, 
                    sf::Vector2f projectionVector
                );

                static bool isColliding(
                    const CollisionRect &rect1, 
                    const CollisionRect &rect2 
                );
        };
    }

#endif /* BZ_COLLISION_RECT_HPP */


// File: Main\BattleZone\include\Entity\entity.h++

#if !defined( BZ_ENTITY_HPP )
#define BZ_ENTITY_HPP

    #include "entityBase.h++"
    #include "collisionRect.h++"
    #include <functional>

    namespace BattleZone
    {
        class Entity
        {
            protected:
                Model3D *model;
                sf::Vector2f position;
                float rotation;
                int health;
                Id id;
                bool dead;
                EntityType type;

            public:
                Entity( sf::Vector2f position = {0,0} );

                sf::Vector2f getPosition() const;
                float getRotation() const;
                int getHealth() const;
                Id getId() const;
                bool isDead() const;
                EntityType getType() const;
                Model3D *getModel();
                virtual CollisionRect getCollisionRect() const;

                void setPosition( sf::Vector2f position );
                void setRotation( float rotation );
                void setHealth( int health );
                void setId( Id id );

                void moveForward( float distance );
                void turnLeft( float angle );
                void turnRight( float angle );
                void damage( int amount );
                void kill();

                sf::Vector2f relativePositionOf( sf::Vector2f position );

                static std::vector<Entity*> getColliding( 
                    Entity *entity, 
                    sf::Vector2f offset, 
                    const std::map<Id,Entity*> &entities, 
                    std::function<bool(Entity*)> filter = []( Entity *entity){return true;}
                );

                virtual void update( BattleZoneGame &game );
        };
    }

#endif /* BZ_ENTITY_HPP */


// File: Main\BattleZone\include\Entity\entityBase.h++

#if !defined( BZ_ENTITY_BASE_HPP )
#define BZ_ENTITY_BASE_HPP

    #include "SFML/Graphics.hpp"
    #include "Render/model3D.h++"

    namespace BattleZone
    {
        class BattleZoneGame;

        typedef int Id;
        extern const Id NullId;

        extern Model3D tankModel;
        extern Model3D obstacleModel;
        extern Model3D bulletModel;

        extern bool loadEntityAssets();

        enum EntityType
        {
            NoType,
            TankType,
            ObstacleType,
            BulletType,
            PlayerType
        };

        class Entity;
    }
    
#endif /* BZ_ENTITY_BASE_HPP */


// File: Main\BattleZone\include\Entity\obstacle.h++

#if !defined( BZ_OBSTACLE_HPP )
#define BZ_OBSTACLE_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Obstacle: public Entity
        {
            public:
                Obstacle( sf::Vector2f position = {0,0} );
        
                virtual CollisionRect getCollisionRect() const override;
        };
    }

#endif /* BZ_OBSTACLE_HPP */


// File: Main\BattleZone\include\Entity\player.h++

#if !defined( BZ_PLAYER_HPP )
#define BZ_PLAYER_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Player: public Entity
        {
            public:
                Player( sf::Vector2f position = {0,0} );
                
                virtual CollisionRect getCollisionRect() const override;
        };
    }

#endif /* BZ_PLAYER_HPP */


// File: Main\BattleZone\include\Entity\tank.h++

#if !defined( BZ_TANK_HPP )
#define BZ_TANK_HPP

    #include "Entity/entity.h++"

    namespace BattleZone
    {
        class Tank: public Entity
        {
            int reloadCooldown;

            public:
                Tank( sf::Vector2f position = {0,0} );

                virtual CollisionRect getCollisionRect() const override;

                virtual void update( BattleZoneGame &game ) override;
        };
    }

#endif /* BZ_TANK_HPP */


// File: Main\BattleZone\include\mainLoop.h++

#if !defined ( BZ_MAIN_LOOP_HPP )
#define BZ_MAIN_LOOP_HPP

    #include "SFML/Graphics.hpp"
    #include "time.h++"
    #include "battleZone.h++"
    #include "Entity/entity.h++"
    #include "Entity/tank.h++"
    #include "Entity/obstacle.h++"
    #include "Entity/bullet.h++"

    namespace BattleZone
    {
        extern const float targetWidth;
        extern const float targetHeight;

        void handleResize( 
            sf::RenderWindow &window,
            float windowWidth, 
            float windowHeight
        );

        void handleInputs( sf::RenderWindow &window, BattleZoneGame &game );
        
        void mainLoop( sf::RenderWindow &window );
        void deathScreenLoop( sf::RenderWindow &window );
    }
    
#endif /* BZ_MAIN_LOOP_HPP */


// File: Main\BattleZone\include\Render\camera.h++

#if !defined( BZ_CAMERA_HPP )
#define BZ_CAMERA_HPP

    #include "vector.h++"

    namespace BattleZone
    {
        class Camera
        {
            sf::Vector3f position;
            float yaw;
            float pitch;
            float roll;
            float fov;
            
            public:
                Camera();

                sf::Vector3f getPosition() const;
                float getYaw() const;
                float getPitch() const;
                float getRoll() const;
                float getFov() const;

                void setPosition( sf::Vector3f position );
                void setYaw( float yaw );
                void setPitch( float pitch );
                void setRoll( float roll );
                void setFov( float fov );

                void moveForward( float distance );

                sf::Vector3f relativePositionOf( sf::Vector3f position );
        };
    }
    
#endif /* BZ_CAMERA_HPP */


// File: Main\BattleZone\include\Render\line.h++

#if !defined( BZ_LINE_HPP )
#define BZ_LINE_HPP
    
    #include <SFML/System.hpp>

    namespace BattleZone
    {
        struct LineVertex
        {
            sf::Vector3f position = { 0, 0, 0 };
        };

        class Line
        {
            LineVertex vertices[2];
            public:
                LineVertex getVertex( int index ) const;
                sf::Vector3f getVertexPosition( int index ) const;

                void setVertex( int index, LineVertex vertex );
                void setVertexPosition( int index, sf::Vector3f position );
        };
    }

#endif /* BZ_LINE_HPP */


// File: Main\BattleZone\include\Render\model3D.h++

#if !defined( BZ_MODEL_3D_HPP )
#define BZ_MODEL_3D_HPP

    #include <fstream>
    #include <vector>
    #include <string>
    #include "Render/triangle.h++"
    #include "Render/line.h++"
    #include "vector.h++"

    namespace BattleZone
    {
        class Model3D
        {
            std::vector<Triangle> triangles;
            std::vector<Line> lines;
            public:
                struct Transformations 
                {
                    float yaw = 0;
                    float pitch = 0;
                    float roll = 0;
                    sf::Vector3f position = {0,0,0};
                    sf::Vector3f rotationOrigin = {0,0,0};

                    public:
                        Transformations( 
                            float yaw = 0, 
                            float pitch = 0, 
                            float roll = 0, 
                            sf::Vector3f position = {0,0,0},
                            sf::Vector3f rotationOrigin = {0,0,0}
                        ): yaw(yaw), pitch(pitch), roll(roll), position(position), rotationOrigin(rotationOrigin)
                        {
                        }

                        sf::Vector3f apply( sf::Vector3f position ) const;
                };
                
                Model3D();
                Model3D( std::string path );

                const Triangle& getTriangle( std::size_t index ) const;
                const Line& getLine( std::size_t index ) const;

                std::size_t getTriangleCount() const; 
                std::size_t getLineCount() const;

                void setTriangle( std::size_t index, Triangle triangle );
                void setTriangle( std::size_t index, Line line );

                void importFromFile( std::string path );

                int parseFile( std::ifstream& file,
                                std::vector<sf::Vector3f>& vertices,
                                std::vector<sf::Vector3f>& verticesNormal,
                                std::vector<std::vector<std::size_t>>& faces,
                                std::vector<std::vector<std::size_t>>& lines );

                static bool parseVectorString( std::istringstream &stream, sf::Vector3f &vector );

                bool parseLine( std::string line,
                                std::vector<sf::Vector3f>& vertices,
                                std::vector<sf::Vector3f>& verticesNormal,
                                std::vector<std::vector<std::size_t>>& faces,
                                std::vector<std::vector<std::size_t>>& lines );

                bool processData( std::vector<sf::Vector3f>& vertices,
                                std::vector<sf::Vector3f>& verticesNormal,
                                std::vector<std::vector<std::size_t>>& faces,
                                std::vector<std::vector<std::size_t>>& lines );
        };
    }

#endif /* BZ_MODEL_3D_HPP */


// File: Main\BattleZone\include\Render\renderer.h++

#if !defined( BZ_RENDERER_HPP )
#define BZ_RENDERER_HPP

    #include "Render/camera.h++"
    #include "Render/model3D.h++"
    #include "Entity/entityBase.h++"
    #include <SFML/Graphics.hpp>

    namespace BattleZone
    {
        extern sf::Texture mountains;
        extern sf::Texture crosshair;

        extern bool loadAssets();

        class Renderer
        {
            const sf::Vector2u displaySize;
            const float zNear;
            const float mountainHeight;
            sf::VertexArray lineVertices;
            Camera camera;

            public:
                Renderer( sf::Vector2u displaySize );

                Camera& getCamera();
                float getZNear() const;
                sf::Vector2u getDisplaySize() const;

                sf::Vector3f clipLineToNearPlane( 
                    const sf::Vector3f& lineStart, 
                    const sf::Vector3f& lineEnd 
                );

                bool projectLine( 
                    sf::Vector3f& lineStart,
                    sf::Vector3f& lineEnd
                );

                void drawTriangle( 
                    const Triangle& triangle, 
                    const Model3D::Transformations& transformations = {} 
                );

                void drawLine( 
                    const Line& line, 
                    const Model3D::Transformations& transformations = {} 
                );

                void draw( 
                    Model3D *model, 
                    Model3D::Transformations transformations = {} 
                );

                void drawEntity( Entity *entity );
                
                void clear();
                void drawBackground( sf::RenderWindow& window );
                void drawCrosshair( sf::RenderWindow& window );
                void display( sf::RenderWindow& window );
        };
    }

#endif /* BZ_RENDERER_HPP */


// File: Main\BattleZone\include\Render\triangle.h++

#if !defined( BZ_TRIANGLE_HPP )
#define BZ_TRIANGLE_HPP
    
    #include <SFML/System.hpp>

    namespace BattleZone
    {
        struct TriangleVertex
        {
            sf::Vector3f position = { 0, 0, 0 };
            sf::Vector3f normal = { 0, 0, 0 };
        };

        class Triangle
        {
            TriangleVertex vertices[3];
            public:
                TriangleVertex getVertex( int index ) const;
                sf::Vector3f getVertexPosition( int index ) const;
                sf::Vector3f getVertexNormal( int index ) const;

                void setVertex( int index, TriangleVertex vertex );
                void setVertexPosition( int index, sf::Vector3f position );
                void setVertexNormal( int index, sf::Vector3f normal );
        };
    }

#endif /* BZ_TRIANGLE_HPP */


// File: Main\BattleZone\include\vector.h++

#if !defined( BZ_VECTOR_HPP )
#define BZ_VECTOR_HPP    
    
    #include <SFML/System.hpp>
    #define _USE_MATH_DEFINES
    #include <cmath>
    #include <vector>

    namespace BattleZone
    {
        float normaliseAngle( float angle );
        
        sf::Vector2f rotatePosition( sf::Vector2f position, float angle );

        sf::Vector3f rotatePosition( sf::Vector3f position, float yaw, float pitch = 0, float roll = 0 );

        sf::Vector2f get2DUnitVector( float angle );

        sf::Vector2f getRandom2DUnitVector();

        sf::Vector3f get3DUnitVector( float angle );

        sf::Vector3f getRandom3DUnitVector();

        float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 );

        float vectorLength( sf::Vector2f vector );
    }
    
#endif /* BZ_VECTOR_HPP */ 


// File: Main\BattleZone\src\battleZone.c++

#include "battleZone.h++"
#include "Entity/entity.h++"
#include "Entity/player.h++"
#include "Entity/bullet.h++"
#include "Entity/tank.h++"
#include "Entity/obstacle.h++"


namespace BattleZone
{
    BattleZoneGame::BattleZoneGame( sf::Vector2u displaySize ): renderer(displaySize)
    {
        setRandomNumberSeed( timeNow().time_since_epoch().count() );
        
        this->nextId = 0;

        this->playerId = 
            addEntity(
                new Player( { 0,0 } ) 
            );
            
        this->playerKills = 0;
    }

    BattleZoneGame::~BattleZoneGame()
    {
        for ( std::pair<Id, Entity*> idEntityPair : this->entities )
        {
            delete idEntityPair.second;
        }

        this->entities.clear();
    }

    Camera &BattleZoneGame::getCamera() { return this->renderer.getCamera(); }

    Entity *BattleZoneGame::getEntity( Id id ) { return this->entities[id]; }

    const std::map<Id, Entity*> &BattleZoneGame::getEntities() { return this->entities; }

    Entity *BattleZoneGame::getPlayer() { return getEntity( this->playerId ); }

    Id BattleZoneGame::addEntity( Entity* entity )
    {
        Id entityId = nextId++;
        this->entities[entityId] = entity;
        entity->setId( entityId );
        return entityId;
    }

    void BattleZoneGame::addPlayerKill() { this->playerKills++; }

    bool BattleZoneGame::canMoveInDirection( Entity *entity, float distance )
    {
        std::vector<Entity*> collidingEntities = 
            Entity::getColliding(
                entity, 
                distance * get2DUnitVector( getPlayer()->getRotation() ), 
                getEntities(),
                [ this ]( Entity *entity ) { return entity->getType() != BulletType; } 
            );
        
        return collidingEntities.empty();
    }

    void BattleZoneGame::cleanUpEntities()
    {
        for ( auto iterator = this->entities.begin(); iterator != this->entities.end(); )
        {
            Entity *entity = (*iterator).second;
            sf::Vector2f relativePositionToPlayer = entity->getPosition() - getPlayer()->getPosition();
            float distanceToPlayer = vectorLength( relativePositionToPlayer );
            
            if ( ( entity->isDead() || distanceToPlayer > 30 ) && entity->getType() != PlayerType )
            {
                delete (*iterator).second;
                iterator = this->entities.erase( iterator );
            }
            else
            {
                iterator++;
            }
        }
    }

    void BattleZoneGame::attemptToSpawnEntities()
    {
        int numberOfTanks =
            std::count_if(
                this->entities.begin(),
                this->entities.end(),
                []( const std::pair<Id, Entity*> idEntityPair )
                {
                    return idEntityPair.second->getType() == TankType;
                }
            );

        while ( numberOfTanks < 4 )
        {
            float spawnAngle = randomFloat( 0, 2 * M_PI );
            sf::Vector2f spawnLocation = getPlayer()->getPosition() + 
                20.f * get2DUnitVector( spawnAngle );
            addEntity( new Tank( spawnLocation ) );
            numberOfTanks++;
        }

        int numberOfObstacles = 
            std::count_if(
                this->entities.begin(),
                this->entities.end(),
                []( const std::pair<Id, Entity*> idEntityPair )
                {
                    return idEntityPair.second->getType() == ObstacleType;
                }
            );

        while ( numberOfObstacles < 10 )
        {
            float spawnAngle = randomFloat( 0, 2 * M_PI );
            sf::Vector2f spawnLocation = getPlayer()->getPosition() + 
                20.f * get2DUnitVector( spawnAngle );
            addEntity( new Obstacle( spawnLocation ) );
            numberOfObstacles++;
        }
    }

    void BattleZoneGame::handleInput( sf::Event &event )
    {
        if ( event.type == sf::Event::KeyPressed )
        {
            if ( event.key.code == sf::Keyboard::Space )
                addEntity(
                    new Bullet(
                        getPlayer()->getId(),
                        getPlayer()->getPosition(),
                        getPlayer()->getRotation()
                    ) 
                );

            if ( event.key.code == sf::Keyboard::Escape )
                getPlayer()->kill();
        }
    }

    void BattleZoneGame::update( sf::RenderWindow &window )
    {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
            getPlayer()->turnLeft( M_PI/100 );
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
            getPlayer()->turnRight( M_PI/100 );
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) && canMoveInDirection( getPlayer(), 0.08 ) )
            getPlayer()->moveForward( 0.08 );
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) && canMoveInDirection( getPlayer(), -0.08 ) )
            getPlayer()->moveForward( -0.08 );

        getCamera().setPosition( { getPlayer()->getPosition().x, 0.85, getPlayer()->getPosition().y } );
        getCamera().setYaw( getPlayer()->getRotation() );

        for ( std::pair<Id, Entity*> idEntityPair: entities )
        {
            if ( !idEntityPair.second->isDead() )
            {
                idEntityPair.second->update( *this );
            }
        }

        cleanUpEntities();
        attemptToSpawnEntities();
    }

    void BattleZoneGame::drawGUI( sf::RenderWindow &window )
    {
        renderer.drawCrosshair( window );

        sf::Text text("Health:"+std::to_string(getPlayer()->getHealth())+"\nScore:"+std::to_string(this->playerKills),gameFont,40);
        text.setOrigin( {text.getGlobalBounds().width/2.f,0} );
        text.setPosition( {(3*renderer.getDisplaySize().x)/4.f, 10} );
        window.draw( text );
    }

    void BattleZoneGame::render( sf::RenderWindow &window )
    {
        renderer.clear();
        
        renderer.drawBackground( window );

        for ( std::pair<Id, Entity*> idEntityPair: entities )
        {
            if ( idEntityPair.first != getPlayer()->getId() )
                renderer.drawEntity( idEntityPair.second );
        }

        drawGUI( window );

        renderer.display( window );
    }
}


// File: Main\BattleZone\src\Entity\bullet.c++

#include "Entity/bullet.h++"
#include "battleZone.h++"

namespace BattleZone
{
    Bullet::Bullet( Id ownerId, sf::Vector2f position, float rotation ): Entity( position )
    {
        this->type = BulletType;
        this->model = &bulletModel;
        this->ownerId = ownerId;
        setRotation( rotation );
    }

    Id Bullet::getOwnerId() const
    {
        return this->ownerId;
    }

    CollisionRect Bullet::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {0.1,0.3}, getRotation() );
    }

    void Bullet::update( BattleZoneGame &game )
    {
        std::vector<Entity *> collidingEntities = 
            getColliding( 
                this,
                0.1f * get2DUnitVector( getRotation() ), 
                game.getEntities(), 
                [ this ]( Entity *entity) { 
                    if ( entity->getType() == BulletType )
                        return static_cast<Bullet*>( entity )->getOwnerId() != getOwnerId();
                    return entity->getId() != getOwnerId();
                }
            );
        
        if ( !collidingEntities.empty() )
        {
            for ( Entity* entity: collidingEntities )
            {
                entity->damage( 1 );
                if ( entity->isDead() && entity->getType() == TankType && getOwnerId() == game.getPlayer()->getId() )
                    game.addPlayerKill();
            }
            kill();
            return;
        }

        moveForward( 0.1 );
    }
}


// File: Main\BattleZone\src\Entity\collisionRect.c++

#include "Entity/collisionRect.h++"

namespace BattleZone
{
    bool CollisionRect::Projection::contains( Projection projection2 ) const
    {
        return ( min <= projection2.min && projection2.min <= max ) ||
            ( min <= projection2.max && projection2.max <= max );
    }

    sf::Vector2f CollisionRect::getCenter() const { return this->center; }

    sf::Vector2f CollisionRect::getDimensions() const { return this->dimensions; }

    float CollisionRect::getRotation() const { return this->rotation; }

    void CollisionRect::setCenter( sf::Vector2f position ) { this->center = position; }

    void CollisionRect::setDimensions( sf::Vector2f dimensions ) { this->dimensions = dimensions; }

    void CollisionRect::setRotation( float rotation ) { this->rotation = rotation; }

    CollisionRect::CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation )
    {
        setCenter(center);
        setDimensions(dimensions);
        setRotation(rotation);
    }

    CollisionRect::PolygonPoints CollisionRect::getPoints() const
    {
        return {
            center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
            center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
            center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
            center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
        };
    }

    CollisionRect::Projection CollisionRect::getProjection( const PolygonPoints &rect, sf::Vector2f projectionVector )
    {
        std::vector<float> dots;
        for ( std::size_t index = 0; index < rect.size(); index++ )
        {
            dots.push_back(vectorDot( rect[index], projectionVector ));
        }

        return {*std::min_element(dots.begin(),dots.end()), *std::max_element(dots.begin(),dots.end())};
    }

    bool CollisionRect::overlappingOnVector( const PolygonPoints &rect1, const PolygonPoints &rect2, sf::Vector2f projectionVector )
    {
        Projection projection1 = getProjection(rect1, projectionVector);
        Projection projection2 = getProjection(rect2, projectionVector);

        return projection1.contains(projection2) || projection2.contains(projection1);
    }

    inline bool invalidNormal( sf::Vector2f vector )
    {
        return vector.x + 0.0f == 0.0f && vector.y + 0.0f == 0.0f;
    }

    bool CollisionRect::isColliding( const CollisionRect &rect1, const CollisionRect &rect2 )
    {
        PolygonPoints selfPoints = rect1.getPoints();
        PolygonPoints rectPoints = rect2.getPoints();

        std::vector<sf::Vector2f> normals = { 
            { -(selfPoints[0].y - selfPoints[1].y), selfPoints[0].x - selfPoints[1].x },
            { -(selfPoints[1].y - selfPoints[2].y), selfPoints[1].x - selfPoints[2].x },
            { -(rectPoints[0].y - rectPoints[1].y), rectPoints[0].x - rectPoints[1].x },
            { -(rectPoints[1].y - rectPoints[2].y), rectPoints[1].x - rectPoints[2].x }
        };

        normals.erase( std::remove_if(
            normals.begin(),
            normals.end(), 
            invalidNormal
        ), normals.end() );

        if ( normals.empty() )
            return false;

        for ( sf::Vector2f normal: normals )
        {
            bool overlapping = overlappingOnVector(selfPoints,rectPoints,normal);
            if ( !overlapping )
            {
                return false;
            }
        }

        return true;
    }
}


// File: Main\BattleZone\src\Entity\entity.c++

#include "Entity/entity.h++"
#include "battleZone.h++"
#include "file.h++"

namespace BattleZone
{
    const Id NullId = -1;

    Model3D tankModel;
    Model3D obstacleModel;
    Model3D bulletModel;

    bool loadEntityAssets()
    {
        setWorkingDirectoryToDefault();

        tankModel.importFromFile( "BattleZone/tank.obj" );
        obstacleModel.importFromFile( "BattleZone/pyramid.obj" );
        bulletModel.importFromFile( "BattleZone/bullet.obj" );

        return true;
    }

    Entity::Entity( sf::Vector2f position )
    {
        this->position = position;
        this->rotation = 0;
        this->health = 1;
        this->id = NullId;
        this->dead = false;
        this->type = NoType;
        this->model = nullptr;
    }

    sf::Vector2f Entity::getPosition() const { return this->position; }

    float Entity::getRotation() const { return this->rotation; }

    int Entity::getHealth() const { return this->health; }

    Id Entity::getId() const { return this->id; }

    bool Entity::isDead() const { return this->dead; }

    EntityType Entity::getType() const { return this->type; }

    Model3D *Entity::getModel() { return this->model; }

    CollisionRect Entity::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {0,0}, getRotation() );
    }

    void Entity::setPosition( sf::Vector2f position ) { this->position = position; }

    void Entity::setRotation( float rotation ) { this->rotation = normaliseAngle( rotation ); }

    void Entity::setHealth( int health ) { this->health = health; }

    void Entity::setId( Id id ) { this->id = id; }

    void Entity::moveForward( float distance )
    {
        setPosition(
            getPosition() + distance * get2DUnitVector( getRotation() )
        );
    }

    void Entity::turnLeft( float angle )
    {
        setRotation( getRotation() - angle );
    }

    void Entity::turnRight( float angle )
    {
        setRotation( getRotation() + angle );
    }

    void Entity::damage( int amount )
    {
        setHealth( std::max( getHealth() - amount, 0 ) );

        if ( getHealth() <= 0 )
            kill();
    }

    void Entity::kill()
    {
        this->dead = true;
    }

    sf::Vector2f Entity::relativePositionOf( sf::Vector2f position )
    {
        return rotatePosition( 
            position - getPosition(),
            normaliseAngle( -getRotation() )
        );
    }

    std::vector<Entity*> Entity::getColliding( Entity *entity, sf::Vector2f offset, const std::map<Id,Entity*> &entities, std::function<bool(Entity*)> filter )
    {
        CollisionRect collisionRect = entity->getCollisionRect();
        collisionRect.setCenter( collisionRect.getCenter() + offset );
        
        std::vector<Entity*> collidingEntities;
        for ( const std::pair<const Id, Entity*> &idEntityPair: entities )
        {
            if ( !idEntityPair.second->isDead() && idEntityPair.first != entity->getId() && filter( idEntityPair.second ) )
            {
                if ( CollisionRect::isColliding( collisionRect, idEntityPair.second->getCollisionRect() ) )
                {
                    collidingEntities.push_back( idEntityPair.second );
                }
            }
        }

        return collidingEntities;
    }

    void Entity::update( BattleZoneGame &game )
    {

    }
}


// File: Main\BattleZone\src\Entity\obstacle.c++

#include "Entity/obstacle.h++"

namespace BattleZone
{
    Obstacle::Obstacle( sf::Vector2f position ): Entity( position )
    {
        this->type = ObstacleType;
        this->model = &obstacleModel;
        this->health = 1000;
    }

    CollisionRect Obstacle::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {1,1}, getRotation() );
    }
}


// File: Main\BattleZone\src\Entity\player.c++

#include "Entity/player.h++"

namespace BattleZone
{
    Player::Player( sf::Vector2f position ): Entity( position )
    {
        this->type = PlayerType;
        this->health = 10;
    }

    CollisionRect Player::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {1,1}, getRotation() );
    }
}


// File: Main\BattleZone\src\Entity\tank.c++

#include "Entity/tank.h++"
#include "Entity/bullet.h++"
#include "battleZone.h++"
#include <iostream>

namespace BattleZone
{
    Tank::Tank( sf::Vector2f position ): Entity( position )
    {
        this->type = TankType;
        this->model = &tankModel;
        this->reloadCooldown = 0;
    }

    CollisionRect Tank::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {1,2}, getRotation() );
    }

    void Tank::update( BattleZoneGame &game )
    {
        if ( this->reloadCooldown > 0)
        {
            this->reloadCooldown--;
        }

        sf::Vector2f relativePosition = relativePositionOf( game.getPlayer()->getPosition() );

        float angleOffset = atan2( relativePosition.x, relativePosition.y );

        // To the right 
        if ( angleOffset > M_PI/100.f )
        {
            turnRight( M_PI/200.f );
        }
        else if ( angleOffset < -M_PI/100.f )
        {
            turnLeft( M_PI/200.f );
        }
        else
        {
            if ( game.canMoveInDirection( this, 0.03 ) )
                moveForward( 0.03 );

            if ( this->reloadCooldown == 0 )
            {
                game.addEntity( new Bullet( getId(), getPosition(), getRotation() ) );
                this->reloadCooldown = 120;
            }
        }
    }
}


// File: Main\BattleZone\src\main.c++

#include "mainLoop.h++"

using namespace BattleZone;

int main()
{
    sf::RenderWindow window( sf::VideoMode(1600,900), "BattleZone" );
    
    mainLoop( window );

    return 0;
}


// File: Main\BattleZone\src\mainLoop.c++

#include "mainLoop.h++"

namespace BattleZone
{
    const float targetWidth = 1600;
    const float targetHeight = 900;

    void handleResize( 
        sf::RenderWindow &window,
        float windowWidth, 
        float windowHeight
    )
    {
        float ratio = windowWidth/windowHeight;
        float targetRatio = targetWidth/targetHeight;
        sf::FloatRect visibleArea(0, 0, targetWidth, targetHeight);
        
        if ( ratio > targetRatio )
        {
            float offset = targetWidth*(ratio/targetRatio-1);
            visibleArea = sf::FloatRect(-offset/2, 0, targetWidth+offset, targetHeight);
        }
        else if ( ratio < targetRatio )
        {
            float offset = targetHeight*(targetRatio/ratio-1);
            visibleArea = sf::FloatRect(0, -offset/2, targetWidth, targetHeight+offset);
        }
        window.setView(sf::View(visibleArea));
    }

    void handleInputs( sf::RenderWindow &window, BattleZoneGame &game )
    {
        sf::Event event;
        // For each event
        while ( window.pollEvent(event) )
        {
            // Handle appropriately
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::Resized:
                    handleResize(window, (float) event.size.width, (float) event.size.height);
                    break;
                
                default:
                    game.handleInput(event);
                    break;
            }
        }
    }

    void mainLoop( sf::RenderWindow &window )
    {
        handleResize( window, window.getSize().x, window.getSize().y );
        window.setTitle( "BattleZone" );
        window.setKeyRepeatEnabled(false);

        if ( !loadEntityAssets() || !loadAssets() )
            return;

        FpsLimiter fps( 60 );

        BattleZoneGame game( {1600,900} );
        
        while (window.isOpen() && !game.getPlayer()->isDead())
        {
            handleInputs( window, game );
            game.update( window );

            window.clear( sf::Color::Black );

            game.render( window );

            window.display();
            fps.restartAndSleep();
        }

        BattleZone::deathScreenLoop( window );
    }

    void deathScreenLoop( sf::RenderWindow &window )
    {
        bool keyPressed = false;
        while (window.isOpen() && !keyPressed)
        {
            sf::Event event;
            while ( window.pollEvent(event) )
            {
                switch ( event.type )
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    
                    case sf::Event::Resized:
                        handleResize(window, (float) event.size.width, (float) event.size.height);
                        break;

                    case sf::Event::KeyPressed:
                        keyPressed = true;
                        break;
                    
                    default:
                        break;
                }
            }

            window.clear( sf::Color::Black );
            drawTextCentered(
                window,
                "GAME OVER", gameFont, 60,
                {targetWidth/2.f, targetHeight/2.f - 60},
                sf::Color::Green
            );
            drawTextCentered(
                window,
                "PRESS ANY KEY TO CONTINUE", gameFont, 30,
                {targetWidth/2.f, targetHeight/2.f + 60},
                sf::Color::Green
            );
            window.display();
        }
    }
}


// File: Main\BattleZone\src\Render\camera.c++

#include "Render/camera.h++"

namespace BattleZone
{
    Camera::Camera()
    {
        this->position = {0,0,0};
        this->yaw = 0;
        this->pitch = 0;
        this->roll = 0;
        this->fov = M_PI / 2;
    }

    sf::Vector3f Camera::getPosition() const
    {
        return this->position;
    }

    float Camera::getYaw() const
    {
        return this->yaw;
    }

    float Camera::getPitch() const
    {
        return this->pitch;
    }

    float Camera::getRoll() const
    {
        return this->roll;
    }

    float Camera::getFov() const
    {
        return this->fov;
    }

    void Camera::setPosition( sf::Vector3f position )
    {
        this->position = position;
    }

    void Camera::setYaw( float yaw )
    {
        this->yaw = normaliseAngle( yaw );
    }

    void Camera::setPitch( float pitch )
    {
        this->pitch = normaliseAngle( pitch );
    }

    void Camera::setRoll( float roll )
    {
        this->roll = normaliseAngle( roll );
    }

    void Camera::setFov( float fov )
    {
        this->fov = fov;
    }

    void Camera::moveForward( float distance )
    {
        setPosition( getPosition() + distance * get3DUnitVector( getYaw() ) );
    }

    sf::Vector3f Camera::relativePositionOf( sf::Vector3f position )
    {
        return rotatePosition( 
            position - getPosition(),
            normaliseAngle( -getYaw() ),
            normaliseAngle( -getPitch() ),
            normaliseAngle( -getRoll() )
        );
    }
}


// File: Main\BattleZone\src\Render\line.c++

#include <Render/line.h++>

namespace BattleZone
{
    LineVertex Line::getVertex( int index ) const { return this->vertices[index % 2]; }

    void Line::setVertex( int index, LineVertex vertex ) { this->vertices[index % 2] = vertex; }

    sf::Vector3f Line::getVertexPosition( int index ) const { return getVertex( index ).position; }

    void Line::setVertexPosition( int index, sf::Vector3f position ) { this->vertices[index % 2].position = position; }
}


// File: Main\BattleZone\src\Render\model3D.c++

#include "Render/model3D.h++"
#include "file.h++"
#include "assert.h++"

namespace BattleZone
{
    sf::Vector3f Model3D::Transformations::apply( sf::Vector3f position ) const
    {
        return 
            rotatePosition( 
                position - this->rotationOrigin,
                this->yaw,
                this->pitch,
                this->roll
            ) + this->rotationOrigin + this->position;
    };

    Model3D::Model3D() {}

    Model3D::Model3D( std::string path )
    {
        importFromFile( path );
    }

    const Triangle& Model3D::getTriangle( std::size_t index ) const { return this->triangles[index]; }

    void Model3D::setTriangle( std::size_t index, Triangle triangle ) { this->triangles[index] = triangle; }

    const Line& Model3D::getLine( std::size_t index ) const { return this->lines[index]; }

    void Model3D::setTriangle( std::size_t index, Line line ) { this->lines[index] = line; }

    std::size_t Model3D::getTriangleCount() const { return this->triangles.size(); }

    std::size_t Model3D::getLineCount() const { return this->lines.size(); }

    void Model3D::importFromFile( std::string path )
    {
        std::vector<sf::Vector3f> vertices;
        std::vector<sf::Vector3f> verticesNormal;
        std::vector<std::vector<std::size_t>> faces;
        std::vector<std::vector<std::size_t>> lines;
        this->triangles.clear();
        this->lines.clear();

        setWorkingDirectoryToDefault();
        // Open the file in input mode
        std::ifstream file( path );
        assert( file.is_open(), "Error opening file: " + getWorkingDirectory() +"/" + path );

        int lineError = parseFile( file, vertices, verticesNormal, faces, lines );
        assert( lineError == -1, "Error reading file: "+path+", line: "+std::to_string( lineError ) );

        file.close();

        assert( processData( vertices, verticesNormal, faces, lines ), "Error processing file: "+path );
    }

    int Model3D::parseFile( std::ifstream& file,
                    std::vector<sf::Vector3f>& vertices,
                    std::vector<sf::Vector3f>& verticesNormal,
                    std::vector<std::vector<std::size_t>>& faces,
                    std::vector<std::vector<std::size_t>>& lines )
    {
        int index = 0;
        std::string line;
        // Keep getting the next line until it returns false (Meaning there is no next line)
        while ( getline( file, line ) )
        {
            // Keep track of which line index we are on.
            index++;
            // If the parseLine function returns a false, indicating a failure, end the loop.
            if ( !parseLine( line, vertices, verticesNormal, faces, lines ) )
            {
                return index;
            }
        }

        // Return -1 indicating no error.
        return -1;
    }

    bool Model3D::parseVectorString( std::istringstream &stream, sf::Vector3f &vector )
    {
        std::string value;
        // Retrieve the next value using the >> stream operator
        // If the >> operator returns false it means that an invalid value was found
        if ( !(stream >> value) ) { return false; } vector.x = std::stof( value );
        if ( !(stream >> value) ) { return false; } vector.y = std::stof( value );
        if ( !(stream >> value) ) { return false; } vector.z = std::stof( value );

        // Everything was successful!
        return true;
    }

    bool Model3D::parseLine( std::string line,
                    std::vector<sf::Vector3f>& vertices,
                    std::vector<sf::Vector3f>& verticesNormal,
                    std::vector<std::vector<std::size_t>>& faces,
                    std::vector<std::vector<std::size_t>>& lines )
    {
        std::istringstream stream( line );
        std::string identifier; stream >> identifier;

        if ( identifier == "v" )
        {
            sf::Vector3f position;
            if ( !parseVectorString( stream, position ) ) return false;

            vertices.push_back( position );
        }
        else if ( identifier == "vn" )
        {
            sf::Vector3f normal;
            if ( !parseVectorString( stream, normal ) ) return false;

            verticesNormal.push_back( normal );
        }
        else if ( identifier == "f" )
        {
            faces.push_back( {} );
            while ( stream >> identifier )
            {
                // For now just retrieve the first value, the vertex value.
                // If I implement the Star Wars Arcade Game, i can add further code to fetch the normal data.
                std::size_t end = identifier.find( '/' );
                if ( end == std::string::npos ) end = identifier.size();
                std::string number = identifier.substr(0, end);
                if ( number == "" ) return false;
                faces.back().push_back( std::stoi( number ) );
            }
            if ( faces.back().size() < 3 )
                return false;
        }
        else if ( identifier == "l" )
        {
            lines.push_back( {} );
            while ( stream >> identifier )
            {
                lines.back().push_back( std::stoi( identifier ) );
            }
            if ( lines.back().size() < 2 )
                return false;
        }

        // Everything was successful!
        return true;
    }

    bool Model3D::processData( std::vector<sf::Vector3f>& vertices,
                        std::vector<sf::Vector3f>& verticesNormal,
                        std::vector<std::vector<std::size_t>>& faces,
                        std::vector<std::vector<std::size_t>>& lines )
    {
        // Iterate through each face
        for ( std::size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++ )
        {
            // Fan triangulation
            for ( std::size_t vertexIndex = 1; vertexIndex < faces[faceIndex].size() - 1; vertexIndex++ )
            {
                this->triangles.push_back( Triangle() );
                this->triangles.back().setVertexPosition( 0, vertices[ faces[faceIndex][0] - 1 ] );
                this->triangles.back().setVertexPosition( 1, vertices[ faces[faceIndex][vertexIndex] - 1 ] );
                this->triangles.back().setVertexPosition( 2, vertices[ faces[faceIndex][vertexIndex + 1] - 1 ] );
            }
        }

        // Iterate through each line
        for ( std::size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++ )
        {
            for ( std::size_t vertexIndex = 0; vertexIndex < lines[lineIndex].size() - 1; vertexIndex++ )
            {
                this->lines.push_back( Line() );
                this->lines.back().setVertexPosition( 0, vertices[ lines[lineIndex][vertexIndex] - 1 ] );
                this->lines.back().setVertexPosition( 1, vertices[ lines[lineIndex][vertexIndex+1] - 1 ] );
            }
        }

        return true;
    }
}


// File: Main\BattleZone\src\Render\renderer.c++

#include "Render/renderer.h++"
#include "Entity/entity.h++"
#include "draw.h++"

namespace BattleZone
{
    sf::Texture mountains;
    sf::Texture crosshair;

    bool loadAssets()
    {
        if ( !loadBaseAssets() )
            return false;
        
        if ( !mountains.loadFromFile( "BattleZone/mountains.png" ) )
            return false;
        
        mountains.setRepeated( true );
        
        if ( !crosshair.loadFromFile( "BattleZone/crosshair.png" ) )
            return false;

        return true;
    }

    Renderer::Renderer( sf::Vector2u displaySize ): displaySize(displaySize), 
                                                    zNear( 0.01f ), 
                                                    mountainHeight( 150 ),
                                                    lineVertices( sf::PrimitiveType::Lines ), 
                                                    camera()
    {
    }

    Camera& Renderer::getCamera() { return camera; }

    float Renderer::getZNear() const { return this->zNear; }
                
    sf::Vector2u Renderer::getDisplaySize() const { return this->displaySize; }

    sf::Vector3f Renderer::clipLineToNearPlane( const sf::Vector3f& lineStart, const sf::Vector3f& lineEnd  )
    {
        float delta = ( lineStart.z - getZNear() ) / ( lineStart.z - lineEnd.z );
        
        return { lineStart.x + ( lineEnd.x - lineStart.x) * delta, lineStart.y + ( lineEnd.y - lineStart.y) * delta, getZNear() };
    }

    bool Renderer::projectLine( 
        sf::Vector3f& lineStart,
        sf::Vector3f& lineEnd
    )
    {
        //Getting relative position
        lineStart = getCamera().relativePositionOf( lineStart );
        lineEnd = getCamera().relativePositionOf( lineEnd );

        // Clip near
        if ( lineStart.z < getZNear() && lineEnd.z < getZNear() )
            return false;
        else if ( lineStart.z < getZNear() )
        {
            lineStart = clipLineToNearPlane( lineStart, lineEnd );
        }
        else if ( lineEnd.z < getZNear() )
        {
            lineEnd = clipLineToNearPlane( lineStart, lineEnd );
        }

        lineStart.x /= lineStart.z;
        lineEnd.x /= lineEnd.z;
        lineStart.y /= lineStart.z;
        lineEnd.y /= lineEnd.z;

        lineStart.x = lineStart.x * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.x / 2.f;
        lineEnd.x = lineEnd.x * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.x / 2.f;

        //Y axis is inverted
        lineStart.y = -lineStart.y * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.y / 2.f;
        lineEnd.y = -lineEnd.y * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.y / 2.f;

        return true;
    }

    void Renderer::drawTriangle(
        const Triangle& triangle, 
        const Model3D::Transformations& transformations 
    )
    {
        sf::Vector3f lineStart, lineEnd;
        for ( int index = 0; index < 3; index++ )
        {
            lineStart = transformations.apply( triangle.getVertexPosition( index ) );
            lineEnd = transformations.apply( triangle.getVertexPosition( index + 1 ) );
            if ( projectLine( lineStart, lineEnd ) )
            {
                appendLineToArray( lineVertices, { lineStart.x, lineStart.y }, { lineEnd.x, lineEnd.y }, sf::Color::Green );
            }
        }
    }

    void Renderer::drawLine(
        const Line& line, 
        const Model3D::Transformations& transformations 
    )
    {
        sf::Vector3f lineStart = transformations.apply( line.getVertexPosition( 0 ) );
        sf::Vector3f lineEnd = transformations.apply( line.getVertexPosition( 1 ) );
        if ( projectLine( lineStart, lineEnd ) )
        {
            appendLineToArray( lineVertices, { lineStart.x, lineStart.y }, { lineEnd.x, lineEnd.y }, sf::Color::Green );
        }
    }

    void Renderer::draw(
        Model3D *model, 
        Model3D::Transformations transformations 
    )
    {
        for ( std::size_t index = 0; index < model->getTriangleCount(); index++ )
        {
            drawTriangle( model->getTriangle(index), transformations );
        }

        for ( std::size_t index = 0; index < model->getLineCount(); index++ )
        {
            drawLine( model->getLine(index), transformations );
        }
    }

    void Renderer::drawEntity( Entity *entity )
    {
        if ( !entity->isDead() )
        {
            sf::Vector3f position = { entity->getPosition().x, 0, entity->getPosition().y };
            draw( entity->getModel(), { entity->getRotation(), 0, 0, position } );
        }
    }

    void Renderer::drawBackground( sf::RenderWindow& window )
    {
        int textureWidth = std::floor( mountains.getSize().x * 3 * ( camera.getFov() / ( 2*M_PI ) ) );
        int textureOffset = std::floor(
            mountains.getSize().x * 3 * ( normaliseAngle( camera.getYaw() ) / ( 2*M_PI ) ) - textureWidth/2.f 
        );

        sf::RectangleShape background( {(float)displaySize.x, (float)this->mountainHeight} );
        // Center on screen
        background.setPosition({0,displaySize.y/2.f-this->mountainHeight});
        background.setTexture( &mountains );

        // This function sets which part of the mountains to display
        background.setTextureRect( sf::IntRect({textureOffset,0},{textureWidth, (int) mountains.getSize().y}) );

        window.draw( background );
    }

    void Renderer::drawCrosshair( sf::RenderWindow& window )
    {
        sf::RectangleShape crosshairRect(sf::Vector2f(crosshair.getSize())*2.f);

        crosshairRect.setOrigin(crosshairRect.getSize()/2.f);
        crosshairRect.setPosition(sf::Vector2f(displaySize)/2.f);
        crosshairRect.setTexture(&crosshair);

        window.draw(crosshairRect);
    }

    void Renderer::clear()
    {
        lineVertices.clear();
    }

    void Renderer::display( sf::RenderWindow& window )
    {
        window.draw( lineVertices );
    }
}


// File: Main\BattleZone\src\Render\triangle.c++

#include "Render/triangle.h++"
namespace BattleZone
{
    TriangleVertex Triangle::getVertex( int index ) const { return this->vertices[index % 3]; }

    void Triangle::setVertex( int index, TriangleVertex vertex ) { this->vertices[index % 3] = vertex; }

    sf::Vector3f Triangle::getVertexPosition( int index ) const { return getVertex( index ).position; }

    void Triangle::setVertexPosition( int index, sf::Vector3f position ) { this->vertices[index % 3].position = position; }

    sf::Vector3f Triangle::getVertexNormal( int index ) const { return getVertex( index ).normal; }

    void Triangle::setVertexNormal( int index, sf::Vector3f normal ) { this->vertices[index % 3].normal = normal; }
}


// File: Main\BattleZone\src\vector.c++

#include "vector.h++"
#include "random.h++"

namespace BattleZone
{
    float normaliseAngle( float angle )
    {
        angle = std::fmod( angle, 2 * M_PI );

        if ( angle < 0 )
            angle += 2*M_PI;
        
        return angle;
    }

    sf::Vector2f rotatePosition( sf::Vector2f position, float angle )
    {
        // The 2D rotation matrix
        return {
            static_cast<float>( 
                position.x*cos( angle ) + position.y*sin( angle ) 
            ),
            static_cast<float>( 
                - position.x*sin( angle ) + position.y*cos( angle )
            )
        };
    }

    sf::Vector3f xRotationMatrix( sf::Vector3f position, float angle )
    {
        return {
            position.x,
            position.y * cos( angle ) + position.z * sin( angle ),
            - position.y * sin( angle ) + position.z * cos( angle ) 
        };
    }

    sf::Vector3f yRotationMatrix( sf::Vector3f position, float angle )
    {
        return { 
            position.x * cos( angle ) + position.z * sin( angle ),
            position.y,
            - position.x * sin( angle ) + position.z * cos( angle )
        };  
    }

    sf::Vector3f zRotationMatrix( sf::Vector3f position, float angle )
    {
        return {
            position.x * cos( angle ) - position.y * sin ( angle ),
            position.x * sin( angle ) + position.y * cos( angle ),
            position.z
        };
    }

    sf::Vector3f rotatePosition( sf::Vector3f position, float yaw, float pitch, float roll )
    {
        return 
        xRotationMatrix(
            yRotationMatrix( 
                zRotationMatrix( 
                    position,
                    roll
                ),
                yaw
            ),
            pitch 
        );
    }

    sf::Vector2f get2DUnitVector( float angle )
    {
        return { sin( angle ), cos( angle ) };
    }

    sf::Vector2f getRandom2DUnitVector()
    {
        return get2DUnitVector( randomFloat( 0, M_PI * 2 ) );
    }

    sf::Vector3f get3DUnitVector( float angle )
    {
        return { sin( angle ), 0, cos( angle ) };
    }

    sf::Vector3f getRandom3DUnitVector()
    {
        return get3DUnitVector( randomFloat( 0, M_PI * 2 ) );
    }

    float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 )
    {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    float vectorLength( sf::Vector2f vector )
    {
        return sqrt( vector.x * vector.x + vector.y * vector.y );
    }
}


// File: Main\main.c++

#include "MazeWars/include/mainLoop.h++"
#include "BattleZone/include/mainLoop.h++"

sf::Texture instructionsTexture;

int main()
{
    sf::RenderWindow window( {1600,900}, "3D Rendering" );
    
    if (!loadBaseAssets())
       return 1;

    if ( !instructionsTexture.loadFromFile("instructions.png") )
        return 1;

    sf::Text instructions = 
        getTextCentered(
            "INSTRUCTIONS", gameFont, 60,
            {800, 250},
            sf::Color::Green
        );

    sf::Text mazeWarTitle = 
        getTextCentered(
            "MAZE WAR", gameFont, 60,
            {400, 550},
            sf::Color::Green
        );

    sf::Text battleZoneTitle = 
        getTextCentered(
            "BATTLEZONE", gameFont, 60,
            {1200,550},
            sf::Color::Green
        );

    while (window.isOpen())
    {
        sf::Event event;
        while ( window.pollEvent(event) )
        {
            switch ( event.type )
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::Resized:
                    BattleZone::handleResize( window, (float) event.size.width, (float) event.size.height );
                    break;

                case sf::Event::MouseButtonPressed:
                    if ( mazeWarTitle.getGlobalBounds().contains( window.mapPixelToCoords( sf::Mouse::getPosition(window) ) ) )
                    {
                        MazeWars::mainLoop( window );
                        BattleZone::handleResize( window, window.getSize().x, window.getSize().y );
                    }
                    if ( battleZoneTitle.getGlobalBounds().contains( window.mapPixelToCoords( sf::Mouse::getPosition(window) ) ) )
                    {
                        BattleZone::mainLoop( window );
                        BattleZone::handleResize( window, window.getSize().x, window.getSize().y );
                    }
                    if ( instructions.getGlobalBounds().contains( window.mapPixelToCoords( sf::Mouse::getPosition(window) ) ) )
                    {
                        sf::RectangleShape instructionsRect;
                        instructionsRect.setTexture( &instructionsTexture );
                        instructionsRect.setSize( {1600,900} );

                        bool end = false;
                        while ( !end )
                        {
                            while ( window.pollEvent(event) )
                            {
                                if ( event.type == sf::Event::Closed  )
                                {
                                    end = true;
                                    window.close();
                                }
                                    
                                if ( event.type == sf::Event::KeyPressed )
                                {
                                    end = true;
                                }
                            }

                            window.clear( sf::Color::Black );

                            window.draw( instructionsRect );

                            window.display();
                        }
                        break;
                    }
                    break;

                default:
                    break;
            }
        }

        window.clear( sf::Color::Black );

        window.draw( mazeWarTitle );
        window.draw( battleZoneTitle );
        window.draw( instructions );

        window.display();
    }

    return 0;
}