//#define _CRTDBG_MAP_ALLOC // ! This thing fucking kills the project for some reason

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "RNG_Manager.h"
#include "RandomItem.h"
#include "RandomItemParser.h"

#include "Game.h"

void start() {
    Game g;

    g.init();
    g.start();
    g.run();
}

int main (int, char**)
{
    // _CrtSetBreakAlloc(73706);

    #ifdef _WIN32
    SetProcessDPIAware();
    #endif

    try {
        start();
    } catch (const std::string &e) { // catch exceptions thrown as strings
        std::cerr << e << std::endl;
    } catch (const char *e) { // catch exceptions thrown as char*
        std::cerr << e << std::endl;
    } catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
        std::cerr << e.what();
    } catch (...) {
        std::cerr << "Caught and exception of unknown type ...";
    }
 
    _CrtDumpMemoryLeaks();
    return 0;
}