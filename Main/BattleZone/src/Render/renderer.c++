#include "Render/renderer.h++"

sf::Texture mountains;

bool loadAssets()
{
    if ( !loadBaseAssets() )
        return false;
    
    if ( !mountains.loadFromFile( "BattleZone/mountains.png" ) )
        return false;
    
    mountains.setRepeated( true );

    return true;
}

Renderer::Renderer(): zNear( 0.01f ), camera(), lineVertices( sf::PrimitiveType::Lines )
{
    
}

Camera& Renderer::getCamera()
{
    return camera;
}

float Renderer::getZNear() const
{
    return this->zNear;
}

sf::Vector3f Renderer::clipLineToNearPlane( const sf::Vector3f& lineStart, const sf::Vector3f& lineEnd  )
{
    float delta = ( lineStart.z - getZNear() ) / ( lineStart.z - lineEnd.z );
    
    return { lineStart.x + ( lineEnd.x - lineStart.x) * delta, lineStart.y + ( lineEnd.y - lineStart.y) * delta, getZNear() };
}

bool Renderer::projectLine( 
    sf::RenderWindow& window,
    sf::Vector3f& lineStart,
    sf::Vector3f& lineEnd
)
{
    //Getting relative position
    lineStart = getCamera().relativePositionOf( lineStart );
    lineEnd = getCamera().relativePositionOf( lineEnd );

    // Clip near
    if ( lineStart.z < getZNear() && lineEnd.z < getZNear() )
        return false;
    else if ( lineStart.z < getZNear() )
    {
        lineStart = clipLineToNearPlane( lineStart, lineEnd );
    }
    else if ( lineEnd.z < getZNear() )
    {
        lineEnd = clipLineToNearPlane( lineStart, lineEnd );
    }

    lineStart.x /= lineStart.z;
    lineEnd.x /= lineEnd.z;
    lineStart.y /= lineStart.z;
    lineEnd.y /= lineEnd.z;

    lineStart.x = lineStart.x * ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window.getSize().x / 2.f;
    lineEnd.x = lineEnd.x * ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window.getSize().x / 2.f;

    //Y axis is inverted
    lineStart.y = -lineStart.y * ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window.getSize().y / 2.f;
    lineEnd.y = -lineEnd.y * ( window.getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window.getSize().y / 2.f;

    // Test side - to be done

    return true;
}

void Renderer::drawTriangle(
    sf::RenderWindow& window, const Triangle& triangle, const Model3D::Transformations& transformations )
{
    sf::Vector3f lineStart, lineEnd;
    for ( int index = 0; index < 3; index++ )
    {
        lineStart = transformations.apply( triangle.getVertexPosition( index ) );
        lineEnd = transformations.apply( triangle.getVertexPosition( index + 1 ) );
        if ( projectLine( window,  lineStart, lineEnd ) )
        {
            appendLineToArray( lineVertices, { lineStart.x, lineStart.y }, { lineEnd.x, lineEnd.y }, sf::Color::Green );
        }
    }
}

void Renderer::drawLine(
    sf::RenderWindow& window, const Line& line, const Model3D::Transformations& transformations )
{
    sf::Vector3f lineStart = transformations.apply( line.getVertexPosition( 0 ) );
    sf::Vector3f lineEnd = transformations.apply( line.getVertexPosition( 1 ) );
    if ( projectLine( window, lineStart, lineEnd ) )
    {
        appendLineToArray( lineVertices, { lineStart.x, lineStart.y }, { lineEnd.x, lineEnd.y }, sf::Color::Green );
    }
}

void Renderer::draw(
    sf::RenderWindow& window, Model3D &model, Model3D::Transformations transformations )
{
    for ( int index = 0; index < model.getTriangleCount(); index++ )
    {
        drawTriangle( window, model.getTriangle(index), transformations );
    }

    for ( int index = 0; index < model.getLineCount(); index++ )
    {
        drawLine( window, model.getLine(index), transformations );
    }
}

void Renderer::drawSkybox( sf::RenderWindow& window )
{
    float percentOffset = std::fmod( 2 * M_PI + camera.getYaw(), 2* M_PI ) / ( 2*M_PI );
    float percentWidth = camera.getFov() / ( 2*M_PI );

    sf::RectangleShape skyBox( {1600,150} );
    skyBox.setPosition({0,250});
    skyBox.setTexture( &mountains );
    skyBox.setTextureRect( sf::IntRect({(mountains.getSize().x*3) * ( percentOffset - percentWidth/2 ),0},{(mountains.getSize().x*3) * ( percentWidth ), mountains.getSize().y}) );

    window.draw( skyBox );
}

void Renderer::clear()
{
    lineVertices.clear();
}

void Renderer::display( sf::RenderWindow& window )
{
    window.draw( lineVertices );
}