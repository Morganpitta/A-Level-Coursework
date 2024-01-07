#if !defined( FPS_HPP )
#define FPS_HPP

    #include <SFML/Window.hpp>
    #include <math.h>
    #include <unistd.h>
    #include "draw.h++"
    #include <chrono>
    #include <thread>
    #include <iostream>

    typedef std::chrono::_V2::system_clock::time_point timePoint;
    typedef std::chrono::microseconds microseconds;

    inline timePoint timeNow()
    {
        return std::chrono::high_resolution_clock::now();
    }

    class FpsLimiter
    {
        float averageFps;
        timePoint startTime;
        microseconds maxDuration;

        public:
            FpsLimiter( int fps )
            {
                this->maxDuration = std::chrono::microseconds(int(1000000.f/fps));
                this->averageFps = fps;
                this->startTime = timeNow();
            }

            microseconds restart()
            {
                microseconds duration = std::chrono::duration_cast<microseconds>( timeNow() - this->startTime );

                this->averageFps = ( this->averageFps + 1/( std::max( duration, this->maxDuration ).count()*1000000.f ) )/2.f;
                
                this->startTime = timeNow();

                return duration;
            }

            microseconds restartAndSleep()
            {
                microseconds duration = std::chrono::duration_cast<microseconds>(timeNow() - this->startTime);

                if ( duration < maxDuration )
                {
                    //https://stackoverflow.com/questions/51088819/control-loop-time-with-usleep
                    std::this_thread::sleep_until( startTime + maxDuration );
                }

                this->averageFps = ( this->averageFps + 1/( std::max( duration, this->maxDuration ).count()/1000000.f ) )/2.f;
                
                this->startTime = timeNow();

                return duration;
            }

            void draw( sf::RenderWindow &window, sf::Vector2f topLeft, std::size_t size, sf::Color colour = sf::Color::Black )
            {
                sf::Text text( std::to_string( (int) std::ceil( this->averageFps ) ), defaultFont );

                text.setFillColor( colour );
                text.setPosition( topLeft );
                text.setCharacterSize( size );

                window.draw(text);
            }
    };

    class TimeDebugger
    {
        std::map<std::string,timePoint> startTimes;
        std::map<std::string,microseconds> averageTimes;

        public:
            void start( std::string name )
            {
                this->startTimes[name] = timeNow();
            }

            void end( std::string name )
            {
                assert( startTimes.count(name) > 0, "Invalid debug time point" );

                microseconds duration = std::chrono::duration_cast<microseconds>( timeNow() - this->startTimes[name] );

                averageTimes[name] = ( averageTimes[name] + duration )/2;
            }

            void draw( sf::RenderWindow &window, sf::Vector2f topLeft, std::size_t size, sf::Color colour = sf::Color::Black )
            {
                std::string times = "";
                for ( std::pair<std::string,microseconds> nameDurationPair: averageTimes )
                {
                    times += nameDurationPair.first + ": " + std::to_string(nameDurationPair.second.count());
                }

                sf::Text text( times, defaultFont );

                text.setFillColor( colour );
                text.setPosition( topLeft );
                text.setCharacterSize( size );

                window.draw(text);
            }
    };

#endif /* FPS_HPP */