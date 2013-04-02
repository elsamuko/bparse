#ifndef PARSER_H
#define PARSER_H

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include "mixer.h"

namespace qi      = boost::spirit::qi;
namespace ascii   = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using qi::_1;
using qi::lit;
using qi::float_;
using ascii::no_case;
using phoenix::ref;

template <typename Iterator>
qi::rule<Iterator, float, ascii::space_type> parseColor( std::string name, float& f, bool& ok ) {
    qi::rule<Iterator, float, ascii::space_type> c;

    // e.g.            r                                    =                   45.0            ;
    c = no_case[ lit( name ) ][ ref( ok ) = true ] >> lit( "=" ) >> float_[ ref( f ) = _1 ] >> ';';
    return c;
}

template <typename StringT>
std::string parseMixer( const StringT& in, Mixer& m ) {

    std::string error;

    typedef typename StringT::const_iterator Iterator;
    Iterator first = in.begin();
    Iterator last  = in.end();

    typedef qi::rule<Iterator, float, ascii::space_type> rule;
    bool rok = false;
    bool gok = false;
    bool bok = false;

    rule red   = parseColor<Iterator>( "r", m.r, rok );
    rule green = parseColor<Iterator>( "g", m.g, gok );
    rule blue  = parseColor<Iterator>( "b", m.b, bok );

    bool ok = phrase_parse( first, last,
                            (
                                no_case[ lit( "bs::Mixer;" ) ]
                                >> ( red | green | blue )
                                >> ( red | green | blue )
                                >> ( red | green | blue )
                            ),
                            ascii::space );

    if( !ok ) {
        error += "Could not parse expression\n";
    }

    if( !rok ) {
        error += "Did not find a red value\n";
    }

    if( !gok ) {
        error += "Did not find a green value\n";
    }

    if( !bok ) {
        error += "Did not find a blue value\n";
    }

    if( first != last ) {
        error += "Failed to parse whole expression\n";
    }

    return error;
}

#endif // PARSER_H
