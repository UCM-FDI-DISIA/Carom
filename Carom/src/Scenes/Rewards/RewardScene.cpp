 #include "RewardScene.h"
 #include "ScenesManager.h"
 #include "PoolScene.h"


RewardScene::RewardScene(Game* game, Reward reward) 
    : UIScene(game)
    , _reward(reward)
{
}

RewardScene::~RewardScene() {

}

void 
RewardScene::init() 
{
    RewardScene::initObjects(); // fondo comun a todas las escenas y boton continuar para salir

    initObjects();
    initFunctionalities();
    showExitButton(); // !tst
}

void 
RewardScene::initObjects() 
{
    // Background
    //
    createBackground("suelo");
    createTable();

    // Pantalla negra con alpha
    entity_t blackScreen = createSVGImage("lose", "blackscreen", "blackscreen", false, grp::grpId::DEFAULT, renderLayer::UI_BACK);
    auto render = blackScreen->getComponent<RenderTextureComponent>();
    render->changeOpacity(100);

    // Texto de descripcion de recompensa
    // 
    int txtPosX = sdlutils().width()/2;

    std::string r0, rName, rType;
    r0 = "Recompensa";
    rName = _reward.translateName(_reward.getName());
    rType = _reward.translateType(_reward.getType());

    createText(r0, txtPosX, 80, 1.5, {255, 255, 255, 255}, renderLayer::UI);
    createText(rName, txtPosX, 150, 1.5, {102, 0, 0, 255}, renderLayer::UI);
    createText(rType, txtPosX, 220, 1.5, {194, 197, 204, 255}, renderLayer::UI);

    createText(rType, txtPosX, 220, 1.5, {194, 197, 204, 255}, renderLayer::UI);

    // Boton de continuar 
    //
    _exitButton = createSVGImage("win", "scoreSprite", "scoreSprite", true);
    _exitButton->getComponent<Button>()->setOnClick([this]() { exitCallback(); });
    _exitButton->deactivate();
    // Texto del boton
    _exitBttText = createSVGImage("win", "rewardButtonText", "rewardButtonText", false);
    _exitBttText->deactivate();
}

void 
RewardScene::showExitButton() 
{
    _exitButton->activate();
    _exitBttText->activate();
}

// Applies reward y sale de reward scene
void 
RewardScene::exitCallback()
{
    applyReward();

    game->getScenesManager()->popScene(); // Poppea esta escena
    // vuelve a poolscene
    if(_reward.getType() == Reward::Type::BOSS) {
        game->getScenesManager()->popScene(); // popea poolscene
        game->getProgressionManager()->anteUp();
        game->getScenesManager()->pushScene(std::make_shared<PoolScene>(game)); // Nueva PoolScene
    }
}
