#include "RewardScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"

// TODO: refactorizar -> recibir recompensa

RewardScene::RewardScene(Game *g, std::shared_ptr<Reward> r) 
    : UIScene(g)
    , _isBoss(r->getType() == Reward::Type::BOSS)
{
    createBackground("suelo");

    createTable();

    // mitad de la pantalla en x.
    int midWinX = sdlutils().width()/2;

    std::string r0, rName, rType;
    r0 = "Tu recompensa es:";
    rName = r->translateName(r->getName());
    rType = r->translateType(r->getType());

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

    entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);

    // boton de concluir reward y ir a nueva pool
    b->getComponent<Button>()->setOnClick([this](){

        game->getScenesManager()->popScene(); // Poppea esta escena
        // vuelve a poolscene
        
        if(_isBoss) {
            game->getScenesManager()->popScene(); // popea poolscene
            game->getProgressionManager()->anteUp();
            game->getScenesManager()->pushScene(std::make_shared<PoolScene>(game)); // Nueva PoolScene
        }
    }); 

    createSVGImage("win", "rewardButtonText", "rewardButtonText", false);

    // TODO añadir este metodo en el callback de los botones de la UI
    // r->applyReward();
}

RewardScene::~RewardScene()
{
    std::cout << "DESTRUCTOR REWARD" << std::endl;
}
