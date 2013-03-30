#ifndef MIXER_H
#define MIXER_H

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

struct mixer {
    float r;
    float g;
    float b;
    mixer() : r( 0 ), g( 0 ), b( 0 ) {}
};

BOOST_FUSION_ADAPT_STRUCT(
    mixer,
    ( float, r )
    ( float, g )
    ( float, b )
)

#endif // MIXER_H
