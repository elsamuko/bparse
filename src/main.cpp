
#include <string>
#include <iostream>

#include "mixer.h"
#include "parser.h"

int main( int /*argc*/, char** /*argv*/ ) {

    std::string data = "bs::mixer; R = -76.0000; B = 365.0000  ; g=-34.0000;";

    mixer m;
    std::string error = parseMixer( data.begin(), data.end(), m );

    if( error.empty() ) {
        std::cout << "Parsing succeeded" << std::endl;
        std::cout << "Got: " << boost::fusion::as_vector( m ) << std::endl;
    } else {
        std::cout << "Parsing failed" << std::endl;
        std::cout << "Reason: " << error << std::endl;
    }

    return 0;
}

