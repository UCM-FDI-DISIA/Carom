#include "RewardScene.h"
namespace ecs{
    
    RewardScene::RewardScene(Game *g) : EndScene(g)
    {
        createBackground("suelo");
        createTable();
        createText("¡Has GANADO!");
        createExitButton();
    }
}