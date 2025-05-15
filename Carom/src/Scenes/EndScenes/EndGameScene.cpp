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
    createText("Has PERDIDO.", // text
    sdlutils().width()/2, // x
    sdlutils().height()/2, // y
    2.5 // size
    );

    entity_t b = createSVGImage("lose", "scoreSprite", "scoreSprite", true);

    // Vuelve a main scene
    b->getComponent<Button>()->setOnClick([this]()
    {
        game->getScenesManager()->invokeLose(); // vuelve a main scene
    }); 

    createSVGImage("lose", "loseButtonText", "loseButtonText");
}