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
    io::pr< MyOut > p;
    *p( 123 )( " " )( A() )( io::nl() );

    *io::ou( 123 )( "e: ёклмн" )( io::nl() );

    *io::ou1( stderr )( 123 )( "e: ёклмн" )( "\n" );

    *io::ou2( MyOut() )( 123 )( "o: ёклмн" )( "\n" );

    printf( "\n-----------------\n" );
    return 0;
}
