#include "tsio.h"
#include <cstdio>
#include <cstring>

struct A
{
};

struct MyOut : private io::Out
{
    using io::Out::operator();
    void operator () ( std::FILE* f, const A& v )
    {
        std::fprintf( f, "%s", "A()" );
    }
};

void test_in ();

int main ( int argc, char* argv[] )
{
    io::Wr< MyOut > p;
    *p( 123 )( " " )( A() )( io::nl() );

    *io::ou( 123 )( "e: ёклмн" )( io::nl() );

    *io::ou1( stderr )( 123 )( "e: ёклмн" )( "\n" );

    *io::ou2( MyOut() )( 123 )( "o: ёклмн" )( "\n" );

    *io::ou( "\n-----------------\n" );

    test_in();

    *io::ou( "\n-----------------\n" );
    return 0;
}

void test_in ()
{
    int n = 0;
    char s[ 10 ] = "";

    io::Inp i;
    i( stdin, &n );
    i( stdin, s );

    io::ou( n )( " " )( s );

}
