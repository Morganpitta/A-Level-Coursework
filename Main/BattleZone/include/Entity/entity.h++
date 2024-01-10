#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    class BattleZone;
    #include "entityBase.h++"

    class Entity
    {
        protected:
            Model3D *model;
            sf::Vector2f position;
            float rotation;
            int health;
            Id id;
            bool dead;
            EntityType type;

        public:
            Entity( sf::Vector2f position = {0,0} );

            sf::Vector2f getPosition() const;

            float getRotation() const;

            int getHealth() const;

            Id getId() const;

            bool isDead() const;

            EntityType getType() const;

            Model3D *getModel();

            float getSize() const;

            void setPosition( sf::Vector2f position );

            void setRotation( float rotation );

            void moveForward( float distance );

            void turnLeft( float angle );

            void turnRight( float angle );

            sf::Vector2f relativePositionOf( sf::Vector2f position );
            
            void setHealth( int health );

            void damage( int amount );

            void setId( Id id );

            void kill();

            virtual void update( BattleZone &game );
    };

#endif /* ENTITY_HPP */