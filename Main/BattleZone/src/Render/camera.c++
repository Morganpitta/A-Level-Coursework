#include "Render/camera.h++"

Camera::Camera()
{
    this->position = {0,0,0};
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->fov = 2;
}

sf::Vector3f Camera::getPosition() const
{
    return this->position;
}


float Camera::getYaw() const
{
    return this->yaw;
}

float Camera::getPitch() const
{
    return this->pitch;
}

float Camera::getRoll() const
{
    return this->roll;
}

float Camera::getFov() const
{
    return this->fov;
}

void Camera::setPosition( sf::Vector3f position )
{
    this->position = position;
}

void Camera::setYaw( float yaw )
{
    this->yaw = normaliseAngle( yaw );
}

void Camera::setPitch( float pitch )
{
    this->pitch = normaliseAngle( pitch );
}

void Camera::setRoll( float roll )
{
    this->roll = normaliseAngle( roll );
}

void Camera::setFov( float fov )
{
    this->fov = fov;
}

void Camera::moveForward( float distance )
{
    setPosition( getPosition() + distance * get3DUnitVector( getYaw() ) );
}

sf::Vector3f Camera::relativePositionOf( sf::Vector3f position )
{
    return rotatePosition( 
        position - getPosition(),
        normaliseAngle( -getYaw() ),
        normaliseAngle( -getPitch() ),
        normaliseAngle( -getRoll() )
    );
}