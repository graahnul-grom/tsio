#include "tsio.h"
#include <cstdio>
#include <cstring>

class A
{
    int n_;
    char s_[ 3 ];
public:
    A ()
        : n_( -1 )
    {
        std::strcpy( s_, "" );
    }
    A ( int n, const char* s )
        : n_( n )
    {
        sets( s );
    }
    int getn () const
    {
        return n_;
    }
    const char* gets () const
    {
        return s_;
    }
    void setn ( int n )
    {
        n_ = n;
    }
    void sets ( const char* s )
    {
        std::strncpy( s_, s, sizeof( s_ ) );
        s_[ sizeof( s_ ) - 1 ] = '\0';
    }
};

struct MyOut : private io::Out
{
    using io::Out::operator();
    void operator () ( std::FILE* f, const A& v )
    {
        std::fprintf( f, "[ A: %d, %s ]", v.getn(), v.gets() );
    }
};

void test_in ();

int main ( int argc, char* argv[] )
{
    io::Wr< MyOut > p;
    *p( 123 )( " " )( A( 123, "12345" ) )( io::nl() );

    *io::ou( 123 )( " e: ёклмн" )( io::nl() );

    *io::ou1( stderr )( 123 )( " e: ёклмн" )( "\n" );

    *io::ou2( MyOut() )( 123 )( " o: ёклмн" )( "\n" );

    *io::ou( "\n-----------------\n" );

    test_in();

    *io::ou( "\n-----------------\n" );
    return 0;
}

void test_in ()
{
    int n = 0;
    char s[ 10 ] = "";

    io::in( &n )( s );
    io::ou( n )( " " )( s );

}
