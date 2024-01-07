#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    class MazeWars;
    #include "direction.h++"
    #include "SFML/Graphics.hpp"
    #include "file.h++"
    #include "Entity/entityBase.h++"

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

            void moveForward();

            void moveBackward();

            void turnLeft();

            void turnRight();

            sf::Vector2i relativePositionOf( sf::Vector2i position );
            
            void setHealth( int health );

            void damage( int amount );

            void setId( Id id );

            void kill();

            virtual void update( MazeWars &game );
    };

#endif /* ENTITY_HPP */