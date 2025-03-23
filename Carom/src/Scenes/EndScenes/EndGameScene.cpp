#include "EndGameScene.h"
namespace ecs{

    EndGameScene::EndGameScene(Game *g) : EndScene(g)
    {
        createBackground("suelo");

        createTable();

        createText("Has PERDIDO.", // text
            sdlutils().width()/2, // x
            sdlutils().height()/2, // y
            3 // size
        );

        NullState* state = new NullState(nullptr);
        ecs::GameScene *ms = new ecs::PoolScene(state, game, nullptr); // ! tst 

        entity_t b = createExitButton(
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
