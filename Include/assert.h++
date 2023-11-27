#if !defined( ASSERT_HPP )
#define ASSERT_HPP

    #include <iostream>
    #include <string>
    #include <unistd.h>

    #ifndef NDEBUG
    #   define assertCondition(Expr, Msg) \
        __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
    #else
    #   define assertCondition(Expr, Msg)
    #endif

    void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const std::string msg)
    {
        if (!expr)
        {
            std::cerr << "Assert failed:\t" << msg << "\n"
                << "Expected:\t" << expr_str << "\n"
                << "Source:\t\t" << file << ", line " << line << "\n";
            
            sleep( 10 );
            abort();
        }
    }

#endif /* ASSERT_HPP */