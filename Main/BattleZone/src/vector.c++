#include "vector.h++"

float normaliseAngle( float angle )
{
    angle = std::fmod( angle, 2 * M_PI );

    if ( angle < 0 )
        angle += 2*M_PI;
    
    return angle;
}

sf::Vector3f rotatePosition( sf::Vector3f position, float angle )
{
    // The 2D rotation matrix
    return {
        static_cast<float>( 
            position.x*cos( angle ) + position.y*sin( angle ) 
        ),
        static_cast<float>( 
            - position.x*sin( angle ) + position.y*cos( angle )
        ),
        0
    };
}

sf::Vector3f getUnitVector( float angle )
{
    return { cos( angle ), sin( angle ), 0 };
}

sf::Vector3f getRandomUnitVector()
{
    return getUnitVector( randomFloat( 0, M_PI * 2 ) );
}