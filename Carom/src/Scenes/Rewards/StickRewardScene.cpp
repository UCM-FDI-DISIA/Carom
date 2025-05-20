#include "StickRewardScene.h"
#include "InventoryManager.h"
#include "TextDisplayComponent.h"

#include "AudioManager.h"

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
    hideExitButton();

    std::vector<ButtonWithSlot> a_buttonVector = openInventory();

    for (ButtonWithSlot& e : a_buttonVector) {
        if (e.slot == 0) { // asi es, magic number // bravo
            if (e.button != nullptr) {
                _oldStickTextureComponent = e.button->getEntity()->getComponent<RenderTextureComponent>();
                e.button->setOnClick([this]() {
                    selectItem(0);
                    if (!_invSelected){ 
                        _invSelected = true;
                        _newSelected = false;
                        _oldStickTextureComponent->resetColorTint();
                        _newStickTextureComponent->changeColorTint(64, 64, 64);
                        AudioManager::Instance()->playSoundEfect("pick");
                    }
                    else {
                        _invSelected = false;
                        _oldStickTextureComponent->changeColorTint(64, 64, 64);
                        AudioManager::Instance()->playSoundEfect("unpick");
                    }

                    toggleExitButton();
                });
            }
        }
    }

    _oldStickTextureComponent->changeColorTint(64, 64, 64);
    _newStickTextureComponent->changeColorTint(64, 64, 64);
}

void StickRewardScene::initObjects()
{
    moveExitButtonToRight();

    std::vector<RandomItem<StickId>> a_stickList = std::vector<RandomItem<StickId>>();

    getStickId();

    for(int i = 0; i < StickId::NUM_STICKS; ++i){
        if(StickId (i) != _stickID) a_stickList.push_back({StickId (i), 1.0});
    }

    _stickReward = RNG_Manager::Instance()->getRandomItem(a_stickList);

    entity_t nuevo_palo = new Entity(*this, grp::UI);

    auto a_stick = sdlutils().svgs().at("reward").at("newStick");

    b2Vec2 a_pos = PhysicsConverter::pixel2meter(
        a_stick.x,
        a_stick.y
    );

    Texture* a_stickTexture = idToTexture(_stickReward);


    float a_stickScale = float(a_stickTexture->width()) / float(a_stick.width);
    a_stickScale*= 0.5; // se generaba muy grande

    TransformComponent* a_tr = addComponent<TransformComponent>(nuevo_palo, a_pos);
    a_tr->setRotation(90.0);
    _newStickTextureComponent = addComponent<RenderTextureComponent>(nuevo_palo, a_stickTexture, renderLayer::UI, a_stickScale);

    Button::TextureButton rButton = Button::TextureButton(true);
    auto button = addComponent<Button>(nuevo_palo, rButton);

    button->setOnClick([this]() {
        if (!_newSelected) {
             // Si el palo del inventario está seleccionado, lo deseleccionamos
            if (_invSelected) {
                selectItem(0);
                _invSelected = false;
            } 
            _newSelected = true;
            showExitButton();
            _oldStickTextureComponent->changeColorTint(64, 64, 64);
            _newStickTextureComponent->resetColorTint();
            AudioManager::Instance()->playSoundEfect("pick");
        }
        else {
            _newSelected = false;
            hideExitButton();
            toggleExitButton();
            _newStickTextureComponent->changeColorTint(64, 64, 64);
            AudioManager::Instance()->playSoundEfect("unpick");
        }
    });

    // Texto de ayuda
    entity_t help_text = new Entity(*this, grp::UI);

    a_pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("reward").at("textArea_right").x,
        *&sdlutils().svgs().at("reward").at("textArea_right").y
    );

    a_tr = addComponent<TransformComponent>(help_text, a_pos);

    TextDisplayComponent* a_textDisplay = new TextDisplayComponent(help_text, renderLayer::UI, 1.0, 
        "Elige entre este palo o el del inventario", {255, 255, 255, 255}, "Aladin-Regular48");
    help_text->addComponent(a_textDisplay);    
}

void StickRewardScene::applyReward()
{
    if (_newSelected) InventoryManager::Instance()->addStick(_stickReward);
}

Texture*
StickRewardScene::idToTexture(StickId id) {

    std::string textureId;

    switch (id)
    {
    case BOXING:
        textureId = "boxing";
        break;
    case DONUT:
        textureId = "donut";
        break;
    case GRENADE:
        textureId = "lanzagranadas";
        break;
    case NORMAL_STICK:
        textureId = "palo1";
        break;
    case WAND:
        textureId = "magic_wand";
        break;
    default:
        textureId = "palo1";
        break;
    }

    return &sdlutils().images().at(textureId);
}