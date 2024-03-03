#include <SFML/Graphics.hpp>
#include "time.h++"

int main()
{
    int frame = 0;
    timePoint startTime = timeNow();

    FpsLimiter fps( 60 );

    while ( true )
    {
        std::cout << ++frame / ( float(std::chrono::duration_cast<microseconds>( startTime - timeNow() ).count()) / 1000000.f ) << std::endl;
        fps.restartAndSleep();
    }

    return 0; // Program ran successfully! return 0 to represent no errors
}