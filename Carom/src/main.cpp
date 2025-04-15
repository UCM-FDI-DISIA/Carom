#include <iostream>

#include "RNG_Manager.h"
#include "RandomItem.h"
#include "RandomItemParser.h"

#include "Game.h"

/*
la ruta para acceder a la mierda esta por codigo es

nlohmann::json
*/

void start() {
    Game g;

    g.init();
    g.start();
    g.run();
}

int main (int, char**)
{
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

    return 0;
}