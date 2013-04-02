#ifndef GENERATOR_H
#define GENERATOR_H

#include <boost/spirit/include/karma.hpp>

#include "mixer.h"

namespace karma = boost::spirit::karma;

using karma::lit;
using karma::float_;
using karma::generate;

template <typename Iterator>
karma::rule<Iterator, float()> generateColor( const std::string& name, const float& f ) {
    karma::rule<Iterator, float()> c;

    // e.g.   r              =             45.0      ;
    c = lit( name ) << lit( "=" ) << float_( f ) << ';';
    return c;
}


template <typename StringT>
std::string generateMixer( StringT& out, const Mixer& m ) {
    std::string error;
    std::back_insert_iterator<StringT> sink( out );

    typedef std::back_insert_iterator< StringT > Iterator;
    typedef karma::rule<Iterator, float()> rule;

    rule red   = generateColor<Iterator>( "r", m.r );
    rule green = generateColor<Iterator>( "g", m.g );
    rule blue  = generateColor<Iterator>( "b", m.b );


    bool ok = generate( sink,
                        (
                            "bs::Mixer; " << red << " " << green << " " << blue
                        ),
                        m.r, m.g, m.b
                      );

    if( !ok ) {
        error += "Could not generate expression\n";
    }

    return error;
}

#endif // GENERATOR_H
