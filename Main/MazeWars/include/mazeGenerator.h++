#if !defined( MAZE_GENERATOR_HPP )
#define MAZE_GENERATOR_HPP

    #include "mazeGrid.h++"
    #include "time.h++"
    #include <array>

    extern void randomlyRemoveWall( 
        sf::Vector2i position,
        MazeGrid &mazeGrid,
        float randomness
    );

    extern Direction getRandomValidDirection( 
        sf::Vector2i position, 
        MazeGrid &mazeGrid, 
        const std::vector<std::vector<bool>> &isSearched 
    );

    extern void generateMazeDepthFirst( 
        MazeGrid &mazeGrid, 
        float randomness, 
        std::size_t seed = time(NULL)
    );
#endif /* MAZE_GENERATOR_HPP */