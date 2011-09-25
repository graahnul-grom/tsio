#include "tsio.h"
#include <cstdio>

struct A
{
};

struct MyOut : private io::out
{
    using io::out::operator();
    void operator () ( std::FILE* f, const A& v )
    {
        std::fprintf( f, "%s", "A()" );
    }
};

int main ( int argc, char* argv[] )
{
    io::pr< MyOut > p( stdout );
    p( 123 )( " " )( A() )( "\n" );

    printf( "\n-----------------\n" );
    return 0;
}
