#include "MainMenuScene.h"
#include "PoolScene.h"

MainMenuScene::MainMenuScene(Game *g) 
    : UIScene(g)
{
}

MainMenuScene::~MainMenuScene()
{
    /* Como es sharedptr poolscene esta mierda ya no hace falta
    
    if(isInitialized()) {
        if (!_poolScene->isInitialized()) {
            delete _poolScene;
            _poolScene = nullptr;
        }
    }
    
    */
}

void MainMenuScene::initFunctionalities()
{
    _poolScene = std::make_shared<PoolScene>(game);
}

void MainMenuScene::initObjects()
{
    createBackground("suelo");

    createTable();

    createText("Carom Titulo de Ejemplo", // text
        sdlutils().width()/2, // x
        sdlutils().height()/2 - 250, // y
        2 // size.
    );

    entity_t b = createSceneButton(
        sdlutils().width()/2, // x
        (sdlutils().height()/2), // y
        _poolScene // scene
    );

    createText("Comenzar Partida.", // text
        sdlutils().width()/2 , // x
        (sdlutils().height()/2 - 100), // y
        1 // scale
    );

    // modificar luego, ahora te comienza este tambien partida.
    entity_t c = createSceneButton(
        sdlutils().width()/2, // x
        (sdlutils().height()/2) + 250, // y
        _poolScene // scene
    );

    createText("Cargar Partida.", // text
        sdlutils().width()/2 , // x
        (sdlutils().height()/2 + 150), // y
        1 // scale
    );
}
