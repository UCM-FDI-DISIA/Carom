#include "RewardScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"

// TODO: refactorizar -> recibir recompensa

RewardScene::RewardScene(Game *g, std::shared_ptr<Reward> r) : UIScene(g)
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

    
    std::string r0, rName, rType;
    r0 = "Tu recompensa es:";
    rName = r->getName();
    rType = r->getType();

    createText(
        r0, 
        midWinX, 
        sdlutils().height()/2.25, 
        1.5
    );

    createText(
        rName, 
        midWinX, 
        sdlutils().height()/2 + 25, 
        1.5,
        {102, 0, 0, 255}
    );

    createText(
        rType, 
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

    createSVGImage("win", "rewardButtonText", "rewardButtonText", false);

    // TODO añadir este metodo en el callback de los botones de la UI
    //r->applyReward();
}
