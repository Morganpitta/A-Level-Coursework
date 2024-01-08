#if !defined( LINE_HPP )
#define LINE_HPP
    
    #include <SFML/System.hpp>

    struct LineVertex
    {
        sf::Vector3f position = { 0, 0, 0 };
    };

    class Line
    {
        LineVertex vertices[2];
        public:
            LineVertex getVertex( int index ) const;

            void setVertex( int index, LineVertex vertex );
            
            sf::Vector3f getVertexPosition( int index ) const;

            void setVertexPosition( int index, sf::Vector3f position );
    };

#endif /* LINE_HPP */