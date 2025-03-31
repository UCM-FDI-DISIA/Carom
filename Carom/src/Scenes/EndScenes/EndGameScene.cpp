#include "EndGameScene.h"
namespace ecs{

    EndGameScene::EndGameScene(Game *g) : EndScene(g)
    {
        createBackground("suelo");
        createTable();
        createText("Has PERDIDO.");
        createExitButton();
    }
}
