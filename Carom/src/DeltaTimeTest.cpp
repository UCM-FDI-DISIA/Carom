#include "SDLUtils.h"
#include <vector>
#include <set>
#include "testBox2D.cpp"

void deltaTimeTest(){
    
    SDLUtils::Init("Test", 800, 600);
    SDLUtils* sdlUtils = SDLUtils::Instance();
    
    sdlUtils->regCurrTime();
    std::cout << "First test: \n";
    // First test, counting to 100
    for(int i = 0; i < 100; i++){
        sdlUtils->regCurrTime();
        std::cout << i << ", ";
        std::cout << sdlUtils->deltaTime() << "\n";
    }
    
    std::cout << "\nSecond test: \n";
    // Second test, operating with integers
    int h = 0;
    for(int i = 0; i < 10; i++){
        sdlUtils->regCurrTime();
        h += 10;
        h *= 2;
        h-= 40;
        std::cout << h << ", ";
        std::cout << sdlUtils->deltaTime() << "\n";
    }
    
    std::cout << "\nThird test: \n";
    // Third test, using set
    
    std::cout << "\nEmplacing 13 ints in a set:\n";
    std::set<int> unordered_list;
    
    sdlUtils->regCurrTime();
    unordered_list.emplace(4);
    unordered_list.emplace(16);
    unordered_list.emplace(2);
    unordered_list.emplace(-8);
    unordered_list.emplace(4);
    unordered_list.emplace(9);
    unordered_list.emplace(20);
    unordered_list.emplace(425);
    unordered_list.emplace(3);
    unordered_list.emplace(3);
    unordered_list.emplace(12);
    unordered_list.emplace(-55);
    unordered_list.emplace(8);
    sdlUtils->regCurrTime();
    
    std::cout << "DeltaTime: " << sdlUtils->deltaTime() << "\n";
    
    std::cout << "\nFourth test:\n";
    //Fourth test, executing the entire box2d test
    sdlUtils->regCurrTime();
    std::set<int> list;
    for(int i = 0; i < 1000000; ++i){
        list.emplace(i);
    }
    sdlUtils->regCurrTime();
    
    std::cout << "DeltaTime 1000000: " << sdlUtils->deltaTime() << "\n";

    std::set<int> list2;
    sdlUtils->regCurrTime();
    for(int i = 0; i < 10000; ++i){
        list2.emplace(i);
    }
    sdlUtils->regCurrTime();
    
    std::cout << "DeltaTime 10000: " << sdlUtils->deltaTime() << "\n";
    
    std::set<int> list3;
    sdlUtils->regCurrTime();
    for(int i = 0; i < 1000; ++i){
        list3.emplace(i);
    }
    sdlUtils->regCurrTime();
    
    std::cout << "DeltaTime 1000: " << sdlUtils->deltaTime() << "\n";
}