#include "Render/model3D.h++"
#include "file.h++"
#include "assert.h++"

namespace BattleZone
{
    sf::Vector3f Model3D::Transformations::apply( sf::Vector3f position ) const
    {
        return 
            rotatePosition( 
                position - this->rotationOrigin,
                this->yaw,
                this->pitch,
                this->roll
            ) + this->rotationOrigin + this->position;
    };

    Model3D::Model3D() {}

    Model3D::Model3D( std::string path )
    {
        importFromFile( path );
    }

    const Triangle& Model3D::getTriangle( std::size_t index ) const { return this->triangles[index]; }

    void Model3D::setTriangle( std::size_t index, Triangle triangle ) { this->triangles[index] = triangle; }

    const Line& Model3D::getLine( std::size_t index ) const { return this->lines[index]; }

    void Model3D::setTriangle( std::size_t index, Line line ) { this->lines[index] = line; }

    std::size_t Model3D::getTriangleCount() const { return this->triangles.size(); }

    std::size_t Model3D::getLineCount() const { return this->lines.size(); }

    void Model3D::importFromFile( std::string path )
    {
        std::vector<sf::Vector3f> vertices;
        std::vector<sf::Vector3f> verticesNormal;
        std::vector<std::vector<std::size_t>> faces;
        std::vector<std::vector<std::size_t>> lines;
        this->triangles.clear();
        this->lines.clear();

        setWorkingDirectoryToDefault();
        // Open the file in input mode
        std::ifstream file( path );
        assert( file.is_open(), "Error opening file: " + getWorkingDirectory() +"/" + path );

        int lineError = parseFile( file, vertices, verticesNormal, faces, lines );
        assert( lineError == -1, "Error reading file: "+path+", line: "+std::to_string( lineError ) );

        file.close();

        assert( processData( vertices, verticesNormal, faces, lines ), "Error processing file: "+path );
    }

    int Model3D::parseFile( std::ifstream& file,
                    std::vector<sf::Vector3f>& vertices,
                    std::vector<sf::Vector3f>& verticesNormal,
                    std::vector<std::vector<std::size_t>>& faces,
                    std::vector<std::vector<std::size_t>>& lines )
    {
        int index = 0;
        std::string line;
        // Keep getting the next line until it returns false (Meaning there is no next line)
        while ( getline( file, line ) )
        {
            // Keep track of which line index we are on.
            index++;
            // If the parseLine function returns a false, indicating a failure, end the loop.
            if ( !parseLine( line, vertices, verticesNormal, faces, lines ) )
            {
                return index;
            }
        }

        // Return -1 indicating no error.
        return -1;
    }

    bool Model3D::parseVectorString( std::istringstream &stream, sf::Vector3f &vector )
    {
        std::string value;
        // Retrieve the next value using the >> stream operator
        // If the >> operator returns false it means that an invalid value was found
        if ( !(stream >> value) ) { return false; } vector.x = std::stof( value );
        if ( !(stream >> value) ) { return false; } vector.y = std::stof( value );
        if ( !(stream >> value) ) { return false; } vector.z = std::stof( value );

        // Everything was successful!
        return true;
    }

    bool Model3D::parseLine( std::string line,
                    std::vector<sf::Vector3f>& vertices,
                    std::vector<sf::Vector3f>& verticesNormal,
                    std::vector<std::vector<std::size_t>>& faces,
                    std::vector<std::vector<std::size_t>>& lines )
    {
        std::istringstream stream( line );
        std::string identifier; stream >> identifier;

        if ( identifier == "v" )
        {
            sf::Vector3f position;
            if ( !parseVectorString( stream, position ) ) return false;

            vertices.push_back( position );
        }
        else if ( identifier == "vn" )
        {
            sf::Vector3f normal;
            if ( !parseVectorString( stream, normal ) ) return false;

            verticesNormal.push_back( normal );
        }
        else if ( identifier == "f" )
        {
            faces.push_back( {} );
            while ( stream >> identifier )
            {
                // For now just retrieve the first value, the vertex value.
                // If I implement the Star Wars Arcade Game, i can add further code to fetch the normal data.
                std::size_t end = identifier.find( '/' );
                if ( end == std::string::npos ) end = identifier.size();
                std::string number = identifier.substr(0, end);
                if ( number == "" ) return false;
                faces.back().push_back( std::stoi( number ) );
            }
            if ( faces.back().size() < 3 )
                return false;
        }
        else if ( identifier == "l" )
        {
            lines.push_back( {} );
            while ( stream >> identifier )
            {
                lines.back().push_back( std::stoi( identifier ) );
            }
            if ( lines.back().size() < 2 )
                return false;
        }

        // Everything was successful!
        return true;
    }

    bool Model3D::processData( std::vector<sf::Vector3f>& vertices,
                        std::vector<sf::Vector3f>& verticesNormal,
                        std::vector<std::vector<std::size_t>>& faces,
                        std::vector<std::vector<std::size_t>>& lines )
    {
        // Iterate through each face
        for ( std::size_t faceIndex = 0; faceIndex < faces.size(); faceIndex++ )
        {
            // Fan triangulation
            for ( std::size_t vertexIndex = 1; vertexIndex < faces[faceIndex].size() - 1; vertexIndex++ )
            {
                this->triangles.push_back( Triangle() );
                this->triangles.back().setVertexPosition( 0, vertices[ faces[faceIndex][0] - 1 ] );
                this->triangles.back().setVertexPosition( 1, vertices[ faces[faceIndex][vertexIndex] - 1 ] );
                this->triangles.back().setVertexPosition( 2, vertices[ faces[faceIndex][vertexIndex + 1] - 1 ] );
            }
        }

        // Iterate through each line
        for ( std::size_t lineIndex = 0; lineIndex < lines.size(); lineIndex++ )
        {
            for ( std::size_t vertexIndex = 0; vertexIndex < lines[lineIndex].size() - 1; vertexIndex++ )
            {
                this->lines.push_back( Line() );
                this->lines.back().setVertexPosition( 0, vertices[ lines[lineIndex][vertexIndex] - 1 ] );
                this->lines.back().setVertexPosition( 1, vertices[ lines[lineIndex][vertexIndex+1] - 1 ] );
            }
        }

        return true;
    }
}