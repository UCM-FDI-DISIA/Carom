#include "InventoryManager.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include "GameScene.h"

#include "JsonEntityParser.h"

InventoryManager::InventoryManager()
{

}

InventoryManager::~InventoryManager() {

}

void InventoryManager::loadStartingInventory(){
    loadInventoryWithPath("../../resources/prefabs/inventoryData/storedInventory.json");
}

void InventoryManager::loadSavedInventory(){
    loadInventoryWithPath("../../resources/prefabs/inventoryData/savedInventory.json");
}

void InventoryManager::loadInventoryWithPath(std::string path){
    std::string line;

    std::ifstream ini_file {path};
    std::ofstream out_file {"../../resources/prefabs/inventoryData/inventory.json"};
 
    if(ini_file && out_file){
 
        while(std::getline(ini_file,line)){
            out_file << line << "\n";
        }
        std::cout << "Loaded " << path << " Correctly" << std::endl;
 
    } else {
        //Something went wrong
        printf("Cannot read File");
    }
}

std::vector<entity_t> 
InventoryManager::getEffectBalls(GameScene& scene, std::vector<b2Vec2> positions) {
    std::vector<entity_t> balls;
    balls.reserve(MAX_BALLS);
    std::string file = "../../resources/prefabs/inventoryData/inventory.json";

    if(positions.size() != MAX_BALLS){
        for(int i =0; i < MAX_BALLS; i++){
            std::string childName = "slot" + std::to_string(i);
            balls.emplace_back(JsonEntityParser::createEffectBall(scene, file, childName));
        }
    }
    else{
        for(int i =0; i < MAX_BALLS; i++){
            std::string childName = "slot" + std::to_string(i);
            balls.emplace_back(JsonEntityParser::createEffectBall(scene, file, childName, positions[i]));
        }
    }

    return balls;
}

entity_t 
InventoryManager::getStick(GameScene& scene) {
    //! TO DO
    //retorna el objeto de stick en el json
    return nullptr;
}

Inventory::Perma& 
InventoryManager::getPerma() {
    //! TO DO
    //retorna el perma del json
    Inventory::Perma perma{0,0,0,0,0,1.0f};
    return perma;
}
void 
InventoryManager::addBall(entity_t ball) {
    //! TO DO
}

void
InventoryManager::addStick(entity_t stick) {
    //! TO DO
}

void 
InventoryManager::swapBall(entity_t newBall, int indexOfOldBall) {
    //! TO DO
}


void
InventoryManager::removeBall(int index) {
    //! TO DO
}

void InventoryManager::removeAllBalls() {
    //! TO DO
}

void InventoryManager::removeStick() {
    //! TO DO
}