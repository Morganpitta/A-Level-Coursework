#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "Render/camera.h++"
    #include "Render/model3D.h++"
    #include "draw.h++"
    #include <SFML/Graphics.hpp>

    extern sf::Texture mountains;

    extern bool loadAssets();

    class Renderer
    {
        const float zNear;
        sf::VertexArray lineVertices;
        Camera camera;

        public:
            Renderer();

            Camera& getCamera();

            float getZNear() const;

            sf::Vector3f clipLineToNearPlane( const sf::Vector3f& lineStart, const sf::Vector3f& lineEnd  );

            bool projectLine( 
                sf::RenderWindow& window,
                sf::Vector3f& lineStart,
                sf::Vector3f& lineEnd
            );

            void drawTriangle( sf::RenderWindow& window, const Triangle& triangle, const Model3D::Transformations& transformations = {} );

            void drawLine( sf::RenderWindow& window, const Line& line, const Model3D::Transformations& transformations = {} );

            void draw( sf::RenderWindow& window, Model3D &model, Model3D::Transformations transformations = { 0, {0,0,0} } );

            void drawSkybox( sf::RenderWindow& window );

            void clear();

            void display( sf::RenderWindow& window );
    };

#endif /* RENDERER_HPP */