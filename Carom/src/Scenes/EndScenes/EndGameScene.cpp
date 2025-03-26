#include "EndGameScene.h"
EndGameScene::EndGameScene(Game *g) : EndScene(g)
{
    createBackground("suelo");
    createTable();
    createText("Has PERDIDO.");
    createExitButton();
}
