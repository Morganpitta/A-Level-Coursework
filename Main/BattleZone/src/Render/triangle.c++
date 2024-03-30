#include "Render/triangle.h++"
namespace BattleZone
{
    TriangleVertex Triangle::getVertex( int index ) const { return this->vertices[index % 3]; }

    void Triangle::setVertex( int index, TriangleVertex vertex ) { this->vertices[index % 3] = vertex; }

    sf::Vector3f Triangle::getVertexPosition( int index ) const { return getVertex( index ).position; }

    void Triangle::setVertexPosition( int index, sf::Vector3f position ) { this->vertices[index % 3].position = position; }

    sf::Vector3f Triangle::getVertexNormal( int index ) const { return getVertex( index ).normal; }

    void Triangle::setVertexNormal( int index, sf::Vector3f normal ) { this->vertices[index % 3].normal = normal; }
}