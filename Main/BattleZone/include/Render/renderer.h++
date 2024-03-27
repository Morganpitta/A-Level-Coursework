#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "Render/camera.h++"
    #include "Render/model3D.h++"
    #include "Entity/entityBase.h++"
    #include <SFML/Graphics.hpp>

    extern sf::Texture mountains;
    extern sf::Texture crosshair;

    extern bool loadAssets();

    class Renderer
    {
        const sf::Vector2u displaySize;
        const float zNear;
        const float mountainHeight;
        sf::VertexArray lineVertices;
        Camera camera;

        public:
            Renderer( sf::Vector2u displaySize );

            Camera& getCamera();
            float getZNear() const;
            sf::Vector2u getDisplaySize() const;

            sf::Vector3f clipLineToNearPlane( 
                const sf::Vector3f& lineStart, 
                const sf::Vector3f& lineEnd 
            );

            bool projectLine( 
                sf::Vector3f& lineStart,
                sf::Vector3f& lineEnd
            );

            void drawTriangle( 
                const Triangle& triangle, 
                const Model3D::Transformations& transformations = {} 
            );

            void drawLine( 
                const Line& line, 
                const Model3D::Transformations& transformations = {} 
            );

            void draw( 
                Model3D *model, 
                Model3D::Transformations transformations = {} 
            );

            void drawEntity( Entity *entity );

            void drawBackground( sf::RenderWindow& window );

            void drawUI( sf::RenderWindow& window );

            void clear();

            void display( sf::RenderWindow& window );
    };

#endif /* RENDERER_HPP */