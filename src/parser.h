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
using ascii::space;
using ascii::no_case;
using phoenix::ref;

template <typename T>
qi::rule<T, float, ascii::space_type> color( std::string name, float& f, bool& ok ) {
    qi::rule<T, float, ascii::space_type> c;

    // e.g.             r                                  =                   45.0           ;
    c %= no_case[lit( name )][ ref( ok ) = true ] >> lit( "=" ) >> float_[ ref( f ) = _1] >> ';';
    return c;
}

template <typename Iterator>
std::string parseMixer( Iterator first, Iterator last, mixer& m ) {

    std::string error;

    typedef qi::rule<Iterator, float, ascii::space_type> rule;
    bool rok = false;
    bool gok = false;
    bool bok = false;

    rule red   = color<Iterator>( "r", m.r, rok );
    rule green = color<Iterator>( "g", m.g, gok );
    rule blue  = color<Iterator>( "b", m.b, bok );

    bool ok = phrase_parse( first, last,
                            (
                                no_case[ lit( "bs::mixer;" ) ]
                                >> ( red | green | blue )
                                >> ( red | green | blue )
                                >> ( red | green | blue )
                            ),
                            space );

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
