#ifndef _DMN_TSIO_H_
#define _DMN_TSIO_H_

#include <cstdio>

namespace io
{
    void out ( std::FILE* f, const int v )
    {
        std::fprintf( f, "%d", v );
    }

    void out ( std::FILE* f, const char* v )
    {
        std::fprintf( f, "%s", v );
    }

    class pr
    {
        FILE* f_;

    public:
        explicit pr ( FILE* f )
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
            io::out( f_, v );
            return *this;
        }
//        void operator * ()
//            { out( f_, "\n" ); }
    };

    template< class T >
    pr ou ( const T& v )
    {
        return pr( stdout )( v );
    }

} // // io

#endif //
