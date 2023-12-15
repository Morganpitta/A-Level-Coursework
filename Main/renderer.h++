#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "camera.h++"
    #include "mazeGrid.h++"
    #include <queue>

    class Renderer
    {
        const float yNear = 0.1;
        const float wallHeight = 200;
        Camera camera;
        sf::VertexArray vertexArray;

        public:
            Renderer(): camera(), vertexArray( sf::PrimitiveType::Lines )
            {

            }

            Camera &getCamera()
            {
                return this->camera;
            }

            float getYNear()
            {
                return this->yNear;
            }

            bool onScreen( sf::RenderWindow& window, float xValue )
            {
                return 0 <= xValue && xValue < window.getSize().x;
            }

            sf::Vector2f clipWallSegmentToNearPlane( sf::Vector2f wallStart, sf::Vector2f wallEnd )
            {
                float delta = ( wallStart.y - getYNear() ) / ( wallStart.y - wallEnd.y );
                
                return { wallStart.x + ( wallEnd.x - wallStart.x ) * delta, getYNear() };
            }

            bool projectWall( sf::RenderWindow& window, sf::Vector2f &wallStart, sf::Vector2f &wallEnd )
            {
                //Getting relative position
                wallStart = getCamera().relativePositionOf( wallStart );
                wallEnd = getCamera().relativePositionOf( wallEnd );

                // Clip near
                if ( wallStart.y < getYNear() && wallEnd.y < getYNear() )
                    return false;
                else if ( wallStart.y < getYNear() )
                {
                    wallStart = clipWallSegmentToNearPlane( wallStart, wallEnd );
                }
                else if ( wallEnd.y < getYNear() )
                {
                    wallEnd = clipWallSegmentToNearPlane( wallStart, wallEnd );
                }

                wallStart.x /= wallStart.y;
                wallEnd.x /= wallEnd.y;

                // Making sure it's start to end not end to start
                if ( wallStart.x > wallEnd.x )
                {
                    std::swap( wallStart, wallEnd );
                }

                wallStart.x *= ( window.getSize().x / 2 ) * camera.getFov();
                wallEnd.x *= ( window.getSize().x / 2 ) * camera.getFov();

                wallStart.x += window.getSize().x / 2.f;
                wallEnd.x += window.getSize().x / 2.f;

                // Test if offscreen
                if ( wallEnd.x < 0  || wallStart.x > window.getSize().x )
                    return false;

                return true;
            }

            void drawWallEdge( sf::RenderWindow& window, sf::Vector2f edge )
            {
                float wallHeight = std::floor( this->wallHeight / edge.y );
                
                vertexArray.append( 
                    sf::Vertex( 
                        sf::Vector2f( 
                            std::floor(edge.x), 
                            ( window.getSize().y + wallHeight ) / 2 
                        ), 
                        sf::Color::Green 
                    ) 
                );
                vertexArray.append( 
                    sf::Vertex( 
                        sf::Vector2f( 
                            std::floor(edge.x), 
                            ( window.getSize().y - wallHeight ) / 2 
                        ), 
                        sf::Color::Green 
                    ) 
                );
            }

            void drawWallTop( sf::RenderWindow& window, sf::Vector2f &wallStart, sf::Vector2f &wallEnd )
            {
                float wallStartHeight = std::floor( this->wallHeight / wallStart.y );
                float wallEndHeight = std::floor( this->wallHeight / wallEnd.y );

                vertexArray.append( 
                    sf::Vertex( 
                        sf::Vector2f( 
                            wallStart.x,
                            ( window.getSize().y + wallStartHeight ) / 2
                        ), 
                        sf::Color::Green 
                    ) 
                );
                vertexArray.append( 
                    sf::Vertex( 
                        sf::Vector2f( 
                            wallEnd.x, 
                            ( window.getSize().y + wallEndHeight ) / 2
                        ), 
                        sf::Color::Green 
                    ) 
                );

                vertexArray.append( 
                    sf::Vertex( 
                        sf::Vector2f( 
                            wallStart.x, 
                            ( window.getSize().y - wallStartHeight ) / 2
                        ), 
                        sf::Color::Green
                    ) 
                );
                vertexArray.append(
                    sf::Vertex( 
                        sf::Vector2f( 
                            wallEnd.x, 
                            ( window.getSize().y - wallEndHeight ) / 2
                        ), 
                        sf::Color::Green 
                    )
                );
            }

            void drawWall( 
                sf::RenderWindow& window, 
                sf::Vector2f &wallStart, 
                sf::Vector2f &wallEnd 
            )
            {
                drawWallEdge( window, wallStart );

                drawWallEdge( window, wallEnd );

                // If its one or two pixel thin we can stop
                if ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) <= 1 )
                    return;

                drawWallTop( window, wallStart, wallEnd );
            }

            void render( sf::RenderWindow& window, MazeGrid &mazeGrid )
            {
                vertexArray.clear();

                for ( int xIndex = 0; xIndex < mazeGrid.getDimensions().x; xIndex++ )
                {
                    for ( int yIndex = 0; yIndex < mazeGrid.getDimensions().y; yIndex++ )
                    {
                        for ( int direction = North; direction < NumberOfDirections; direction++ )
                        {
                            sf::Vector2f wallStart = sf::Vector2f(xIndex + 0.5, yIndex + 0.5 ) + 
                                                     rotatePosition({-0.5, 0.5}, (Direction) direction);
                            sf::Vector2f wallEnd = sf::Vector2f(xIndex + 0.5, yIndex + 0.5 ) + 
                                                     rotatePosition({0.5, 0.5}, (Direction) direction);

                            drawWall( window, wallStart, wallEnd );
                        }
                    }
                }

                window.draw( vertexArray );
            }
    };

#endif /* RENDERER_HPP */