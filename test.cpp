#include "tsio.h"
#include <cstdio>
#include <cstring>
#include <limits>
#include <cstdlib>
#include <cassert>


class A
{
public:
    enum
    {
        sz = 3, len = sz - 1
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

}; // class A




void test_in();
void test_scanf();
void test_out();



// --------------------------------
//

int main ( int argc, char* argv[] )
{
    char* e = getenv( "LANG" );
    if ( e )
        *io::wr( e )( "\n" );
    e = getenv( "SHELL" );
    if ( e )
        *io::wr( e )( "\n" );

    test_out();
    // test_in();
    // test_scanf();

    *io::wr( "\n-----------------\n" );
    return 0;
}

//
// --------------------------------



struct MyInp : private io::Inp
{
    using io::Inp::operator();
    void operator () ( std::FILE* f, A* v, unsigned long = 0 )
    {
        assert( v );

        int n = -1;
        char s[ A::sz ];

        io::rd1( f )( &n );
        io::rd1( f )( s, A::len );

        v->setn( n );
        v->sets( s );
    }
};


struct MyOut : private io::Out
{
    using io::Out::operator();
    void operator () ( std::FILE* f, const A& v )
    {
        io::wr1( f )( "A: ")( v.getn() )( ", [" )( v.gets() )( "]" );
    }
};



void test_in()
{
    using namespace io;
    char s[ 3 ] = "";
    int i = 0;

    rd( s, sizeof( s ) - 1 )( &i );
    *wr( s );
    *wr( i );

    A a;
    rd2< MyInp >()( &a );
    wr2< MyOut >()( a );
}



void test_scanf()
{
    using namespace io;
    char s[ 3 ] = "";

    int res0 = fscanf( stdin, "%2s", s );
    printf( "res: %d, err: %d, eof: %d\n", res0, ferror( stdin ), feof( stdin ) );
    printf( "string: [%s], len: %lu\n", s, strlen( s ) );
}



void test_out()
{
    io::Wr< MyOut > p;
    *p( 123 )( " " )( A( 123, "abcde" ) )( io::fl() );

    *io::wr( 123 )( " o: ёклмн" )( io::fl() );

    *io::wr1( stderr )( 123 )( " e: ёклмн" );

    *io::wr2( MyOut() )( 123 )( " o: ёклмн" )( io::fl() );


    *io::wr2( MyOut() )( 123 )( " o: ЁКЛМН!" )( io::fl() );


    *io::wr( "\n-----------------\n" );

    *io::wr( io::fl() );
}

