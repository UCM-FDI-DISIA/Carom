#include "Inventory.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include "GameScene.h"
#include "JsonEntityParser.h"
#include "StickInputComponent.h"
#include <nlohmann/json.hpp>

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
    loadInventoryWithPath(pathToSavedInventory);
}

void Inventory::loadInventoryWithPath(std::string path){
    std::ifstream f(path);
    
    nlohmann::json data = nlohmann::json::parse(f);

    _ease = data["ease"];
    _charisma = data["charisma"];
    _combo = data["combo"];
    _hitEase = data["hitEase"];
    _power = data["power"];
    _cunning = data["cunning"];
    

    for(int i =0; i < MAX_BALLS; i++){
        std::string slotName = "slot_" + std::to_string(i);
        _slots[i].used = data[slotName]["used"];
        _slots[i].ballEffects = data[slotName]["ballEffects"];
    }
}

void Inventory::exportInventoryToSave(){
    std::ifstream f(pathToSavedInventory);
    
    nlohmann::json data = nhlomann::json();
    data.erase();

    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data.dump(3);
    fileStream.close();
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
    _slots[index].ballEffects.clear();
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

void Inventory::setStick(stickId_t s) {_stick = s;}

std::vector<effectId_t> Inventory::getEffectsFromBall(int index) {
    assert(index < MAX_BALLS);
    return _slots[index].ballEffects;
}

std::array<SlotInfo, MAX_BALLS> Inventory::getSlotsInfo() {
    std::array<SlotInfo, MAX_BALLS> res;
    for(int i =0; i < MAX_BALLS; i++) {
        res[i].ballEffects = _slots[i].ballEffects;
        res[i].used = _slots[i].used;
    }
    return res;
}