#include "renderer.h++"
#include "Entity/entity.h++"

void Renderer::drawWallVertical(
    sf::Vector2f position
)
{
    float wallHeight = std::floor( this->wallHeight / position.y );
    
    appendLineToArray(
        wallVertices,
        sf::Vector2f(
            std::floor(position.x),
            ( getDisplaySize().y + wallHeight ) / 2
        ),
        sf::Vector2f(
            std::floor(position.x),
            ( getDisplaySize().y - wallHeight ) / 2
        ),
        sf::Color::Green
    );
}

void Renderer::drawWallHorizontals(
    sf::Vector2f &wallStart,
    sf::Vector2f &wallEnd
)
{
    float wallStartHeight = std::floor( this->wallHeight / wallStart.y );
    float wallEndHeight = std::floor( this->wallHeight / wallEnd.y );

    appendLineToArray(
        wallVertices,
        sf::Vector2f(
            wallStart.x,
            ( getDisplaySize().y + std::floor( wallStartHeight ) ) / 2
        ),
        sf::Vector2f(
            wallEnd.x,
            ( getDisplaySize().y + std::floor( wallEndHeight ) ) / 2
        ),
        sf::Color::Green
    );

    appendLineToArray(
        wallVertices,
        sf::Vector2f(
            wallStart.x,
            ( getDisplaySize().y - std::floor( wallStartHeight ) ) / 2
        ),
        sf::Vector2f(
            wallEnd.x,
            ( getDisplaySize().y - std::floor( wallEndHeight ) ) / 2
        ),
        sf::Color::Green
    );
}

void Renderer::drawWall(
    sf::Vector2f &wallStart,
    sf::Vector2f &wallEnd
)
{
    drawWallVertical(  wallStart );

    drawWallVertical( wallEnd );

    // If it's one or two pixels thin we can stop
    if ( std::floor( wallEnd.x ) - std::floor( wallStart.x ) <= 1 )
        return;

    drawWallHorizontals( wallStart, wallEnd );
}