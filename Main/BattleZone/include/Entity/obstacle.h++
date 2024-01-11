#if !defined( OBSTACLE_HPP )
#define OBSTACLE_HPP

    #include "Entity/entity.h++"

    class Obstacle: public Entity
    {
        public:
            Obstacle( sf::Vector2f position = {0,0} );
    };

#endif /* OBSTACLE_HPP */