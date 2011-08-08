#include "tsio.h"
#include <cstdio>

struct A
{
};

namespace io
{
    void out( std::FILE* f, const A& v )
        { std::fprintf( f, "%s", "A()" ); }
}


int main( int argc, char* argv[] )
{
    // io::ou( 123 )( A() ); // // ?
    // io::pr( stderr )( "123" )( A() ); // // ?

    printf( "-----------------\n" );
    return 0;
}
