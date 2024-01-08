#if !defined( VECTOR_HPP )
#define VECTOR_HPP    
    
    #include <SFML/System.hpp>
    #define _USE_MATH_DEFINES
    #include <cmath>
    #include "random.h++"

    float normaliseAngle( float angle );

    sf::Vector2f rotatePosition( sf::Vector2f position, float angle );

    sf::Vector2f getUnitVector( float angle );

    sf::Vector2f getRandomUnitVector();

#endif /* VECTOR_HPP */ 