#if !defined( CAMERA_HPP )
#define CAMERA_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    class Camera
    {
        sf::Vector2i position = {0,0};
        Direction direction = North;
        float fov = M_PI/2;
        
        public:
            Camera()
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

            float getFov()
            {
                return this->fov;
            }

            void setPosition( sf::Vector2i position )
            {
                this->position = position;
            }

            void setDirection( Direction direction )
            {
                this->direction = direction;
            }

            void setFov( float fov )
            {
                this->fov = fov;
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
                return sf::Vector2f( rotatePosition( position - sf::Vector2f( getPosition().x+0.5, getPosition().y+0.5 ), Direction( ( int(South) + getDirection() ) % 4 ) ) );
            }
    };
#endif /* CAMERA_HPP */