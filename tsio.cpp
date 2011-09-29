#include "tsio.h"
#include <cstdio>
#include <cstring>
#include <limits>

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
void test_out ()
{
    io::Wr< MyOut > p;
    *p( 123 )( " " )( A( 123, "abcde" ) );

    *io::ou( 123 )( " e: ёклмн" );

    *io::ou1( stderr )( 123 )( " e: ёклмн" );

    *io::ou2( MyOut() )( 123 )( " o: ёклмн" );

    *io::ou( "\n-----------------\n" );
}

int main ( int argc, char* argv[] )
{
//    test_out();
    test_in();
//    test_scanf();

    *io::ou( "\n-----------------\n" );
    return 0;
}

struct MyInp : private io::Inp
{
    using io::Inp::operator();
    void operator () ( std::FILE* f, A* v, unsigned long = 0 )
    {
        assert( v );

        int n = -1;
        char s[ A::sz ];

        io::in1( f )( &n );
        io::in1( f )( s, A::len );

        v->setn( n );
        v->sets( s );
    }
};

void test_in ()
{
    using namespace io;
    char s[ 3 ] = "";
    int i = 0;

    in( s, sizeof( s ) - 1 )( &i );
    *ou( s );
    *ou( i );

    A a;
    in2< MyInp >()( &a );
    ou2< MyOut >()( a );

}

void test_scanf ()
{
    using namespace io;
    char s[ 3 ] = "";

    int res0 = fscanf( stdin, "%2s", s );
    printf( "res: %d, err: %d, eof: %d\n", res0, ferror( stdin ), feof( stdin ) );
    printf( "string: [%s], len: %d\n", s, strlen( s ) );
}
