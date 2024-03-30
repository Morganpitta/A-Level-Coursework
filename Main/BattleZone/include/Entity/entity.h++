#if !defined( ENTITY_HPP )
#define ENTITY_HPP

    #include "entityBase.h++"
    #include "collisionRect.h++"
    #include <functional>

    namespace BattleZone
    {
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
                virtual CollisionRect getCollisionRect() const;

                void setPosition( sf::Vector2f position );
                void setRotation( float rotation );
                void setHealth( int health );
                void setId( Id id );

                void moveForward( float distance );
                void turnLeft( float angle );
                void turnRight( float angle );
                void damage( int amount );
                void kill();

                sf::Vector2f relativePositionOf( sf::Vector2f position );

                static std::vector<Entity*> getColliding( 
                    Entity *entity, 
                    sf::Vector2f offset, 
                    const std::map<Id,Entity*> &entities, 
                    std::function<bool(Entity*)> filter = []( Entity *entity){return true;}
                );

                virtual void update( BattleZoneGame &game );
        };
    }

#endif /* ENTITY_HPP */