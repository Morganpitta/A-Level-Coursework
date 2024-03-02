#if !defined( RENDERER_HPP )
#define RENDERER_HPP

    #include "Entity/entityBase.h++"
    #include "camera.h++"
    #include "mazeGrid.h++"
    #include "draw.h++"
    #include <queue>
    #include <map>

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
            sf::RenderWindow &window,
            float startIndex,
            float endIndex
        ) const;

        void setHasBeenDrawnOn(
            int xIndex,
            bool value
        );

        public:
            Renderer( sf::Vector2u displaySize );

            Camera &getCamera();

            float getYNear() const;
            
            sf::Vector2u getDisplaySize() const;

            bool onScreen( 
                sf::RenderWindow& window, 
                float xValue 
            ) const;

            sf::Vector2f clipWallSegmentToNearPlane( 
                sf::Vector2f wallStart,
                sf::Vector2f wallEnd 
            );

            bool projectWall(
                sf::RenderWindow& window,
                sf::Vector2f &wallStart,
                sf::Vector2f &wallEnd
            );

            bool projectPoint(
                sf::RenderWindow& window,
                sf::Vector2f &position,
                float &size
            );

            void drawWallVertical(
                sf::RenderWindow& window,
                sf::Vector2f position
            );

            void drawWallHorizontals(
                sf::RenderWindow& window,
                sf::Vector2f &wallStart,
                sf::Vector2f &wallEnd
            );

            void drawWall(
                sf::RenderWindow& window,
                sf::Vector2f &wallStart,
                sf::Vector2f &wallEnd
            );

            void drawEntity(
                sf::RenderWindow &window,
                Entity *entity
            );

            void render(
                sf::RenderWindow& window,
                MazeGrid &mazeGrid,
                const std::vector<std::vector<std::vector<Entity*>>> &entityGrid,
                Id playerId
            );
    };

#endif /* RENDERER_HPP */