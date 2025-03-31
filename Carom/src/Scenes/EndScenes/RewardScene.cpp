#include "RewardScene.h"
#include "PoolScene.h"
namespace ecs{
    
    RewardScene::RewardScene(Game *g) : UIScene(g)
    {
        createBackground("suelo");

        createTable();

        createText("¡Has GANADO!", // text
            sdlutils().width()/2, // x
            sdlutils().height()/2, // y
            3 // size.
        );

        ecs::GameScene* ms = new ecs::PoolScene(game); // se crea una nueva poolscene.
        

        entity_t b = createSceneButton(
            sdlutils().width()/2, // x
            (sdlutils().height()/2) + 250, // y
            ms // scene
        );

        createText("Terminar.", // text
            sdlutils().width()/2 , // x
            (sdlutils().height()/2 + 150), // y
            2 // size
        );
    }
}