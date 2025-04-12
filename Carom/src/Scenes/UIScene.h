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
    entity_t createSceneButton(int x, int y, GameScene *scene, grpId_t g, layerId_t r, std::string tex, float size);
    entity_t createSceneButton(int x, int y, GameScene *scene); // crea el boton de cambio de escena.

public:
    UIScene(Game *g) : GameScene(g) {} // para cuando se gana (hay reward).
    virtual ~UIScene() = default;

    void setNewState(State *s);
};