#include "StickRewardScene.h"

#include <iostream>

StickRewardScene::StickRewardScene(Game* game, Reward reward)
    : InstantRewardScene(game, reward, 1)
{
    #ifdef _DEBUG
        std::cout << "STICK REWARD CONSTRUCTOR" << std::endl;
    #endif
}

StickRewardScene::~StickRewardScene()
{

}

void StickRewardScene::atRender()
{
    openInventory();
}

void StickRewardScene::applyReward()
{

}

void StickRewardScene::initObjects()
{
    std::vector<RandomItem<stickID>> a_stickList = {
        {stickID::BOXING, 1.0},
        {stickID::DONUT, 1.0},
        {stickID::GRENADE, 1.0},
        {stickID::NORMAL_STICK, 1.0},
        {stickID::WAND, 1.0}
    };

    _stickReward = RNG_Manager::Instance()->getRandomItem(a_stickList);
}

void StickRewardScene::initFunctionalities() 
{
    // aqui nada
}

Texture*
StickRewardScene::idToTexture(stickID id) {

    std::string textureId;

    switch (id)
    {
    case stickID::BOXING:
        #ifdef _DEBUG
            std::cout << "FALTA LA TESTURA DEL GUANTE GUILLERMO NO SUBAS MAS LAS TARIFAS\n";
        #endif

        textureId = "palo1";
        break;
    case stickID::DONUT:
        textureId = "donut";
        break;
    case stickID::GRENADE:
        textureId = "lanzagranadas";
        break;
    case stickID::NORMAL_STICK:
        textureId = "palo1";
        break;
    case stickID::WAND:
        textureId = "magic_wand";
        break;
    default:
        textureId = "palo1";
        break;
    }

    return &sdlutils().images().at(textureId);
}