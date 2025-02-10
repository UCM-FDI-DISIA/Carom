#include "SDLUtils.h"

void deltaTimeTest(){
    
    SDLUtils* sdlUtils = SDLUtils::Instance();

    // First test, counting to 100
    for(int i = 0; i < 100; i++){
        std::cout << i;
        std::cout << sdlUtils->deltaTime();
    }
}