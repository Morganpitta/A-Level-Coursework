#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    class Entity
    {
        sf::Vector2i position;
        Direction direction;
        int health;
        int id;
        
        public:

    };

#endif /* ENTITY_HPP */