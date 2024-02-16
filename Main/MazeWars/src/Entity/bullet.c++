#include "Entity/bullet.h++"
#include "mazeWars.h++"

Bullet::Bullet( Id ownerId, sf::Vector2i position, Direction direction ): Entity( position )
{
    this->ownerId = ownerId;
    this->type = BulletType;
    this->texture = &CircleTexture;
    this->size = 20;
    this->direction = direction;
    this->movementCooldown = 5;
}

Id Bullet::getOwnerId() const
{
    return this->ownerId;
}

void Bullet::update( MazeWars &game )
{
    if ( this->movementCooldown > 0 )
    {    
        this->movementCooldown--;
        return;
    }

    this->movementCooldown = 5;

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
                if ( entityId == getOwnerId() )
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