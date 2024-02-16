#include "camera.h++" 
#include "assert.h++"

Camera::Camera()
{
    this->position = {0,0};
    this->direction = North;
    this->fov = 2;
}

sf::Vector2i Camera::getPosition() const
{
    return this->position;
}

Direction Camera::getDirection() const
{
    return this->direction;
}

float Camera::getFov() const
{
    return this->fov;
}

void Camera::setPosition( sf::Vector2i position )
{
    this->position = position;
}

void Camera::setDirection( Direction direction )
{
    this->direction = direction;
}

void Camera::setFov( float fov )
{
    this->fov = fov;
}

void Camera::moveForward()
{
    setPosition( transposePosition( getPosition(), getDirection() ) );
}

void Camera::moveBackward()
{
    setPosition( transposePosition( getPosition(), reverseDirection( getDirection() ) ) );
}

void Camera::turnLeft()
{
    setDirection( normaliseDirection( int(getDirection()) - 1 ) );
}

void Camera::turnRight()
{
    setDirection( normaliseDirection( int(getDirection()) + 1 ) );
}

sf::Vector2f Camera::relativePositionOf( sf::Vector2f position )
{
    return rotatePosition( 
        position - sf::Vector2f( getPosition().x+0.5f, getPosition().y+0.5f ),
        normaliseDirection( -getDirection() )
    );
}