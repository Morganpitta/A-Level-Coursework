#if !defined( BZ_TRIANGLE_HPP )
#define BZ_TRIANGLE_HPP
    
    #include <SFML/System.hpp>

    namespace BattleZone
    {
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
    }

#endif /* BZ_TRIANGLE_HPP */