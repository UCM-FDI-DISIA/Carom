#include "MainMenuScene.h"
namespace ecs{
    
    MainMenuScene::MainMenuScene(State* s, Game *g) : UIScene(g)
    {
        createBackground("suelo");

        createTable();

        createText("Carom Titulo de Ejemplo", // text
            sdlutils().width()/2, // x
            sdlutils().height()/2, // y
            4 // size.
        );

        NullState* state = new NullState(nullptr);
        ecs::GameScene *ms = new ecs::PoolScene(state, game, nullptr); // ! tst 

        entity_t b = createSceneButton(
            sdlutils().width()/2, // x
            (sdlutils().height()/2) + 250, // y
            ms // scene
        );

        createText("Comenzar Partida.", // text
            sdlutils().width()/2 , // x
            (sdlutils().height()/2 + 150), // y
            2 // size
        );
    }
}