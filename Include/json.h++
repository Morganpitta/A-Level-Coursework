#if !defined( JSON_H )
#define JSON_H

    #include <nlohmann/json.hpp>
    #include <fstream>

    // Documentation: https://github.com/nlohmann/json#read-json-from-a-file;

    // Literally just renaming for easier use. Thanks for the library nlohmann!
    typedef nlohmann::json Json; 

#endif /* JSON_H */