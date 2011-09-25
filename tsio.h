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

    class Out
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

    class Inp
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

    template< class Impl = Out, class Term = term_flush >
    class Wr
    {
        FILE* f_;

    public:
        explicit Wr ( FILE* f = stdout )
            : f_( f )
        {
        }
        Wr ( const Wr& rhs )
            : f_( rhs.f_ )
        {
        }
        Wr& operator = ( const Wr& rhs )
        {
            if ( this != &rhs )
                f_ = rhs.f_;
            return *this;
        }

        template< class T >
        Wr& operator () ( const T& v )
        {
            Impl()( f_, v );
            return *this;
        }
        void operator * ()
        {
            Term()( f_ );
        }
    };

    template< class T >
    Wr< > ou ( const T& v )
    {
        return Wr< >( stdout )( v );
    }

    Wr< > ou1 ( FILE* f )
    {
        return Wr< >( f );
    }

    template< class T >
    Wr< T > ou2 ( const T& = T(), FILE* f = stdout )
    {
        return Wr< T >( f );
    }

} // // io

#endif //
