#if !defined( STRING_HPP )
#define STRING_HPP

    #include <string>
    #include <array>
    
    template<typename ...Args>
    std::string format( std::string string, Args... arguments )
    {
        char cstring[] = string.c_str();
        sprintf( cstring, arguments... );
        string = cstring;

        return string;
    }

#endif /* STRING_HPP */