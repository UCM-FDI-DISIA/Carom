#include "TutorialScene.h"

#include "TransformComponent.h"
#include "WobblyRenderTextureComponent.h"
#include "RandomVibrationComponent.h"
#include "DialogueTextComponent.h"

TutorialScene::TutorialScene(Game* game, GameScene* sceneToRenderOnTop) : GameScene(game), _bottomScene(sceneToRenderOnTop){
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
    dialogue->addDialogue("Mami");
    dialogue->addDialogue("a mi me gusta tu descendencia entera");
    dialogue->addDialogue("(pol que)");
    dialogue->addDialogue("polque ella me hace");
    dialogue->addDialogue("l");
}

void TutorialScene::render(){
    _bottomScene->render();
    GameScene::render();
}