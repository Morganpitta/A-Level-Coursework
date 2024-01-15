#include "Entity/tank.h++"
#include "Entity/bullet.h++"
#include "battleZone.h++"
#include <iostream>

Tank::Tank( sf::Vector2f position ): Entity( position )
{
    this->type = TankType;
    this->model = &tankModel;
    this->reloadCooldown = 0;
    this->radius = 0.7;
}

void Tank::update( BattleZone &game )
{
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
        if ( !isColliding( 
                this, 
                0.03f * get2DUnitVector( getRotation() ), 
                game.getEntities(),
                [ this ]( Entity *entity) { return entity->getType() != BulletType; }
            ) )
            moveForward( 0.03 );
        
        game.addEntity( new Bullet( getId(), getPosition(), getRotation() ) );
    }
}