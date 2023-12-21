#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"
    #include "file.h++"

    typedef int Id;
    const Id NullId = -1;

    enum EntityType
    {
        NoType
    };

    sf::Texture EntityTexture;

    bool loadEntityAssets()
    {
        setWorkingDirectoryToDefault();

        if ( !EntityTexture.loadFromFile( "MazeWars/triangle.png" ) )
            return false;

        return true;
    }

    class Entity
    {
        sf::Vector2i position = {0,0};
        Direction direction = North;
        int health = 0;
        Id id = NullId;
        bool dead = false;
        EntityType type = NoType;
        sf::Texture *texture = &EntityTexture;
        
        public:
            Entity()
            {
            }

            sf::Vector2i getPosition() const
            {
                return this->position;
            }

            Direction getDirection() const
            {
                return this->direction;
            }

            int getHealth() const
            {
                return this->health;
            }

            Id getId() const
            {
                return this->id;
            }

            bool isDead() const
            {
                return this->dead;
            }

            EntityType getType() const
            {
                return this->type;
            }

            sf::Texture *getTexture() const
            {
                return this->texture;
            }

            void setPosition( sf::Vector2i position )
            {
                this->position = position;
            }

            void setDirection( Direction direction )
            {
                this->direction = direction;
            }

            void moveForward()
            {
                setPosition( 
                    transposePosition( 
                        getPosition(), 
                        getDirection() 
                    )
                );
            }

            void turnLeft()
            {
                setDirection( normaliseDirection( int(getDirection()) - 1 ) );
            }

            void turnRight()
            {
                setDirection( normaliseDirection( int(getDirection()) + 1 ) );
            }

            sf::Vector2i relativePositionOf( sf::Vector2i position )
            {
                return sf::Vector2i( rotatePosition( 
                    sf::Vector2f( position - getPosition() ),
                    normaliseDirection( -getDirection() )
                ) );
            }
            
            void setHealth( int health )
            {
                this->health = health;
            }

            void damage( int amount )
            {
                setHealth( std::max( getHealth() - amount, 0 ) );

                if ( getHealth() <= 0 )
                    kill();
            }

            void setId( Id id )
            {
                this->id = id;
            }

            void kill()
            {
                this->dead = true;
            }

            virtual void update()
            {

            }
    };

#endif /* ENTITY_HPP */