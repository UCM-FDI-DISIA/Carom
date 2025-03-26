#include "MainMenuScene.h"
namespace ecs{
    
    MainMenuScene::MainMenuScene(Game *g) : UIScene(g)
    {
        createBackground("suelo");

        createTable();

        createText("Carom Titulo de Ejemplo", // text
            sdlutils().width()/2, // x
            sdlutils().height()/2 - 250, // y
            4 // size.
        );

        // !!! SE CREA POOLSCENE
        NullState* state = new NullState(nullptr);
        ecs::GameScene *ms = new ecs::PoolScene(state, game, nullptr); // ! tst 

        entity_t b = createSceneButton(
            sdlutils().width()/2, // x
            (sdlutils().height()/2), // y
            ms // scene
        );

        createText("Comenzar Partida.", // text
            sdlutils().width()/2 , // x
            (sdlutils().height()/2 - 100), // y
            2 // size
        );

        // modificar luego, ahora te comienza este tambien partida.
        entity_t c = createSceneButton(
            sdlutils().width()/2, // x
            (sdlutils().height()/2) + 250, // y
            ms // scene
        );

        createText("Cargar Partida.", // text
            sdlutils().width()/2 , // x
            (sdlutils().height()/2 + 150), // y
            2 // size
        );
    }
}