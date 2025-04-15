#include "InventoryManager.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include "GameScene.h"
#include "JsonEntityParser.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
    std::ofstream out_file {pathToInventory};
 
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

    if(positions.size() != MAX_BALLS){
        for(int i =0; i < MAX_BALLS; i++){
            std::string childName = "slot" + std::to_string(i);
            balls.emplace_back(JsonEntityParser::createEffectBall(scene, pathToInventory, childName));
        }
    }
    else{
        for(int i =0; i < MAX_BALLS; i++){
            std::string childName = "slot" + std::to_string(i);
            balls.emplace_back(JsonEntityParser::createEffectBall(scene, pathToInventory, childName, positions[i]));
        }
    }

    return balls;
}

entity_t 
InventoryManager::getStick(GameScene& scene) {
    //! TO DO
    //retorna el objeto de stick en el json
    auto e = JsonEntityParser::Parse(scene, pathToInventory, "stick");
    return e;
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

    bool found = false;
    std::ifstream f(pathToInventory);
    json data = json::parse(f);
    //recorre el mapa en busca de un slot vacio
    for(int i =0; i < MAX_BALLS && !found; i++){
        //si no existe el slot i, es el que va a usar
        std::string key = "slot" + std::to_string(i);
        if(data.find(key) == data.end()){
            data[key]["components"][0]["componentName"] = "BallHandler";
            data[key]["components"][0]["atributes"]["effects"] = JsonEntityParser::getBallEffects(ball);
            found = true;
        }
    }

    //update data
    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data;
    fileStream.close();
}

void
InventoryManager::addStick(entity_t stick) {
    //! TO DO
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    //data["stick"] = 
}

void 
InventoryManager::swapBall(entity_t newBall, int indexOfOldBall) {
    
    assert(indexOfOldBall >= 0 && indexOfOldBall < MAX_BALLS);
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    data["slot" + std::to_string(indexOfOldBall)]["components"][0]["atributes"]["effects"] = JsonEntityParser::getBallEffects(newBall);

    //update data
    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data;
    fileStream.close();
}

void
InventoryManager::removeBall(int index) {
    
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    data.erase("slot" + std::to_string(index));

    //update data
    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data;
    fileStream.close();
}

void InventoryManager::removeAllBalls() {
    
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    for(int i =0; i < MAX_BALLS; i++){
        data.erase("slot" + std::to_string(i));
    }

    //update data
    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data;
    fileStream.close();
}

void InventoryManager::removeStick() {
    //! TO DO
}

//guarda las bolas de la partida en el inventario.json por si hubiera ocurrido algun cambio durante la partida
void InventoryManager::saveBalls(std::vector<entity_t> balls){
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    removeAllBalls();

    for(int i =0; i < balls.size(); i++){
        data["slot" + std::to_string(i)]["components"][0]["atributes"]["effects"] = JsonEntityParser::getBallEffects(balls[i]);
    }

    //update data
    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data;
    fileStream.close();
}