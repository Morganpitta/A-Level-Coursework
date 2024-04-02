#if !defined( MW_MAIN_LOOP_HPP )
#define MW_MAIN_LOOP_HPP
    #include "mazeWars.h++"
    #include "Entity/entity.h++"
    #include "random.h++"

    namespace MazeWars
    {
        extern const float targetWidth;
        extern const float targetHeight;

        void handleResize( 
            sf::RenderWindow &window,
            float windowWidth, 
            float windowHeight
        );

        void handleInputs( sf::RenderWindow &window, MazeWarsGame &game );

        void mainLoop( sf::RenderWindow &window );
        void deathScreenLoop( sf::RenderWindow &window );
    }
#endif /* MW_MAIN_LOOP_HPP */