#if !defined( VECTOR_HPP )
#define VECTOR_HPP    
    
    #include <SFML/System.hpp>
    #define _USE_MATH_DEFINES
    #include <cmath>
    #include "random.h++"

    float normaliseAngle( float angle );
    
    sf::Vector2f rotatePosition( sf::Vector2f position, float angle );

    sf::Vector3f rotatePosition( sf::Vector3f position, float angle );

    sf::Vector2f get2DUnitVector( float angle );
    
    sf::Vector2f getRandom2DUnitVector();

    sf::Vector3f get3DUnitVector( float angle );

    sf::Vector3f getRandom3DUnitVector();

#endif /* VECTOR_HPP */ 