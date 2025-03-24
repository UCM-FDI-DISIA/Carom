#include "EndGameScene.h"
namespace ecs{

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
        NullState* state = new NullState(nullptr);
        ecs::GameScene *ms = new ecs::PoolScene(state, game, nullptr); // ! tst 

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
