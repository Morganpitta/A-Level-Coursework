#include "mazeWars.h++"
#include "Entity/entity.h++"
#include "Entity/bullet.h++"
#include "Entity/player.h++"
#include "Entity/enemy.h++"
#include "random.h++"

void MazeWars::handleInput( sf::Event &event )
{
    if (event.type==sf::Event::KeyPressed)
    {
        switch ( event.key.code )
        {
            case sf::Keyboard::A:
                getPlayer()->turnLeft();
                break;
            case sf::Keyboard::D:
                getPlayer()->turnRight();
                break;
            case sf::Keyboard::W:
                if ( playerCanMove( getPlayer()->getDirection() ) )
                    getPlayer()->moveForward();
                break;
            case sf::Keyboard::S:
                if ( playerCanMove( reverseDirection( getPlayer()->getDirection() ) ) )
                    getPlayer()->moveBackward();
                break;

            default:
                break;
        }
    }
}