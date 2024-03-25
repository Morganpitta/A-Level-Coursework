#if !defined( TRIANGLE_HPP )
#define TRIANGLE_HPP
    
    #include <SFML/System.hpp>

    struct TriangleVertex
    {
        sf::Vector3f position = { 0, 0, 0 };
        sf::Vector3f normal = { 0, 0, 0 };
    };

    class Triangle
    {
        TriangleVertex vertices[3];
        public:
            TriangleVertex getVertex( int index ) const;
            sf::Vector3f getVertexPosition( int index ) const;
            sf::Vector3f getVertexNormal( int index ) const;

            void setVertex( int index, TriangleVertex vertex );
            void setVertexPosition( int index, sf::Vector3f position );
            void setVertexNormal( int index, sf::Vector3f normal );
    };

#endif /* TRIANGLE_HPP */