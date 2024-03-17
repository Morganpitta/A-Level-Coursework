sf::Vector2i Entity::relativePositionOf( sf::Vector2i position )
{
    return sf::Vector2i( rotatePosition( 
        sf::Vector2f( position - getPosition() ),
        normaliseDirection( -getDirection() )
    ) );
}

void Entity::damage( int amount )
{
    setHealth( std::max( getHealth() - amount, 0 ) );

    if ( getHealth() <= 0 )
        kill();
}

void Entity::update( MazeWars &game )
{

}