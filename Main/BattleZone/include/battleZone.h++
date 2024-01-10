#if !defined( BATTLE_ZONE_HPP )
#define BATTLE_ZONE_HPP

    #include "render/renderer.h++"

    class BattleZone
    {
        Renderer renderer;
        public:
            BattleZone();

            Camera &getCamera();

            void update( sf::RenderWindow &window );

            void render( sf::RenderWindow &window );
    };

#endif /* BATTLE_ZONE_HPP */