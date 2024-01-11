#include "Entity/tank.h++"
#include "battleZone.h++"
#include <iostream>

Tank::Tank( sf::Vector2f position )
{
    this->type = TankType;
    this->model = &tankModel;
    this->reloadCooldown = 0;
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
        moveForward( 0.03 );
    }
}