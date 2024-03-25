#include "Render/renderer.h++"
#include "Entity/entity.h++"
#include "draw.h++"

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

Renderer::Renderer( sf::Vector2u displaySize ): displaySize(displaySize), 
                                                zNear( 0.01f ), 
                                                mountainHeight( 150 ),
                                                lineVertices( sf::PrimitiveType::Lines ), 
                                                camera()
{
}

Camera& Renderer::getCamera() { return camera; }

float Renderer::getZNear() const { return this->zNear; }
            
sf::Vector2u Renderer::getDisplaySize() const { return this->displaySize; }

sf::Vector3f Renderer::clipLineToNearPlane( const sf::Vector3f& lineStart, const sf::Vector3f& lineEnd  )
{
    float delta = ( lineStart.z - getZNear() ) / ( lineStart.z - lineEnd.z );
    
    return { lineStart.x + ( lineEnd.x - lineStart.x) * delta, lineStart.y + ( lineEnd.y - lineStart.y) * delta, getZNear() };
}

bool Renderer::projectLine( 
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

    lineStart.x = lineStart.x * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.x / 2.f;
    lineEnd.x = lineEnd.x * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.x / 2.f;

    //Y axis is inverted
    lineStart.y = -lineStart.y * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.y / 2.f;
    lineEnd.y = -lineEnd.y * ( displaySize.x / 2 ) / tan( camera.getFov() / 2 ) + displaySize.y / 2.f;

    return true;
}

void Renderer::drawTriangle(
    const Triangle& triangle, 
    const Model3D::Transformations& transformations 
)
{
    sf::Vector3f lineStart, lineEnd;
    for ( int index = 0; index < 3; index++ )
    {
        lineStart = transformations.apply( triangle.getVertexPosition( index ) );
        lineEnd = transformations.apply( triangle.getVertexPosition( index + 1 ) );
        if ( projectLine( lineStart, lineEnd ) )
        {
            appendLineToArray( lineVertices, { lineStart.x, lineStart.y }, { lineEnd.x, lineEnd.y }, sf::Color::Green );
        }
    }
}

void Renderer::drawLine(
    const Line& line, 
    const Model3D::Transformations& transformations 
)
{
    sf::Vector3f lineStart = transformations.apply( line.getVertexPosition( 0 ) );
    sf::Vector3f lineEnd = transformations.apply( line.getVertexPosition( 1 ) );
    if ( projectLine( lineStart, lineEnd ) )
    {
        appendLineToArray( lineVertices, { lineStart.x, lineStart.y }, { lineEnd.x, lineEnd.y }, sf::Color::Green );
    }
}

void Renderer::draw(
    Model3D *model, 
    Model3D::Transformations transformations 
)
{
    for ( std::size_t index = 0; index < model->getTriangleCount(); index++ )
    {
        drawTriangle( model->getTriangle(index), transformations );
    }

    for ( std::size_t index = 0; index < model->getLineCount(); index++ )
    {
        drawLine( model->getLine(index), transformations );
    }
}

void Renderer::drawEntity( Entity *entity )
{
    if ( !entity->isDead() )
    {
        sf::Vector3f position = { entity->getPosition().x, 0, entity->getPosition().y };
        draw( entity->getModel(), { entity->getRotation(), 0, 0, position } );
    }
}

void Renderer::drawBackground( sf::RenderWindow& window )
{
    int textureWidth = std::floor( mountains.getSize().x * 3 * ( camera.getFov() / ( 2*M_PI ) ) );
    int textureOffset = std::floor(
        mountains.getSize().x * 3 * ( normaliseAngle( camera.getYaw() ) / ( 2*M_PI ) ) - textureWidth/2.f 
    );

    sf::RectangleShape background( {(float)displaySize.x, (float)this->mountainHeight} );
    // Center on screen
    background.setPosition({0,displaySize.y/2.f-this->mountainHeight});
    background.setTexture( &mountains );

    // This function sets which part of the mountains to display
    background.setTextureRect( sf::IntRect({textureOffset,0},{textureWidth, (int) mountains.getSize().y}) );

    window.draw( background );
}

void Renderer::clear()
{
    lineVertices.clear();
}

void Renderer::display( sf::RenderWindow& window )
{
    window.draw( lineVertices );
}