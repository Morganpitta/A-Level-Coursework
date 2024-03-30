#if !defined( MW_ENTITY_HPP )
#define MW_ENTITY_HPP

    #include "direction.h++"
    #include "SFML/Graphics.hpp"
    #include "file.h++"
    #include "Entity/entityBase.h++"

    namespace MazeWars
    {
        class Entity
        {
            protected:
                sf::Vector2i position;
                Direction direction;
                int health;
                Id id;
                bool dead;
                EntityType type;
                sf::Texture *texture;
                float size;
            
            public:
                Entity( sf::Vector2i position = {0,0} );

                sf::Vector2i getPosition() const;
                Direction getDirection() const;
                int getHealth() const;
                Id getId() const;
                bool isDead() const;
                EntityType getType() const;
                sf::Texture *getTexture() const;
                float getSize() const;

                void setPosition( sf::Vector2i position );
                void setDirection( Direction direction );
                void setHealth( int health );
                void setId( Id id );

                void moveForward();
                void moveBackward();
                void turnLeft();
                void turnRight();
                void damage( int amount );
                void kill();

                sf::Vector2i relativePositionOf( sf::Vector2i position );

                virtual void update( MazeWarsGame &game );
        };
    }

#endif /* MW_ENTITY_HPP */