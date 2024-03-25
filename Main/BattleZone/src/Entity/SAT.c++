#include <SFML/System.hpp>
#include "vector.h++"

class CollisionRect
{
    sf::Vector2f center;
    sf::Vector2f dimensions;
    float rotation;
    typedef std::vector<sf::Vector2f> PolygonPoints;

    public:
        CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation ): center(center), dimensions(dimensions), rotation(rotation)
        {
        }

        PolygonPoints toPoints() const
        {
            return {
                center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
                center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
                center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
                center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
            };
        }

        static std::pair<float,float> minAndMaxPoints( const PolygonPoints &rect, sf::Vector2f projectionVector )
        {
            std::vector<float> dots;
            for ( int index = 0; index < rect.size(); index++ )
            {
                dots.push_back(vectorDot( rect[index], projectionVector ));
            }

            return std::make_pair(*std::min_element(dots.begin(),dots.end()), *std::max_element(dots.begin(),dots.end()));
        }

        static float isCollidingOnVector( const PolygonPoints &rect1, const PolygonPoints &rect2, sf::Vector2f projectionVector )
        {
            std::pair<float,float> rect1MinAndMax = minAndMaxPoints(rect1, projectionVector);
            std::pair<float,float> rect2MinAndMax = minAndMaxPoints(rect2, projectionVector);

            return rect1MinAndMax.second > rect2MinAndMax.first || rect2MinAndMax.second > rect1MinAndMax.first;
        }

        bool isColliding( const CollisionRect &rect ) const
        {
            PolygonPoints selfPoints = toPoints();
            PolygonPoints rectPoints = rect.toPoints();

            std::vector<sf::Vector2f> normals = { 
                { -(selfPoints[0].y - selfPoints[1].y), selfPoints[0].x - selfPoints[1].x },
                { -(selfPoints[1].y - selfPoints[2].y), selfPoints[1].x - selfPoints[2].x },
                { -(rectPoints[0].y - rectPoints[1].y), rectPoints[0].x - rectPoints[1].x },
                { -(rectPoints[0].y - rectPoints[1].y), rectPoints[0].x - rectPoints[1].x }
            };

            for ( sf::Vector2f normal: normals )
            {
                isCollidingOnVector(selfPoints,rectPoints,normal);
            }
        }
};