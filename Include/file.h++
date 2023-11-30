#if !defined( FILE_HPP )
#define FILE_HPP

    #include "crossPlatform.h++"
    #include <string>
    #include <vector>
    #include <unistd.h>
    #include <filesystem>
    #include "assert.h++"
    #if defined( OS_Windows )
        #include <windows.h>
    #endif

    std::string getWorkingDirectory()
    {
        #if defined( OS_Windows )

            TCHAR buffer[MAX_PATH]; 
            GetModuleFileName( NULL, buffer, MAX_PATH );
            return std::string( buffer );

        #else

            return std::filesystem::current_path().string();

        #endif 
    }

    bool setWorkingDirectoryToDefault()
    {
        std::string directoryString = getWorkingDirectory();

        std::vector<std::string> directories;

        std::string tmp;

        for ( char character: directoryString )
        {
            if ( !tmp.empty() && ( character == '\\' || character == '/' ) )
            {
                directories.push_back( tmp );
                tmp.clear();
            }
            else if ( !( character == '\\' || character == '/' ) )
            {
                tmp += character;
            }
        }

        if ( !tmp.empty() )
        {
            directories.push_back( tmp );
            tmp.clear();
        }

        #if ( defined( OS_Linux ) || defined( OS_Unix) )
            tmp = "/";
        #endif 

        for ( std::string string : directories )
        {
            if ( string == "A-level-Coursework-Testing" )
            {
                tmp += "A-level-Coursework-Testing/Assets";
                
                #if defined( OS_Windows )
                    std::filesystem::current_path( tmp );
                #else
                    chdir( tmp.c_str() );
                #endif

                return true;
            }
            tmp += string + "/";
        }
        
        assert( false, ( "Unable to find assets folder. (Current working directory: " + directoryString + " )" ) );
        return false;
    }

#endif /* FILE_HPP */