#if !defined( FPS_HPP )
#define FPS_HPP

    #include <SFML/Window.hpp>
    #include <math.h>
    #include <unistd.h>
    #include "draw.h++"
    #include <chrono>
    #include <thread>

    typedef std::chrono::nanoseconds chronoNanoseconds; 

    chronoNanoseconds timeNow()
    {
        return std::chrono::duration_cast<chronoNanoseconds>( std::chrono::steady_clock::now().time_since_epoch() );
    }

    class FpsLimiter
    {
        float averageFps;
        chronoNanoseconds startTime;
        chronoNanoseconds maxTimePerFrame;

        public:
            FpsLimiter( float fps )
            {
                maxTimePerFrame = std::chrono::round<chronoNanoseconds>(std::chrono::duration<float>(1/fps));
                averageFps = fps;
                startTime = timeNow();
            }

            chronoNanoseconds restart()
            {
                chronoNanoseconds elapsed = (timeNow() - startTime);

                //std::cout << std::to_string(std::max( elapsed, maxTimePerFrame ).count()/1000000000.f) << std::endl;

                averageFps = ( averageFps + 1/( std::max( elapsed, maxTimePerFrame ).count()/1000000000.f ) )/2.f;
                
                startTime = timeNow();

                return elapsed;
            }

            chronoNanoseconds restartAndSleep()
            {
                chronoNanoseconds elapsed = (timeNow() - startTime);

                if ( elapsed < maxTimePerFrame )
                {
                    //https://stackoverflow.com/questions/51088819/control-loop-time-with-usleep
                    std::this_thread::sleep_until( std::chrono::steady_clock::time_point(startTime + maxTimePerFrame) );
                }

                return restart();
            }

            void draw( sf::RenderWindow &window, sf::Vector2f topLeft, std::size_t size, sf::Color colour = sf::Color::Black )
            {
                sf::Text text( std::to_string( (int) std::ceil(averageFps) ), defaultFont );

                text.setFillColor( colour );
                text.setPosition( topLeft );
                text.setCharacterSize( size );

                window.draw(text);
            }
    };

#endif /* FPS_HPP */