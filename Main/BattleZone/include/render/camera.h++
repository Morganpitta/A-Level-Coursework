#if !defined( CAMERA_HPP )
#define CAMERA_HPP

    #include "vector.h++"

    class Camera
    {
        sf::Vector3f position;
        float rotation;
        float fov;
        
        public:
            Camera();

            sf::Vector3f getPosition() const;

            float getRotation() const;

            float getFov() const;

            void setPosition( sf::Vector3f position );

            void setRotation( float rotation );

            void setFov( float fov );

            void moveForward( float distance );

            void turnLeft( float angle );

            void turnRight( float angle );

            sf::Vector3f relativePositionOf( sf::Vector3f position );
    };
    
#endif /* CAMERA_HPP */