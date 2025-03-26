#include "RewardScene.h"
    
RewardScene::RewardScene(Game *g) : EndScene(g)
{
    createBackground("suelo");
    createTable();
    createText("¡Has GANADO!");
    createExitButton();
}