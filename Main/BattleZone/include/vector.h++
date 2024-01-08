#if !defined( VECTOR_HPP )
#define VECTOR_HPP    
    
    #include <SFML/System.hpp>
    #define _USE_MATH_DEFINES
    #include <cmath>
    #include "random.h++"

    float normaliseAngle( float angle );

    sf::Vector3f rotatePosition( sf::Vector3f position, float angle );

    sf::Vector3f getUnitVector( float angle );

    sf::Vector3f getRandomUnitVector();

#endif /* VECTOR_HPP */ 