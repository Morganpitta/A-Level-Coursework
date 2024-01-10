#include "battleZone.h++"
#include "Entity/entity.h++"
#include <iostream>

BattleZone::BattleZone()
{
    this->nextId = 0;

    this->playerId = 
        addEntity(
            new Entity( { 0,0 } ) 
        );
}

Camera &BattleZone::getCamera()
{
    return this->renderer.getCamera();
}

Entity *BattleZone::getEntity( Id id )
{
    return this->entities[id];
}

Entity *BattleZone::getPlayer()
{
    return getEntity( this->playerId );
}

Id BattleZone::addEntity( Entity* entity )
{
    Id entityId = nextId++;
    this->entities[entityId] = entity;
    entity->setId( entityId );
    return entityId;
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
            
            case sf::Event::KeyPressed:
                if ( event.key.code == sf::Keyboard::A )
                    getPlayer()->turnLeft(M_PI/50);
                if ( event.key.code == sf::Keyboard::D )
                    getPlayer()->turnRight( M_PI/50 );
                if ( event.key.code == sf::Keyboard::W )
                    getPlayer()->moveForward( 0.1 );
                if ( event.key.code == sf::Keyboard::S )
                    getPlayer()->moveForward( -0.1 );
                if ( event.key.code == sf::Keyboard::P )
                    std::cout<<"REEEE";
                break;
        }
    }

    getCamera().setPosition( { getPlayer()->getPosition().x, 0.83, getPlayer()->getPosition().y } );
    getCamera().setYaw( getPlayer()->getRotation() );

    for ( std::pair<Id, Entity*> idEntityPair: entities )
    {
        if ( !idEntityPair.second->isDead() )
        {
            idEntityPair.second->update( *this );
        }
    }
}

void BattleZone::render( sf::RenderWindow &window )
{
    renderer.clear();
    
    // Things will be renderered at a later date

    for ( std::pair<Id, Entity*> idEntityPair: entities )
    {
        if ( idEntityPair.first != getPlayer()->getId() )
            renderer.drawEntity( window, idEntityPair.second );
    }

    renderer.display( window );
}