#include <iostream>
#include <stdexcept>

#include "Application.hpp"

int main( void ) {
    try {
        Application app;
        app.run();
    }
    catch (std::exception const &e) {
        std::cerr << "Fatal: " << e.what() << '\n';
        return 1;
    }

    return 0;
}