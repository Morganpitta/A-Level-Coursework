#include "render/model3D.h++"

Model3D::Model3D()
{

}

Model3D::Model3D( std::string path )
{
    importFromFile( path );
}

const Triangle& Model3D::getTriangle( int index ) const
{
    return this->triangles[index];
}

void Model3D::setTriangle( int index, Triangle triangle )
{
    this->triangles[index] = triangle;
}

const Line& Model3D::getLine( int index ) const
{
    return this->lines[index];
}

void Model3D::setTriangle( int index, Line line )
{
    this->lines[index] = line;
}

std::size_t Model3D::getTriangleCount() const
{
    return this->triangles.size();
}

std::size_t Model3D::getLineCount() const
{
    return this->lines.size();
}

void Model3D::importFromFile( std::string path )
{
    std::vector<sf::Vector3f> vertices;
    std::vector<sf::Vector3f> verticesNormal;
    std::vector<std::vector<int>> faces;
    std::vector<std::vector<int>> lines;
    this->triangles.clear();
    this->lines.clear();
    setWorkingDirectoryToDefault();
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
                std::vector<std::vector<int>>& faces,
                std::vector<std::vector<int>>& lines )
{
    int index = 0;
    std::string line;
    while ( getline ( file, line ) )
    {
        index++;
        if ( !parseLine( line, vertices, verticesNormal, faces, lines ) )
        {
            return index;
        }
    }

    return -1;
}

bool Model3D::parseLine( std::string line,
                std::vector<sf::Vector3f>& vertices,
                std::vector<sf::Vector3f>& verticesNormal,
                std::vector<std::vector<int>>& faces,
                std::vector<std::vector<int>>& lines )
{
    std::istringstream words( line );
    std::string word;
    words >> word;

    if ( word == "v" )
    {
        sf::Vector3f position;
        if ( !(words >> word) ) return false; position.x = std::stof( word );
        if ( !(words >> word) ) return false; position.y = std::stof( word );
        if ( !(words >> word) ) return false; position.z = std::stof( word );

        vertices.push_back( position );
    }
    else if ( word == "vn" )
    {
        //To be done
    }
    else if ( word == "f" )
    {
        faces.push_back( {} );
        while ( words >> word )
        {
            int end = word.find( '/' );
            if ( end == -1 ) end = word.size();
            std::string number = word.substr(0, end);
            if ( number == "" ) return false;
            faces.back().push_back( std::stoi( number ) );
        }
        if ( faces.back().size() < 3 )
            return false;
    }
    else if ( word == "l" )
    {
        lines.push_back( {} );
        while ( words >> word )
        {
            lines.back().push_back( std::stoi( word ) );
        }
        if ( lines.back().size() < 2 )
            return false;
    }

    return true;
}

bool Model3D::processData( std::vector<sf::Vector3f>& vertices,
                    std::vector<sf::Vector3f>& verticesNormal,
                    std::vector<std::vector<int>>& faces,
                    std::vector<std::vector<int>>& lines )
{
    for ( int faceIndex = 0; faceIndex < faces.size(); faceIndex++ )
    {
        for ( int vertexIndex = 1; vertexIndex < faces[faceIndex].size() - 1; vertexIndex++ )
        {
            this->triangles.push_back( Triangle() );
            this->triangles.back().setVertexPosition( 0, vertices[ faces[faceIndex][0] - 1 ] );
            this->triangles.back().setVertexPosition( 1, vertices[ faces[faceIndex][vertexIndex] - 1 ] );
            this->triangles.back().setVertexPosition( 2, vertices[ faces[faceIndex][vertexIndex + 1] - 1 ] );
        }
    }

    for ( int lineIndex = 0; lineIndex < lines.size(); lineIndex++ )
    {
        for ( int vertexIndex = 0; vertexIndex < lines[lineIndex].size() - 1; vertexIndex++ )
        {
            this->lines.push_back( Line() );
            this->lines.back().setVertexPosition( 0, vertices[ lines[lineIndex][vertexIndex] - 1 ] );
            this->lines.back().setVertexPosition( 1, vertices[ lines[lineIndex][vertexIndex+1] - 1 ] );
        }
    }

    return true;
}