#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    #include "direction.h++"
    #include "assert.h++"
    #include "SFML/Graphics.hpp"

    typedef int Id;
    const Id NullId = -1;

    enum EntityType
    {
        NoType
    };

    class Entity
    {
        sf::Vector2i position = {0,0};
        Direction direction = North;
        int health = 0;
        Id id = NullId;
        bool dead = false;
        EntityType type = NoType;
        
        public:
            Entity()
            {
            }

            sf::Vector2i getPosition()
            {
                return this->position;
            }

            Direction getDirection()
            {
                return this->direction;
            }

            int getHealth()
            {
                return this->health;
            }

            Id getId()
            {
                return this->id;
            }

            bool isDead()
            {
                return this->dead;
            }

            EntityType getType()
            {
                return this->type;
            }
    };
#endif /* ENTITY_HPP */