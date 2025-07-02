#include "Inventory.h"
#include <fstream>
#include <iostream>
#include "GameScene.h"
#include <nlohmann/json.hpp>
#include "BallHandler.h"


#include "EntityGenerator.h"

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

void Inventory::loadInventoryNamed(std::string file){
    loadInventoryWithPath("../../resources/prefabs/inventoryData/" + file);
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
        _slots[i].ballEffects.clear();
        for(auto it = data[slotName]["ballEffects"].begin() ; it != data[slotName]["ballEffects"].end(); ++it)
        _slots[i].ballEffects.push_back(it.value());
    }
}

void Inventory::exportInventoryToSave(){
    nlohmann::json data;

    data["ease"] = _ease;
    data["charisma"] = _charisma;
    data["combo"] = _combo;
    data["hitEase"] = _hitEase;
    data["power"] = _power;
    data["cunning"] = _cunning;

   for(int i =0; i < MAX_BALLS; i++){
        std::string slotName = "slot_" + std::to_string(i);
        data[slotName]["used"] = _slots[i].used;
        for(auto num : _slots[i].ballEffects)
        data[slotName]["ballEffects"].push_back(num);
    }

    std::ofstream fileStream(pathToSavedInventory);
    if(fileStream.is_open()) fileStream << data.dump(3);
    fileStream.close();
}


std::vector<entity_t> 
Inventory::getEffectBalls(GameScene& scene, std::vector<b2Vec2> positions) {
    return EntityGenerator::generateInventoryBalls(scene, positions);
}



entity_t 
Inventory::getStick(GameScene& scene, b2Vec2 pos) {
    //retorna el objeto de stick en el json
    return EntityGenerator::generateInventoryStick(scene, pos);
}



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

int Inventory::getCombo(){return _combo;}
void Inventory::setCombo(int i){_combo = i;}

int Inventory::getEase(){return _ease;}
void Inventory::setEase(int i){_ease = i;}

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

std::array<SlotInfo, Inventory::MAX_BALLS> Inventory::getSlotsInfo(){
    std::array<SlotInfo, MAX_BALLS> res;
    for(int i =0; i < MAX_BALLS; i++) {
        res[i].ballEffects = _slots[i].ballEffects;
        res[i].used = _slots[i].used;
    }
    return res;
}

void Inventory::saveBalls(std::vector<entity_t> balls){
    for(auto slot : _slots){
        slot.ballEffects.clear();
        slot.used = false;
    }

    int i =0;
    for(auto ball : balls){
        _slots[i].used = true;
        _slots[i].ballEffects = ball->getComponent<BallHandler>()->getEffectsID();
        i++;
    }
}