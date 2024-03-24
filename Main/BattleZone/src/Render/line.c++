#include <Render/line.h++>

LineVertex Line::getVertex( int index ) const { return this->vertices[index % 2]; }

void Line::setVertex( int index, LineVertex vertex ) { this->vertices[index % 2] = vertex; }

sf::Vector3f Line::getVertexPosition( int index ) const { return getVertex( index ).position; }

void Line::setVertexPosition( int index, sf::Vector3f position ) { this->vertices[index % 2].position = position; }