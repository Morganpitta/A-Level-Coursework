#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    typedef int Id;
    const Id NullId = -1;

    enum EntityType
    {
        NoType
    };

    class Entity
    {
        sf::Vector2i position = {0,0};
        Direction direction = North;
        int health = 0;
        Id id = NullId;
        bool dead = false;
        EntityType type = NoType;
        
        public:
            Entity()
            {
            }

            sf::Vector2i getPosition()
            {
                return this->position;
            }

            Direction getDirection()
            {
                return this->direction;
            }

            int getHealth()
            {
                return this->health;
            }

            Id getId()
            {
                return this->id;
            }

            bool isDead()
            {
                return this->dead;
            }

            EntityType getType()
            {
                return this->type;
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