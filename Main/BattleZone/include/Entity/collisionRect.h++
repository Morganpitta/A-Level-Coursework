#if !defined ( COLLISION_RECT_HPP )
#define COLLISION_RECT_HPP

    #include "vector.h++"
    #include <algorithm>

    class CollisionRect
    {
        sf::Vector2f center;
        sf::Vector2f dimensions;
        float rotation;

        public:
            typedef std::vector<sf::Vector2f> PolygonPoints;

            CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation = 0 );

            sf::Vector2f getCenter() const;
            sf::Vector2f getDimensions() const;
            float getRotation() const;
            PolygonPoints getPoints() const;

            void setCenter( sf::Vector2f position );
            void setDimensions( sf::Vector2f dimensions );
            void setRotation( float rotation );

            static std::pair<float,float> minAndMaxPoints( 
                const PolygonPoints &rect, 
                sf::Vector2f projectionVector
            );

            static bool overlappingOnVector( 
                const PolygonPoints &rect1, 
                const PolygonPoints &rect2, 
                sf::Vector2f projectionVector
            );

            static bool isColliding(
                const CollisionRect &rect1, 
                const CollisionRect &rect2 
            );
    };

#endif /* COLLISION_RECT_HPP */