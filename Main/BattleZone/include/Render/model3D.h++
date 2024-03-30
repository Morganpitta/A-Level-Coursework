#if !defined( BZ_MODEL_3D_HPP )
#define BZ_MODEL_3D_HPP

    #include <fstream>
    #include <vector>
    #include <string>
    #include "Render/triangle.h++"
    #include "Render/line.h++"
    #include "vector.h++"

    namespace BattleZone
    {
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
                        Transformations( 
                            float yaw = 0, 
                            float pitch = 0, 
                            float roll = 0, 
                            sf::Vector3f position = {0,0,0},
                            sf::Vector3f rotationOrigin = {0,0,0}
                        ): yaw(yaw), pitch(pitch), roll(roll), position(position), rotationOrigin(rotationOrigin)
                        {
                        }

                        sf::Vector3f apply( sf::Vector3f position ) const;
                };
                
                Model3D();
                Model3D( std::string path );

                const Triangle& getTriangle( std::size_t index ) const;
                const Line& getLine( std::size_t index ) const;

                std::size_t getTriangleCount() const; 
                std::size_t getLineCount() const;

                void setTriangle( std::size_t index, Triangle triangle );
                void setTriangle( std::size_t index, Line line );

                void importFromFile( std::string path );

                int parseFile( std::ifstream& file,
                                std::vector<sf::Vector3f>& vertices,
                                std::vector<sf::Vector3f>& verticesNormal,
                                std::vector<std::vector<std::size_t>>& faces,
                                std::vector<std::vector<std::size_t>>& lines );

                static bool parseVectorString( std::istringstream &stream, sf::Vector3f &vector );

                bool parseLine( std::string line,
                                std::vector<sf::Vector3f>& vertices,
                                std::vector<sf::Vector3f>& verticesNormal,
                                std::vector<std::vector<std::size_t>>& faces,
                                std::vector<std::vector<std::size_t>>& lines );

                bool processData( std::vector<sf::Vector3f>& vertices,
                                std::vector<sf::Vector3f>& verticesNormal,
                                std::vector<std::vector<std::size_t>>& faces,
                                std::vector<std::vector<std::size_t>>& lines );
        };
    }

#endif /* BZ_MODEL_3D_HPP */