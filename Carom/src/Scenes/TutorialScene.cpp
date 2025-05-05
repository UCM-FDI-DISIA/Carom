#include "TutorialScene.h"

#include "TransformComponent.h"
#include "WobblyRenderTextureComponent.h"
#include "RandomVibrationComponent.h"
#include "DialogueTextComponent.h"
#include "ScenesManager.h"
#include "CaromScene.h"
#include "NullState.h"
#include "RussianPyramidScene.h"
#include "InventoryManager.h"
#include "TutorialOneStartMatchState.h"
#include "TextHelperScene.h"

TutorialScene::TutorialScene(Game* game, GameScene* sceneToRenderOnTop) : GameScene(game), _bottomScene(sceneToRenderOnTop){

    InventoryManager::Instance()->loadStartingInventory();

    //!tst borrar
    Entity* prueba = new Entity(*this, grp::UI);

    addComponent<TransformComponent>(prueba, b2Vec2{0.f,0.f});
    auto a = addComponent<WobblyRenderTextureComponent>(prueba,           // container
        renderLayer::UI,     // capa renderizado
        1.f,                   // tamano fuente
        " ",                   // text
        SDL_Color{255, 255, 255, 255},   // color (blanco)
        "Basteleur-Moonlight60" // fuente
    );

    addComponent<RandomVibrationComponent>(prueba, .05f, 5);

    auto dialogue = addComponent<DialogueTextComponent>(prueba, a);
    dialogue->addDialogue("Hola");
    dialogue->addDialogue("Veo que has despertado");
    dialogue->addDialogue("¿sabes cuánto tiempo llevas inconsciente?");
    dialogue->addDialogue("207 años");
    dialogue->addDialogue("Te hemos estado esperando durante todo este tiempo");
    dialogue->addDialogue("y por fin estás aquí");
    dialogue->addDialogue("Primero lo importante: ¿sabes jugar?", [=](){

        auto caromOne = new CaromScene(game);
        auto a = std::shared_ptr<CaromScene>(caromOne);
        a.get()->setNewState(new TutorialOneStartMatchState(a.get()));

        game->getScenesManager()->pushScene(a);

        game->getScenesManager()->pushScene(std::shared_ptr<TextHelperScene>(new TextHelperScene(game, a, "Golpeas arrastrando el ratón")));
    });

    dialogue->addDialogue("Veo que sí que te acuerdas...");
    dialogue->addDialogue("Perfecto");
    dialogue->addDialogue("Ahora, veamos si puedes hacer algún truco");
    
}

void TutorialScene::render(){
    _bottomScene->render();
    GameScene::render();
}