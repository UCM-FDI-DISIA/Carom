#include <iostream>
#include "sdlutils_demo.h"
#include "inputTest.h"

int main (int, char**)
{
    try {
        inputTest_basic_demo();
    } catch (const std::string &e) { // catch exceptions thrown as strings
        std::cerr << e << std::endl;
    } catch (const char *e) { // catch exceptions thrown as char*
        std::cerr << e << std::endl;
    } catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
        std::cerr << e.what();
    } catch (...) {
        std::cerr << "Caught and exception of unknown type ...";
    }

    return 0;
}