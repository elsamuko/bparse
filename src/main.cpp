
#include <string>
#include <iostream>

#include "mixer.h"
#include "parser.h"
#include "generator.h"

bool operator== ( const Mixer& lhs, const Mixer& rhs ) {
    return boost::fusion::as_vector( lhs ) == boost::fusion::as_vector( rhs );
}

int main( int /*argc*/, char** /*argv*/ ) {

    std::wstring data = L"bs::Mixer; R = -76.0000; B = 365.0000  ; g=-34.0000;";
    std::wstring out;

    Mixer m;
    Mixer m2;

    // back ...
    std::cout << std::endl;
    {
        std::string error = parseMixer( data, m );

        if( error.empty() ) {
            std::cout << "Parsing succeeded" << std::endl;
            std::cout << "Got: " << boost::fusion::as_vector( m ) << std::endl;
        } else {
            std::cout << "Parsing failed" << std::endl;
            std::cout << "Reason: " << error << std::endl;
        }
    }

    // ... and forth ...
    std::cout << std::endl;
    {
        std::string error = generateMixer( out, m );

        if( error.empty() ) {
            std::cout << "Generating succeeded" << std::endl;
            std::wcout << L"Got: " << out << std::endl;
        } else {
            std::cout << "Generating failed" << std::endl;
            std::cout << "Reason: " << error << std::endl;
        }
    }

    // ... and back
    std::cout << std::endl;
    {
        std::string error = parseMixer( out, m2 );

        if( error.empty() && ( m == m2 ) ) {
            std::cout << "Roundtrip succeeded" << std::endl;
            std::cout << "Got: " << boost::fusion::as_vector( m2 ) << std::endl;
        } else {
            std::cout << "Parsing failed" << std::endl;
            std::cout << "Reason: " << error << std::endl;
        }
    }

    std::cout << std::endl;
    return 0;
}

