#include "Entity/collisionRect.h++"

bool CollisionRect::Projection::contains( Projection projection2 ) const
{
    return min <= projection2.min && projection2.min <= max ||
           min <= projection2.max && projection2.max <= max; 
}

sf::Vector2f CollisionRect::getCenter() const { return this->center; }

sf::Vector2f CollisionRect::getDimensions() const { return this->dimensions; }

float CollisionRect::getRotation() const { return this->rotation; }

void CollisionRect::setCenter( sf::Vector2f position ) { this->center = position; }

void CollisionRect::setDimensions( sf::Vector2f dimensions ) { this->dimensions = dimensions; }

void CollisionRect::setRotation( float rotation ) { this->rotation = rotation; }

CollisionRect::CollisionRect( sf::Vector2f center, sf::Vector2f dimensions, float rotation )
{
    setCenter(center);
    setDimensions(dimensions);
    setRotation(rotation);
}

CollisionRect::PolygonPoints CollisionRect::getPoints() const
{
    return {
        center + rotatePosition({-dimensions.x/2.f,dimensions.y/2.f},rotation),
        center + rotatePosition({dimensions.x/2.f,dimensions.y/2.f},rotation),
        center + rotatePosition({dimensions.x/2.f,-dimensions.y/2.f},rotation),
        center + rotatePosition({-dimensions.x/2.f,-dimensions.y/2.f},rotation)
    };
}

CollisionRect::Projection CollisionRect::getProjection( const PolygonPoints &rect, sf::Vector2f projectionVector )
{
    std::vector<float> dots;
    for ( std::size_t index = 0; index < rect.size(); index++ )
    {
        dots.push_back(vectorDot( rect[index], projectionVector ));
    }

    return {*std::min_element(dots.begin(),dots.end()), *std::max_element(dots.begin(),dots.end())};
}

bool CollisionRect::overlappingOnVector( const PolygonPoints &rect1, const PolygonPoints &rect2, sf::Vector2f projectionVector )
{
    Projection projection1 = getProjection(rect1, projectionVector);
    Projection projection2 = getProjection(rect2, projectionVector);

    return projection1.contains(projection2) || projection2.contains(projection1);
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