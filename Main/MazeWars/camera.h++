#if !defined( CAMERA_HPP )
#define CAMERA_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    class Camera
    {
        sf::Vector2i position = {0,0};
        Direction direction = North;
        float fov = (1.65*M_PI)/3;
        
        public:
            Camera()
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

            float getFov() const
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
                setDirection( normaliseDirection( int(getDirection()) - 1 ) );
            }

            void turnRight()
            {
                setDirection( normaliseDirection( int(getDirection()) + 1 ) );
            }

            sf::Vector2f relativePositionOf( sf::Vector2f position )
            {
                return rotatePosition( 
                    position - sf::Vector2f( getPosition().x+0.5f, getPosition().y+0.5f ),
                    normaliseDirection( -getDirection() )
                );
            }
    };
    
#endif /* CAMERA_HPP */