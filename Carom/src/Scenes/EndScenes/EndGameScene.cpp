#include "EndGameScene.h"
#include "ScenesManager.h"


EndGameScene::EndGameScene(Game *g, bool win)
    : UIScene(g)
    , _win(win)
{
}

void EndGameScene::initObjects()
{
    createBackground("suelo");

    createTable();

    if (_win)
        hasWon();
    else
        hasLost();
}

void EndGameScene::hasWon()
{
    // mitad de la pantalla en x.
    int midWinX = sdlutils().width()/2;

    createText("¡Has GANADO!", // text
        midWinX, // x
        sdlutils().height()/3, // y
        2 // size.
    );
    
    entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);

    // Vuelve a reward
    b->getComponent<Button>()->setOnClick([this]()
    {
        game->getScenesManager()->popScene(); // Poppea esta escena
        // va a reward scene
    }); 
}

void EndGameScene::hasLost()
{
    createSVGImage("lose", "losetext", "citacionlose1");

    entity_t blackScreen = createSVGImage("lose", "blackscreen", "blackscreen", false, grp::grpId::DEFAULT, renderLayer::UI_BACK);

    auto render = blackScreen->getComponent<RenderTextureComponent>();
    render->changeOpacity(0);
    auto opacity = render->getOpacity();

    TweenComponent* t = addComponent<TweenComponent>(blackScreen);
    t->easeValue(opacity, 255, 4, tween::LINEAR, false, [=](){
        entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);
        createSVGImage("lose", "loseButtonText", "loseButtonText");
        // Vuelve a main scene
        b->getComponent<Button>()->setOnClick([this]()
        {
            game->getScenesManager()->invokeLose(); // vuelve a main scene
        }); 
    });

}