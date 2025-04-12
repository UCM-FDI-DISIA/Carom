#include "RewardScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"

// TODO: refactorizar -> recibir recompensa

RewardScene::RewardScene(Game *g) : UIScene(g)
{
    createBackground("suelo");

    createTable();

    createText("¡Has GANADO!", // text
        sdlutils().width()/2, // x
        sdlutils().height()/2, // y
        3 // size.
    );

    GameScene* ms = new PoolScene(game); // se crea una nueva poolscene.

    entity_t b = createSVGSceneButton("win", "scoreSprite", "scoreSprite");

    b->getComponent<Button>()->setOnClick([this, ms](){

        game->getScenesManager()->popScene(); // Poppea la win.
        game->getScenesManager()->pushScene(ms);
    }); 

    createText("Terminar.", // text
        sdlutils().width()/2 , // x
        (sdlutils().height()/2 + 150), // y
        2 // size
    );
}
