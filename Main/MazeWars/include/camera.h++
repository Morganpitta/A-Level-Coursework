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