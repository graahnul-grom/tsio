#ifndef _DMN_TSIO_H_
#define _DMN_TSIO_H_

#include <cstdio>
#include <cassert>

namespace io
{
    //
    //
    // output
    //

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

    template< class Impl = Out, class Term = term_nl >
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

    //
    //
    // input
    //

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

    template< class Impl = Inp >
    class Rd
    {
        FILE* f_;

    public:
        explicit Rd ( FILE* f = stdin )
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
        Rd& operator () ( T v )
        {
            Impl()( f_, v );
            return *this;
        }
//        void operator * ()
//        {
//        }
    };


    template< class T >
    Rd< > in ( const T v )
    {
        return Rd< >( stdin )( v );
    }

    Rd< > in1 ( FILE* f )
    {
        return Rd< >( f );
    }

    template< class T >
    Rd< T > in2 ( const T& = T(), FILE* f = stdin )
    {
        return Rd< T >( f );
    }


} // // io

#endif //
