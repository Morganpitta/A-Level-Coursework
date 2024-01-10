#include "battleZone.h++"

BattleZone::BattleZone()
{
    
}

Camera &BattleZone::getCamera()
{
    return this->renderer.getCamera();
}

void BattleZone::update( sf::RenderWindow &window )
{
    sf::Event event;
    while ( window.pollEvent(event) )
    {
        switch ( event.type )
        {
            case sf::Event::Closed:
                window.close();
                break;
        }
    }
}

void BattleZone::render( sf::RenderWindow &window )
{
    renderer.clear();
    
    // Things will be renderered at a later date

    renderer.display( window );
}