#include "vector.h++"

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
        position.z
    };
}

sf::Vector2f get2DUnitVector( float angle )
{
    return { cos( angle ), sin( angle ) };
}

sf::Vector2f getRandom2DUnitVector()
{
    return get2DUnitVector( randomFloat( 0, M_PI * 2 ) );
}

sf::Vector3f get3DUnitVector( float angle )
{
    return { cos( angle ), sin( angle ), 0 };
}

sf::Vector3f getRandom3DUnitVector()
{
    return get3DUnitVector( randomFloat( 0, M_PI * 2 ) );
}