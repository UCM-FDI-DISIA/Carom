#include "InventoryManager.h"
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
    //retorna el objeto de stick en el json
    return JsonEntityParser::createStick(scene, pathToInventory, "stick");
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
    updateData(data);
}

void
InventoryManager::addStick(entity_t stick) {
    //! TO DO
    removeStick();

    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    //GUARDAR NUEVO STICK
    auto stickInput = stick->getComponent<StickInputComponent>();
    assert(stickInput != nullptr);
    auto stickEffect = stickInput->getStickEffect();

    if(dynamic_cast<DonutStickEffect*>(stickEffect) != nullptr){
        data["stick"]["components"][0]["componentName"] = "DonutStickEffect";
    }
    else if(dynamic_cast<MagicWandStickEffect*>(stickEffect) != nullptr){
        data["stick"]["components"][0]["componentName"] = "MagicWandStickEffect";
    }
    else if(dynamic_cast<BoxingGloveStickEffect*>(stickEffect) != nullptr){
        auto boxing = dynamic_cast<BoxingGloveStickEffect*>(stickEffect);
        data["stick"]["components"][0]["componentName"] = "BoxingGloveStickEffect";
        data["stick"]["components"][0]["atributes"]["factor"] = boxing->_factor;
    }
    else if(dynamic_cast<GranadeLauncherStickEffect*>(stickEffect) != nullptr){
        auto granade = dynamic_cast<GranadeLauncherStickEffect*>(stickEffect);
        data["stick"]["components"][0]["componentName"] = "GrenadeLauncherStickEffect";
        data["stick"]["components"][0]["atributes"]["explosionDelay"] = granade->_explosionDelay;
        data["stick"]["components"][0]["atributes"]["explosionForce"] = granade->_explosionForce;
        data["stick"]["components"][0]["atributes"]["radius"] = granade->_radius;
    }

    updateData(data);
}

void 
InventoryManager::swapBall(entity_t newBall, int indexOfOldBall) {
    
    assert(indexOfOldBall >= 0 && indexOfOldBall < MAX_BALLS);
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    data["slot" + std::to_string(indexOfOldBall)]["components"][0]["atributes"]["effects"] = JsonEntityParser::getBallEffects(newBall);

    //update data
    updateData(data);
}

void
InventoryManager::removeBall(int index) {
    
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    data.erase("slot" + std::to_string(index));

    //update data
    updateData(data);
}

void InventoryManager::removeAllBalls() {
    
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    for(int i =0; i < MAX_BALLS; i++){
        data.erase("slot" + std::to_string(i));
    }

    //update data
    updateData(data);
}

void InventoryManager::removeStick() {
    //! TO DO
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    //vacia components
    data["stick"]["components"] = std::vector<int>();

    //update data
    updateData(data);
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
    updateData(data);
}

void InventoryManager::updateData(json data){
    std::ofstream fileStream(pathToInventory);
    if(fileStream.is_open()) fileStream << data.dump(3);
    fileStream.close();
}

//------------------------------------- P E R M A ----------------------------------------

int InventoryManager::getHitEase(){ return getParameterValue("hitEase");}
void InventoryManager::setHitEase(int i){setParameterValue("hitEase", i);}

int InventoryManager::getComboEase(){return getParameterValue("comboEase");}
void InventoryManager::setComboEase(int i){setParameterValue("comboEase", i);}

int InventoryManager::getCaromEase(){return getParameterValue("caromEase");}
void InventoryManager::setCaromEase(int i){setParameterValue("caromEase", i);}

int InventoryManager::getCharisma(){return getParameterValue("charisma");}
void InventoryManager::setCharisma(int i){setParameterValue("charisma", i);}

int InventoryManager::getPower(){return getParameterValue("power");}
void InventoryManager::setPower(int i){setParameterValue("power", i);}

float InventoryManager::getCunning(){
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    return data["cunning"];
}

void InventoryManager::setCunning(float f){
    std::ifstream fs(pathToInventory);
    json data = json::parse(fs);

    data["cunning"] = f;

    updateData(data);
}

int InventoryManager::getParameterValue(std::string key){
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    return data[key];
}

void InventoryManager::setParameterValue(std::string key, int value){
    std::ifstream f(pathToInventory);
    json data = json::parse(f);

    data[key] = value;

    updateData(data);
}