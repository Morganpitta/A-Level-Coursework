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

void BattleZone::cleanUpEntities()
{
    for ( auto iterator = this->entities.begin(); iterator != this->entities.end(); )
    {
        Entity *entity = (*iterator).second; 
        if ( entity->isDead() && entity->getType() != PlayerType )
            iterator = this->entities.erase( iterator );
        else
            iterator++;
    }
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
                if ( event.key.code == sf::Keyboard::P )
                    std::cout<<"REEEE";
                break;
        }
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
        getPlayer()->turnLeft( M_PI/70 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
        getPlayer()->turnRight( M_PI/70 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
        getPlayer()->moveForward( 0.1 );
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
        getPlayer()->moveForward( -0.1 );

    getCamera().setPosition( { getPlayer()->getPosition().x, 0.85, getPlayer()->getPosition().y } );
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

    renderer.drawBackground( window );

    for ( std::pair<Id, Entity*> idEntityPair: entities )
    {
        if ( idEntityPair.first != getPlayer()->getId() )
            renderer.drawEntity( window, idEntityPair.second );
    }

    renderer.display( window );
}