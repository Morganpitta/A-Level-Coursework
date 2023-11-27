#if !defined( CROSS_PLATFORM_HPP )
#define CROSS_PLATFORM_HPP

 #if defined( _WIN32 ) || defined( WIN32 ) 
    #define OS_Windows
#else
    #define OS_Linux
#endif


#if defined( OS_Windows )
    #include <windows.h>
#elif defined( OS_Linux )
    #include <time.h>   // for nanosleep
#else
    #include <unistd.h> // for usleep
#endif

void sleepFor(int milliseconds)
{
    #ifdef OS_Windows
        Sleep(milliseconds);
    #elif defined( OS_Linux )
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    #else
        if (milliseconds >= 1000)
            sleep(milliseconds / 1000);
        usleep((milliseconds % 1000) * 1000);
    #endif
}

#endif /* CROSS_PLATFORM_HPP */