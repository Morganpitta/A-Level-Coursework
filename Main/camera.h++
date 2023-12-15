#if !defined( CAMERA_HPP )
#define CAMERA_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    class Entity
    {
        sf::Vector2i position = {0,0};
        Direction direction = North;
        
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
                setPosition( transposePosition( getPosition(), getDirection() ) );
            }

            void turnLeft()
            {
                setDirection( Direction( ( getDirection() - 1 ) % NumberOfDirections ) );
            }

            void turnRight()
            {
                setDirection( Direction( ( getDirection() + 1 ) % NumberOfDirections ) );
            }

            sf::Vector2f relativePositionOf( sf::Vector2f position )
            {
                return sf::Vector2f( rotatePosition( position - sf::Vector2f( getPosition() ), getDirection() ) );
            }

            virtual void update()
            {
                
            }
    };
#endif /* CAMERA_HPP */