#ifndef _DMN_TSIO_H_
#define _DMN_TSIO_H_

#include <cstdio>
#include <cassert>

namespace io
{
    struct nl
    {
    };

    struct fl
    {
    };

    class out
    {
        /* (3.9.1):
         * void
         * bool
         * wchar_t
         * char
         * unsineg char
         * short int
         * unsigned short int
         * int
         * unsigned int
         * long int
         * unsigned long int
         * float
         * double
         * long double
         *
         * */
    public:
        void operator () ( std::FILE* f, const int v )
        {
            std::fprintf( f, "%d", v );
        }

        void operator () ( std::FILE* f, const char* v )
        {
            std::fprintf( f, "%s", v );
        }

        void operator () ( std::FILE* f, const nl& )
        {
            std::fprintf( f, "\n" );
        }

        void operator () ( std::FILE* f, const fl& )
        {
            std::fflush( f );
        }
    };

    class in
    {
    public:
        int operator () ( std::FILE* f, int* v )
        {
            assert( v != 0 );
            return std::fscanf( f, "%d", v );
        }
        int operator () ( std::FILE* f, char* v )
        {
            assert( v != 0 );
            return std::fscanf( f, "%s", v );
        }
    };

    struct term_nop
    {
        void operator () ( std::FILE* )
        {
        }
    };

    struct term_nl
    {
        void operator () ( std::FILE* f )
        {
            std::fprintf( f, "\n" );
        }
    };

    struct term_flush
    {
        void operator () ( std::FILE* f )
        {
            std::fflush( f );
        }
    };

    template< class Out = out, class Term = term_flush >
    class Rd
    {
        FILE* f_;

    public:
        explicit Rd ( FILE* f = stdout )
            : f_( f )
        {
        }
        Rd ( const Rd& rhs )
            : f_( rhs.f_ )
        {
        }
        Rd& operator = ( const Rd& rhs )
        {
            if ( this != &rhs )
                f_ = rhs.f_;
            return *this;
        }

        template< class T >
        Rd& operator () ( const T& v )
        {
            Out()( f_, v );
            return *this;
        }
        void operator * ()
        {
            Term()( f_ );
        }
    };

    template< class T >
    Rd< > ou ( const T& v )
    {
        return Rd< >( stdout )( v );
    }

    Rd< > ou1 ( FILE* f )
    {
        return Rd< >( f );
    }

    template< class T >
    Rd< T > ou2 ( const T& = T(), FILE* f = stdout )
    {
        return Rd< T >( f );
    }

} // // io

#endif //
