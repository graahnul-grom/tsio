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
    Wr< > wr ( const T& v )
    {
        return Wr< >( stdout )( v );
    }

    Wr< > wr1 ( FILE* f )
    {
        return Wr< >( f );
    }

    template< class Impl >
    Wr< Impl > wr2 ( const Impl& = Impl(), FILE* f = stdout )
    {
        return Wr< Impl >( f );
    }

    //
    //
    // input
    //

    class Inp
    {
        enum
        {
            fmtsz = 128
        };

    public:
        int operator () ( std::FILE* f, int* v, unsigned long width = 0 )
        {
            assert( v != 0 );

            char fmt[ fmtsz ] = "%d";
            if ( width > 0 )
                sprintf( fmt, "%%%ldd", width );

            return std::fscanf( f, fmt, v );
        }

        int operator () ( std::FILE* f, char* v, unsigned long width )
        {
            assert( v != 0 );

            char fmt[ fmtsz ] = "";
            sprintf( fmt, "%%%lds", width );

            return std::fscanf( f, fmt, v );
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
        Rd& operator () ( T v, long width = 0 )
        {
            Impl()( f_, v, width );
            return *this;
        }
//        void operator * ()
//        {
//        }
    };

    template< class T >
    Rd< > rd ( T v, long width = 0 )
    {
        return Rd< >( stdin )( v, width );
    }

    Rd< > rd1 ( FILE* f )
    {
        return Rd< >( f );
    }

    template< class Impl >
    Rd< Impl > rd2 ( const Impl& = Impl(), FILE* f = stdin )
    {
        return Rd< Impl >( f );
    }

} // // io

#endif //
