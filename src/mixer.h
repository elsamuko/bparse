#ifndef Mixer_H
#define Mixer_H

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/include/io.hpp>

struct Mixer {
    float r;
    float g;
    float b;
    Mixer() : r( 0 ), g( 0 ), b( 0 ) {}
};

BOOST_FUSION_ADAPT_STRUCT(
    Mixer,
    ( float, r )
    ( float, g )
    ( float, b )
)



#endif // Mixer_H
