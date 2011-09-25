#ifndef _DMN_TSIO_H_
#define _DMN_TSIO_H_

#include <cstdio>

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
            return std::fscanf( f, "%d", v );
        }
        int operator () ( std::FILE* f, char* v )
        {
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
    class pr
    {
        FILE* f_;

    public:
        explicit pr ( FILE* f = stdout )
            : f_( f )
        {
        }
        pr ( const pr& rhs )
            : f_( rhs.f_ )
        {
        }
        pr& operator = ( const pr& rhs )
        {
            if ( this != &rhs )
                f_ = rhs.f_;
            return *this;
        }

        template< class T >
        pr& operator () ( const T& v )
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
    pr< > ou ( const T& v )
    {
        return pr< >( stdout )( v );
    }

    pr< > ou1 ( FILE* f )
    {
        return pr< >( f );
    }

    template< class T >
    pr< T > ou2 ( const T& = T(), FILE* f = stdout )
    {
        return pr< T >( f );
    }

} // // io

#endif //
