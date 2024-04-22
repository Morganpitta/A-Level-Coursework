#include <filesystem>
#include <iostream>
#include <fstream>

void pasteContents( std::string folderPath, std::ofstream &outputFile )
{
    for ( const auto &entry: std::filesystem::recursive_directory_iterator( folderPath ) )
    {
        if ( entry.is_directory() )
            continue;
        std::string path = entry.path().string(); 
        std::ifstream inputFile( path );
        if ( !inputFile.is_open() )
        {
            std::cout << "FAILED TO OPEN: " << path << std::endl;
            continue;
        }
        outputFile << "// File: " << path << "\n\n";
        outputFile << inputFile.rdbuf();
        outputFile << "\n\n\n";
        std::cout << "SUCCESSFULLY OPENED: " << path << std::endl;
    }
}

int main()
{
    std::ofstream outputFile( "C:\\Users\\Morga\\Documents\\GitHub\\A-Level-Coursework\\Main\\Tests\\everything.c++" );
    outputFile.clear();
    
    pasteContents( "Main\\MazeWars\\include", outputFile );
    pasteContents( "Main\\MazeWars\\src", outputFile );
    pasteContents( "Main\\BattleZone\\include", outputFile );
    pasteContents( "Main\\BattleZone\\src", outputFile );
}