#include "EndGameScene.h"
#include "ScenesManager.h"


EndGameScene::EndGameScene(Game *g) : UIScene(g)
{
    createBackground("suelo");

    createTable();

    createText("Has PERDIDO.", // text
        sdlutils().width()/2, // x
        sdlutils().height()/2, // y
        3 // size
    );

    // Para cuando este la MainMenu scene, habria que ponerla aqui.
    GameScene *ms = new MainMenuScene(game); // ! tst 

    entity_t b = createSVGImage("lose", "scoreSprite", "scoreSprite", true);

    b->getComponent<Button>()->setOnClick([this, ms](){

        game->getScenesManager()->popScene(); // Poppea la loose.
        game->getScenesManager()->popScene(); // Poppea la carom.
        game->getScenesManager()->popScene(); // Poppea la pool.
        game->getScenesManager()->popScene(); // Poppea la mainMenuScene.
        game->getScenesManager()->pushScene(ms);
    }); 

    createText("Terminar.", // text
        sdlutils().width()/2 , // x
        (sdlutils().height()/2 + 150), // y
        2 // size
    );
}
