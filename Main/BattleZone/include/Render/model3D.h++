#if !defined( MODEL_3D_HPP )
#define MODEL_3D_HPP

    #include <fstream>
    #include <vector>
    #include <string>
    #include "assert.h++"
    #include "file.h++"
    #include "Render/triangle.h++"
    #include "Render/line.h++"
    #include "vector.h++"

    class Model3D
    {
        std::vector<Triangle> triangles;
        std::vector<Line> lines;
        public:
            struct Transformations 
            {
                float yaw = 0;
                float pitch = 0;
                float roll = 0;
                sf::Vector3f position = {0,0,0};
                sf::Vector3f rotationOrigin = {0,0,0};

                public:
                    sf::Vector3f apply( sf::Vector3f position ) const;
            };
            
            Model3D();
            
            Model3D( std::string path );

            const Triangle& getTriangle( int index ) const;

            void setTriangle( int index, Triangle triangle );

            const Line& getLine( int index ) const;

            void setTriangle( int index, Line line );

            std::size_t getTriangleCount() const; 

            std::size_t getLineCount() const;

            void importFromFile( std::string path );

            int parseFile( std::ifstream& file,
                            std::vector<sf::Vector3f>& vertices,
                            std::vector<sf::Vector3f>& verticesNormal,
                            std::vector<std::vector<int>>& faces,
                            std::vector<std::vector<int>>& lines );

            bool parseLine( std::string line,
                            std::vector<sf::Vector3f>& vertices,
                            std::vector<sf::Vector3f>& verticesNormal,
                            std::vector<std::vector<int>>& faces,
                            std::vector<std::vector<int>>& lines );

            bool processData( std::vector<sf::Vector3f>& vertices,
                              std::vector<sf::Vector3f>& verticesNormal,
                              std::vector<std::vector<int>>& faces,
                              std::vector<std::vector<int>>& lines );
    };

#endif /* MODEL_3D_HPP */