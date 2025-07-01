#pragma once

#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"
#include "ecs.h"
#include "Inventory.h"


#include <memory>

class ScenesManager;
class TextDisplayComponent;
class BallInfoDisplayComponent;

class UIScene: public GameScene {
public:
    struct ButtonWithSlot {
        Button* button = nullptr;
        /// @brief el slot 0 es el palo ojo cuidao
        int slot = -1;
    };
protected:

    virtual void initObjects(){}
    virtual void initFunctionalities(){}

    void createTable(); // para que se genere la mesa.
    entity_t createText(std::string text, int x, int y, int size, SDL_Color color = {255, 255, 255, 255}, layerId_t renderlayer = renderLayer::SCORE, Uint32 wrapLength = 0, std::string font = "Basteleur-Moonlight60"); // para q salga el texto de ganar o perdr.
    entity_t createSVGImage(std::string svg, std::string tag, std::string image, 
        bool isButton = false, grp::grpId group = grp::DEFAULT, layerId_t renderlayer = renderLayer::UI);

    void createButton(int x, int y, std::string text, Texture* t, std::function<void ()> cb);

    std::array<SlotInfo, Inventory::MAX_BALLS> _ballsInfo;
    stickId_t _stickID;

    static std::string getTextureName(effectId_t effect);
    static std::string getEffectName(effectId_t effect);
    
    virtual std::vector<UIScene::ButtonWithSlot> instantiateInventory();

    // Ball info handling
    void createBallInfo();
    void createBallShadow(entity_t e);
    virtual void createHints();
    virtual void showBall(int i);
    virtual void hideBall(int i);
    virtual void scrollBallEffect(int i); //Cambia el efecto que se muestra

    std::vector<BallInfoDisplayComponent*> _ballEffectBoxes;

    // Stick info handling
    void createStickInfo();
    void showStick();
    void hideStick();



public:
    UIScene(Game *g) : GameScene(g) {} // para cuando se gana (hay reward).
    virtual ~UIScene() {};

    virtual void init() override;
};