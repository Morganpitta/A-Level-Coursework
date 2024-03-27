#include "Entity/collisionRect.h++"

CollisionRect::PolygonPoints CollisionRect::getPoints() const
{
    return {
        center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
        center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
        center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
        center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
    };
}

inline bool invalidNormal( sf::Vector2f vector )
{
    return vector.x + 0.0f == 0.0f && vector.y + 0.0f == 0.0f;
}

bool CollisionRect::isColliding( const CollisionRect &rect1, const CollisionRect &rect2 )
{
    PolygonPoints selfPoints = rect1.getPoints();
    PolygonPoints rectPoints = rect2.getPoints();

    std::vector<sf::Vector2f> normals = { 
        { -(selfPoints[0].y - selfPoints[1].y), selfPoints[0].x - selfPoints[1].x },
        { -(selfPoints[1].y - selfPoints[2].y), selfPoints[1].x - selfPoints[2].x },
        { -(rectPoints[0].y - rectPoints[1].y), rectPoints[0].x - rectPoints[1].x },
        { -(rectPoints[1].y - rectPoints[2].y), rectPoints[1].x - rectPoints[2].x }
    };

    normals.erase( std::remove_if(
        normals.begin(),
        normals.end(), 
        invalidNormal
    ), normals.end() );

    if ( normals.size() == 0 )
        return false;

    for ( sf::Vector2f normal: normals )
    {
        bool overlapping = overlappingOnVector(selfPoints,rectPoints,normal);
        if ( !overlapping )
        {
            return false;
        }
    }

    return true;
}