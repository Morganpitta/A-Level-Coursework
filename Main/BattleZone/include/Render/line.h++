#if !defined( BZ_LINE_HPP )
#define BZ_LINE_HPP
    
    #include <SFML/System.hpp>

    namespace BattleZone
    {
        struct LineVertex
        {
            sf::Vector3f position = { 0, 0, 0 };
        };

        class Line
        {
            LineVertex vertices[2];
            public:
                LineVertex getVertex( int index ) const;
                sf::Vector3f getVertexPosition( int index ) const;

                void setVertex( int index, LineVertex vertex );
                void setVertexPosition( int index, sf::Vector3f position );
        };
    }

#endif /* BZ_LINE_HPP */