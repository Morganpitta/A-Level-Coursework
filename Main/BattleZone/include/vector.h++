#if !defined( BZ_VECTOR_HPP )
#define BZ_VECTOR_HPP    
    
    #include <SFML/System.hpp>
    #define _USE_MATH_DEFINES
    #include <cmath>
    #include <vector>

    namespace BattleZone
    {
        float normaliseAngle( float angle );
        
        sf::Vector2f rotatePosition( sf::Vector2f position, float angle );

        sf::Vector3f rotatePosition( sf::Vector3f position, float yaw, float pitch = 0, float roll = 0 );

        sf::Vector2f get2DUnitVector( float angle );

        sf::Vector2f getRandom2DUnitVector();

        sf::Vector3f get3DUnitVector( float angle );

        sf::Vector3f getRandom3DUnitVector();

        float vectorDot( sf::Vector2f vector1, sf::Vector2f vector2 );

        float vectorLength( sf::Vector2f vector );
    }
    
#endif /* BZ_VECTOR_HPP */ 