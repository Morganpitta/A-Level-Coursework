#include "camera.h++"

Camera::Camera()
{
    this->position = {0,0};
    this->rotation = 0;
    this->fov = 2;
}

sf::Vector2f Camera::getPosition() const
{
    return this->position;
}

float Camera::getRotation() const
{
    return this->rotation;
}

float Camera::getFov() const
{
    return this->fov;
}

void Camera::setPosition( sf::Vector2f position )
{
    this->position = position;
}

void Camera::setRotation( float rotation )
{
    this->rotation = normaliseAngle( rotation );
}

void Camera::setFov( float fov )
{
    this->fov = fov;
}

void Camera::moveForward( float distance )
{
    setPosition( getPosition() + distance * getUnitVector( getRotation() ) );
}

void Camera::turnLeft( float angle )
{
    setRotation( getRotation() - angle );
}

void Camera::turnRight( float angle )
{
    setRotation( getRotation() + angle );
}

sf::Vector2f Camera::relativePositionOf( sf::Vector2f position )
{
    return rotatePosition( 
        position,
        getRotation()
    );
}