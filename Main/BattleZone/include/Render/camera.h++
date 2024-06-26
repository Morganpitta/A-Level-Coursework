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