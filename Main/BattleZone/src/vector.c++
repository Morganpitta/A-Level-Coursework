#include "vector.h++"
#include "random.h++"

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
        position.x * cos( angle ) - position.z * sin( angle ),
        position.y,
        position.x * sin( angle ) + position.z * cos( angle )
    };  
}

sf::Vector3f zRotationMatrix( sf::Vector3f position, float angle )
{
    return {
        position.x * cos( angle ) + position.y * sin ( angle ),
        - position.x * sin( angle ) + position.y * cos( angle ),
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