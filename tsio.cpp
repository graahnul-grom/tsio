#include "tsio.h"
#include <cstdio>
#include <cstring>
#include <limits>

class A
{
public:
    enum
    {
        sz = 3
    };

private:
    int n_;
    char s_[ sz ];

public:
    A ()
        : n_( -1 )
    {
        std::strcpy( s_, "**" );
    }
    A ( int n, const char* s )
        : n_( n )
    {
        sets( s );
    }
    A ( const A& rhs )
        : n_( rhs.getn() )
    {
        sets( rhs.gets() );
    }
    A& operator = ( const A& rhs )
    {
        n_ = rhs.getn();
        sets( rhs.gets() );
        return *this;
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
void test_scanf ();

int main ( int argc, char* argv[] )
{
    io::Wr< MyOut > p;
    *p( 123 )( " " )( A( 123, "abcde" ) );

    *io::ou( 123 )( " e: ёклмн" );

    *io::ou1( stderr )( 123 )( " e: ёклмн" );

    *io::ou2( MyOut() )( 123 )( " o: ёклмн" );

    *io::ou( "\n-----------------\n" );

    test_in();

    *io::ou( "\n-----------------\n" );
    return 0;
}

struct MyInp0 : private io::Inp
{
    using io::Inp::operator();
    void operator () ( std::FILE* f, A* v )
    {
        assert( v );

        int n = -1;
        char s[ A::sz ];
        char fmt[] = "%d %2s";

        int res = std::fscanf( f, fmt, &n, s );

        *io::ou( "fscanf() res: [" )( fmt )( "] " )( res )( " " )( n )( " " )( s );

        v->setn( n );
        v->sets( s );

        *io::ou( "A: " )( v->getn() )( " " )( v->gets() );
    }
};

struct MyInp : private io::Inp
{
    using io::Inp::operator();
    void operator () ( std::FILE* f, A* v )
    {
        assert( v );

        int n = -1;
        char s[ A::sz ];

        // NOTE: the correct way to handle field sizes:
        //
        char fmt[ 128 ] = "";
        sprintf( fmt, "%%%dd %%%ds", std::numeric_limits< int >::digits, A::sz
            - 1 );

        int res = std::fscanf( f, fmt, &n, s );

        *io::ou( "fscanf() res: [" )( fmt )( "] " )( res )( " " )( n )( " " )( s );

        v->setn( n );
        v->sets( s );

        *io::ou( "A: " )( v->getn() )( " " )( v->gets() );
    }
};

void test_in ()
{
    int n = 0;
    char s[ 5 ] = "";

    A a;
    io::Rd< MyInp0 > r;
    r( &a )( s )( &n );
    *io::ou2( MyOut() )( a )( " [" )( s )( "] [" )( n )( "]" );

}

void test_scanf ()
{
}
