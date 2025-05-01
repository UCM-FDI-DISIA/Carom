#pragma once
#include "GameScene.h"
#include "Game.h"

#include <memory>

class PauseScene: public GameScene{
    //escena sobre la que renderizar
    GameScene* _bottomScene;

    enum ballID{
        NORMAL,
        CRISTAL,
        BOWLING,
        POKEBALL,
        X2,
        ABBACUS,
        QUANTIC,
        PETANQUE
    };

    std::vector<ballID> _ballIDs;

    void instantiateInventory();
    void createBallInfo();
    void showBall(int i);
    void hideBall(int i);
public:

    PauseScene(Game* game, GameScene* sceneToRenderOnTop);

    void render() override;

    void createBallShadow(entity_t e);
};