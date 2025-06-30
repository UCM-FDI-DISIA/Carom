#include "Inventory.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include "GameScene.h"
#include "JsonEntityParser.h"
#include "StickInputComponent.h"

#include "DonutStickEffect.h"
#include "MagicWandStickEffect.h"
#include "BoxingGloveStickEffect.h"
#include "GranadeLauncherStickEffect.h"
#include "RewardScene.h"

Inventory::Inventory()
{

}

Inventory::~Inventory() {

}

void Inventory::loadStartingInventory(){
    loadInventoryWithPath("../../resources/prefabs/inventoryData/startingInventory.json");
}

void Inventory::loadSavedInventory(){
    loadInventoryWithPath("../../resources/prefabs/inventoryData/savedInventory.json");
}

void Inventory::loadInventoryWithPath(std::string path){
    std::string line;

    std::ifstream ini_file {path};
    std::ofstream out_file {pathToInventory};
 
    if(ini_file && out_file){
 
        while(std::getline(ini_file,line)){
            out_file << line << "\n";
        }
        #ifdef _DEBUG
        std::cout << "Loaded " << path << " Correctly" << std::endl;
        #endif
 
    } else {
        //Something went wrong
        printf("Cannot read File");
    }
}

void Inventory::loadInventoryNamed(std::string nameOfInventory){
    loadInventoryWithPath("../../resources/prefabs/inventoryData/" + nameOfInventory + ".json");
}

void Inventory::exportInventoryToSave(){
    std::string line;

    std::ifstream ini_file {pathToInventory};
    std::ofstream out_file {"../../resources/prefabs/inventoryData/savedInventory.json"};
 
    if(ini_file && out_file){
 
        while(std::getline(ini_file,line)){
            out_file << line << "\n";
        }
        #ifdef _DEBUG
        std::cout << "Loaded " << pathToInventory << " Correctly" << std::endl;
        #endif
 
    } else {
        //Something went wrong
        #ifdef _DEBUG
        printf("Cannot read File");
        #endif
    }
}

/* SHOULD NOT BE HERE

std::vector<entity_t> 
Inventory::getEffectBalls(GameScene& scene, std::vector<b2Vec2> positions = std::vector<b2Vec2>{}) {
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
Inventory::getStick(GameScene& scene) {
    //retorna el objeto de stick en el json
    return JsonEntityParser::createStick(scene, pathToInventory, "stick");
}

*/

bool
Inventory::addBall(std::vector<effectId_t> ids) {

    bool found = false;
    int i =0;
    while(i < MAX_BALLS && !found){
        if(!_slots[i].used) {
            found = true;
            _slots[i].ballEffects = ids;
        }
        i++;
    }

    return found;
}

void
Inventory::removeBall(int index) {
    assert(index < MAX_BALLS);
    _slots[index].used = false;
}

void Inventory::removeAllBalls() {
    for(auto slot: _slots){
        slot.used = false;
    }
}

void Inventory::removeStick() {
    setStick(stick::NORMAL_STICK);
}

int Inventory::getNumberOfEffectBalls(){
    int res = 0;
    for(auto slot : _slots){
        if(slot.used) res++;
    }
    return res;
}
//------------------------------------- P E R M A ----------------------------------------

int Inventory::getHitEase(){ return _hitEase;}
void Inventory::setHitEase(int i){_hitEase = i;}

int Inventory::getCombo(){return _combo}
void Inventory::setCombo(int i){_combo = i;}

int Inventory::getEase(){return _ease;}
void Inventory::setCaromEase(int i){_ease = i;}

int Inventory::getCharisma(){return _charisma;}
void Inventory::setCharisma(int i){_charisma = i;}

int Inventory::getPower(){return _power;}
void Inventory::setPower(int i){_power = i;}

float Inventory::getCunning(){return _cunning;}

void Inventory::setCunning(float f){_cunning = f;}

stickId_t Inventory::getStickType() {return _stick;}

void Inventory::setStick(stick::stickId s) {_stick = s;}

std::vector<effectId_t> Inventory::getEffectsFromBall(int index) {
    assert(index < MAX_BALLS);
    return _slots[index].ballEffects;
}