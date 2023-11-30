#if !defined( ASSERT_HPP )
#define ASSERT_HPP

    #include <string>
    #include <stdexcept>

    #ifndef NDEBUG
    #   define assert(expression, message) \
        AssertMacro(#expression, expression, __FILE__, __LINE__, message)
    #else
    #   define assert(expression, message)
    #endif

    void AssertMacro(const char* expressionString, bool expressionValue, const char* file, int line, const std::string message)
    {
        if (!expressionValue)
        {
            throw std::runtime_error(  
                "\n"
                "Assertion failed: " + message + "\n"
                "Expected:         " + expressionString + "\n"
                "In file           " + file + ", line " + std::to_string( line ) + "\n"
            );
        }
    }

#endif /* ASSERT_HPP */