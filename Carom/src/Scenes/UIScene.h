#pragma once

#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"


class ScenesManager;
class TextDisplayComponent;

class UIScene: public GameScene {
protected:
    void createTable(); // para que se genere la mesa.
    void createText(std::string text, int x, int y, int size);       // para q salga el texto de ganar o perdr.
    void createSVGText(std::string id){}
    entity_t createSVGImage(std::string svg, std::string tag, std::string image, 
        bool isButton = false, grp::grpId group = grp::DEFAULT, layerId_t renderlayer = renderLayer::UI);

public:
    UIScene(Game *g) : GameScene(g) {} // para cuando se gana (hay reward).
    virtual ~UIScene() = default;

    void setNewState(State *s);
};