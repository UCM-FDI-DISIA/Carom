#pragma once

#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"

#include "ItemIDs.h"

#include <memory>

class ScenesManager;
class TextDisplayComponent;
class BallInfoDisplayComponent;

class UIScene: public GameScene {
protected:

    virtual void initObjects(){}
    virtual void initFunctionalities(){}

    void createTable(); // para que se genere la mesa.
    entity_t createText(std::string text, int x, int y, int size, SDL_Color color = {255, 255, 255, 255}, layerId_t renderlayer = renderLayer::SCORE, Uint32 wrapLength = 0, std::string font = "Basteleur-Moonlight60"); // para q salga el texto de ganar o perdr.
    entity_t createSVGImage(std::string svg, std::string tag, std::string image, 
        bool isButton = false, grp::grpId group = grp::DEFAULT, layerId_t renderlayer = renderLayer::UI);

    void createButton(int x, int y, std::string text, Texture* t, std::function<void ()> cb);


    /// @brief Struct con la informacion de las bolas de cara a su uso como recompensa y su render 
    struct BallInfo{
        std::vector<BallId> effects;
        int scrollIndex = 0;
        bool free = true; // En el caso del inventario, free significa que el slot está en uso

        bool operator==(const BallInfo& other) const {
            return effects == other.effects;
        }
            bool operator!=(const BallInfo& other) const {
            return !(effects == other.effects);
        }
    };

    std::vector<BallInfo> _ballsInfo;
    StickId _stickID;

    static std::string getTextureName(BallId effect);
    static std::string getEffectName(BallId effect);
    
    virtual void instantiateInventory();

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