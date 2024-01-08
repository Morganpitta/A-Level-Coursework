#if !defined( RANDOM_HPP )
#define RANDOM_HPP

    #define _USE_MATH_DEFINES
    #include <math.h>
    #include <random>

    /* Random */
    // The Mersenne twister engine.
    // You can use rng() to get a number between 0 and 2^(19937) – 1 (hence the name)

    inline std::mt19937 rng;
    inline void setRandomNumberSeed( double seed )
    {
        rng.seed(seed);
    }
    
    // this uses the twister engine to create a uniform distribution;
    inline int randomInt( int start, int end )
    {
        std::uniform_int_distribution<> dist(start,end);
        
        return dist(rng);
    }

    inline float randomFloat( float start, float end )
    {
        std::uniform_real_distribution<> dist(start,end);
        
        return dist(rng);
    }

#endif /* RANDOM_HPP */