#include "RewardScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"

// TODO: refactorizar -> recibir recompensa

RewardScene::RewardScene(Game *g) : UIScene(g)
{
    createBackground("suelo");

    createTable();

    // mitad de la pantalla en x.
    int midWinX = sdlutils().width()/2;

    createText("¡Has GANADO!", // text
        midWinX, // x
        sdlutils().height()/3, // y
        2 // size.
    );

    
    std::string r0, r1, r2;
    r0 = "Tu recompensa es:";
    r1 = "Recompensa";
    r2 = "Tipo";

    createText(
        r0, 
        midWinX, 
        sdlutils().height()/2.25, 
        1.5
    );

    createText(
        r1, 
        midWinX, 
        sdlutils().height()/2 + 25, 
        1.5,
        {102, 0, 0, 255}
    );

    createText(
        r2, 
        midWinX, 
        sdlutils().height()/2 + 115, 
        1.5,
        {194, 197, 204, 255}
    );



    std::shared_ptr<GameScene> ms = std::make_shared<PoolScene>(game); // se crea una nueva poolscene.

    entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);

    b->getComponent<Button>()->setOnClick([this](){

        game->getScenesManager()->popScene(); // Poppea la win.
    }); 

    createSVGImage("win", "rewardButtonText", "rewardButtonText");
}
