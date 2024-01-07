#include "Entity/bullet.h++"
#include "mazeWars.h++"

Bullet::Bullet( Id ownerId, sf::Vector2i position, Direction direction ): Entity( position )
{
    this->ownerId = ownerId;
    this->type = BulletType;
    this->texture = &TriangleTexture;
    this->movementCoolDown = 0;
    this->ownerId = NullId;
    this->direction = direction;
}

void Bullet::update( MazeWars &game )
{
    if ( movementCoolDown > 0 )
    {
        movementCoolDown--;
        return;
    }

    if ( game.getMaze().getCell( getPosition(), getDirection() ) ) 
        kill();
    else
    {
        sf::Vector2i nextPosition = transposePosition( getPosition(), getDirection() );
        if ( game.getMaze().inBounds( nextPosition ) )
        { 
            std::vector<Id> hitEntities = game.getEntitiesAtLocation( nextPosition );
            bool hitEntity = false;
            for ( Id entityId: hitEntities )
            {
                if ( entityId == ownerId )
                    continue;
                Entity* entity = game.getEntity( entityId );

                entity->damage( 1 );
                hitEntity = true;
            }

            if ( hitEntity )
                kill();
            else
                setPosition( nextPosition );
        }
    }
}