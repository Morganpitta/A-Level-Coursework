#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "render/camera.h++"
    #include "render/model3D.h++"
    #include <SFML/Graphics.hpp>

    sf::Texture mountains;

    bool loadAssets()
    {
        if ( !loadBaseAssets() )
            return false;
        
        if ( !mountains.loadFromFile( "mountains.png" ) )
            return false;
        
        mountains.setRepeated( true );

        return true;
    }

    class Renderer
    {
        const float zNear = 0.01f;
        sf::VertexArray lineVerticies;
        Camera camera;

        public:
            Renderer( sf::RenderWindow *window ): camera(), lineVerticies( sf::PrimitiveType::Lines )
            {
                
            }

            Camera& getCamera()
            {
                return camera;
            }

            sf::Vector3f clipLineToNearPlane( const sf::Vector3f& lineStart, const sf::Vector3f& lineEnd  )
            {
                float delta = ( lineStart.z - zNear ) / ( lineStart.z - lineEnd.z );
                
                return { lineStart.x + ( lineEnd.x - lineStart.x) * delta, lineStart.y + ( lineEnd.y - lineStart.y) * delta, zNear };
            }

            bool projectLine( sf::Vector3f& lineStart, sf::Vector3f& lineEnd )
            {
                //Getting relative position
                lineStart = getCamera().relativePosition( lineStart );
                lineEnd = getCamera().relativePosition( lineEnd );

                // Clip near
                if ( lineStart.z < zNear && lineEnd.z < zNear )
                    return false;
                else if ( lineStart.z < zNear )
                {
                    lineStart = clipLineToNearPlane( lineStart, lineEnd );
                }
                else if ( lineEnd.z < zNear )
                {
                    lineEnd = clipLineToNearPlane( lineStart, lineEnd );
                }

                lineStart.x /= lineStart.z;
                lineEnd.x /= lineEnd.z;
                lineStart.y /= lineStart.z;
                lineEnd.y /= lineEnd.z;

                lineStart.x = lineStart.x * ( window->getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window->getSize().x / 2.f;
                lineEnd.x = lineEnd.x * ( window->getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window->getSize().x / 2.f;

                //Y axis is inverted
                lineStart.y = -lineStart.y * ( window->getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window->getSize().y / 2.f;
                lineEnd.y = -lineEnd.y * ( window->getSize().x / 2 ) / tan( camera.getFov() / 2 ) + window->getSize().y / 2.f;

                // Test side - to be done

                return true;
            }

            void drawTriangle( const Triangle& triangle, const Model3D::Transformations& transformations = { 0, {0,0,0} } )
            {
                sf::Vector3f lineStart, lineEnd;
                for ( int index = 0; index < 3; index++ )
                {
                    lineStart = rotatePosition( triangle.getVertexPosition( index ) - transformations.rotationOrigin, transformations.rotation ) + transformations.rotationOrigin + transformations.position;
                    lineEnd = rotatePosition( triangle.getVertexPosition( index + 1 ) - transformations.rotationOrigin, transformations.rotation ) + transformations.rotationOrigin + transformations.position;
                    if ( projectLine( lineStart, lineEnd ) )
                    {
                        vertexArray.append( sf::Vertex( sf::Vector2f( std::floor(lineStart.x), std::floor(lineStart.y) ), sf::Color::Green ) );
                        vertexArray.append( sf::Vertex( sf::Vector2f( std::floor(lineEnd.x), std::floor(lineEnd.y) ), sf::Color::Green ) );
                    }
                }
            }

            void drawLine( const Line& line, const Model3D::Transformations& transformations = { 0, {0,0,0} } )
            {
                sf::Vector3f lineStart, lineEnd;
                for ( int index = 0; index < 3; index++ )
                {
                    lineStart = rotatePosition( line.getVertexPosition( index ) - transformations.rotationOrigin, transformations.rotation ) + transformations.rotationOrigin + transformations.position;
                    lineEnd = rotatePosition( line.getVertexPosition( index + 1 ) - transformations.rotationOrigin, transformations.rotation ) + transformations.rotationOrigin + transformations.position;
                    if ( projectLine( lineStart, lineEnd ) )
                    {
                        vertexArray.append( sf::Vertex( sf::Vector2f( std::floor(lineStart.x), std::floor(lineStart.y) ), sf::Color::Green ) );
                        vertexArray.append( sf::Vertex( sf::Vector2f( std::floor(lineEnd.x), std::floor(lineEnd.y) ), sf::Color::Green ) );
                    }
                }
            }

            void draw( Model3D &model, Model3D::Transformations transformations = { 0, {0,0,0} } )
            {
                for ( int index = 0; index < model.getTriangleCount(); index++ )
                {
                    drawTriangle( model.getTriangle(index), transformations );
                }

                for ( int index = 0; index < model.getLineCount(); index++ )
                {
                    drawLine( model.getLine(index), transformations );
                }
            }

            void drawSkybox()
            {
                float percentOffset = std::fmod( 2 * M_PI + camera.getRotation(), 2* M_PI ) / ( 2*M_PI );
                float percentWidth = camera.getFov() / ( 2*M_PI );

                sf::RectangleShape skyBox( {1600,150} );
                skyBox.setPosition({0,250});
                skyBox.setTexture( &mountains );
                skyBox.setTextureRect( sf::IntRect({(mountains.getSize().x*3) * ( percentOffset - percentWidth/2 ),0},{(mountains.getSize().x*3) * ( percentWidth ), mountains.getSize().y}) );

                window->draw( skyBox );
            }

            void clear()
            {
                vertexArray.clear();
            }

            void display()
            {
                window->draw( vertexArray );
            }
    };

#endif /* RENDERER_HPP */