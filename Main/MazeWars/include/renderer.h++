#if !defined( MW_RENDERER_HPP )
#define MW_RENDERER_HPP

    #include "Entity/entityBase.h++"
    #include "camera.h++"
    #include "mazeGrid.h++"
    #include "draw.h++"
    #include <queue>
    #include <map>
    #include <algorithm>

    namespace MazeWars
    {
        class Renderer
        {
            const sf::Vector2u displaySize;
            const float yNear;
            const float wallHeight;
            Camera camera;
            sf::VertexArray wallVertices;
            std::vector<sf::RectangleShape> entityRectangles;
            std::vector<bool> drawnOn;

            bool hasBeenDrawnOn( int xIndex ) const;
            bool canDrawInRange(
                float startIndex,
                float endIndex
            ) const;
            void setHasBeenDrawnOn(
                int xIndex,
                bool value
            );
            void setHasBeenDrawnOn(
                int startIndex,
                int endIndex,
                bool value
            );

            public:
                Renderer( sf::Vector2u displaySize );

                Camera &getCamera();
                float getYNear() const;
                sf::Vector2u getDisplaySize() const;
                bool onScreen( float xValue ) const;

                sf::Vector2f clipLineToNearPlane( 
                    sf::Vector2f lineStart,
                    sf::Vector2f lineEnd 
                );
                bool projectPoint(
                    sf::Vector2f &position,
                    float &size
                );
                bool projectLine(
                    sf::Vector2f &lineStart,
                    sf::Vector2f &lineEnd
                );

                void drawWallVertical( sf::Vector2f position );
                void drawWallHorizontals(
                    sf::Vector2f &wallStart,
                    sf::Vector2f &wallEnd
                );
                void drawWall(
                    sf::Vector2f &wallStart,
                    sf::Vector2f &wallEnd
                );

                void drawEntity( Entity *entity );

                void render(
                    sf::RenderWindow& window,
                    MazeGrid &mazeGrid,
                    const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
                    Id playerId
                );
        };
    }

#endif /* MW_RENDERER_HPP */