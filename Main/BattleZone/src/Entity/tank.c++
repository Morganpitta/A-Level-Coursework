#include "Entity/tank.h++"
#include "Entity/bullet.h++"
#include "battleZone.h++"
#include <iostream>

namespace BattleZone
{
    Tank::Tank( sf::Vector2f position ): Entity( position )
    {
        this->type = TankType;
        this->model = &tankModel;
        this->reloadCooldown = 0;
    }

    CollisionRect Tank::getCollisionRect() const
    {
        return CollisionRect( getPosition(), {1,2}, getRotation() );
    }

    void Tank::update( BattleZoneGame &game )
    {
        if ( this->reloadCooldown > 0)
        {
            this->reloadCooldown--;
        }

        sf::Vector2f relativePosition = relativePositionOf( game.getPlayer()->getPosition() );

        float angleOffset = atan2( relativePosition.x, relativePosition.y );

        // To the right 
        if ( angleOffset > M_PI/100.f )
        {
            turnRight( M_PI/200.f );
        }
        else if ( angleOffset < -M_PI/100.f )
        {
            turnLeft( M_PI/200.f );
        }
        else
        {
            if ( game.canMoveInDirection( this, 0.03 ) )
                moveForward( 0.03 );

            if ( this->reloadCooldown == 0 )
            {
                game.addEntity( new Bullet( getId(), getPosition(), getRotation() ) );
                this->reloadCooldown = 120;
            }
        }
    }
}