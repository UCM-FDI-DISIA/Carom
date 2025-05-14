#pragma once
#include "GameScene.h"
#include "Game.h"

#include <memory>

class PauseScene: public GameScene{
    //escena sobre la que renderizar
    GameScene* _bottomScene;

    enum ballID{
        NORMAL_BALL,
        CRISTAL,
        BOWLING,
        POKEBALL,
        X2,
        ABBACUS,
        QUANTIC,
        PETANQUE
    };

    enum stickID{
        NORMAL_STICK,
        GRENADE,
        DONUT,
        BOXING,
        WAND
    };

    std::vector<ballID> _ballIDs;
    stickID _stickID;
    int previousTheme;
    
    void instantiateInventory();

    // Ball info handling
    void createBallInfo();
    void showBall(int i);
    void hideBall(int i);

    // Stick info handling
    void createStickInfo();
    void showStick();
    void hideStick();
public:

    PauseScene(Game* game, GameScene* sceneToRenderOnTop);
    virtual ~PauseScene();

    void render() override;

    void createBallShadow(entity_t e);
};