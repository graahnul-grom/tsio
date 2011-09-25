#include "tsio.h"
#include <cstdio>

struct A
{
};

namespace io
{
    void out ( std::FILE* f, const A& v )
    {
        std::fprintf( f, "%s", "A()" );
    }
}

int main ( int argc, char* argv[] )
{

    printf( "\n-----------------\n" );
    return 0;
}
