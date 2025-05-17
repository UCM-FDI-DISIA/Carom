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
    std::vector<ButtonWithSlot> a_buttonVector = openInventory();

    for (ButtonWithSlot& e : a_buttonVector) {
        if (e.slot == 0) { // asi es, magic number
            if (e.button != nullptr) {
                e.button->setOnClick([this]() {
                    selectItem(0);
                    if (!_invSelected){ 
                        _invSelected = true;
                        _newSelected = false;
                    }
                    else {
                        _invSelected = false;
                    }
                });
            }
        }
    }
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

    entity_t nuevo_palo = new Entity(*this, grp::UI);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("reward").at("newStick").x,
        *&sdlutils().svgs().at("reward").at("newStick").y
    );

    Texture* a_stickTexture = idToTexture(_stickReward);

    float a_stickScale = float(sdlutils().svgs().at("reward").at("newStick").width) / float(a_stickTexture->width());

    TransformComponent* a_tr = addComponent<TransformComponent>(nuevo_palo, pos);
    a_tr->setRotation(90.0);
    addComponent<RenderTextureComponent>(nuevo_palo, a_stickTexture, renderLayer::UI, a_stickScale);

    Button::TextureButton rButton = Button::TextureButton();
    auto button = addComponent<Button>(nuevo_palo, rButton);

    button->setOnClick([this]() {
        if (!_newSelected) {
            if (_invSelected) selectItem(0);
            _newSelected = true;
            showExitButton();
        }
        else {
            _newSelected = false;
            hideExitButton();
        }
    });
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