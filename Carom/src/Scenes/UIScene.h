#pragma once

#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"

#include <memory>

class ScenesManager;
class TextDisplayComponent;

class UIScene: public GameScene {
protected:
    virtual void initObjects(){}
    virtual void initFunctionalities(){}

    void createTable(); // para que se genere la mesa.
    void createText(std::string text, int x, int y, int size, SDL_Color color = {255, 255, 255, 255}, layerId_t renderlayer = renderLayer::SCORE); // para q salga el texto de ganar o perdr.
    entity_t createSVGImage(std::string svg, std::string tag, std::string image, 
        bool isButton = false, grp::grpId group = grp::DEFAULT, layerId_t renderlayer = renderLayer::UI);

    void createButton(int x, int y, std::string text, Texture* t, std::function<void ()> cb);

public:
    UIScene(Game *g) : GameScene(g) {} // para cuando se gana (hay reward).
    virtual ~UIScene() {};

    virtual void init() override;
};