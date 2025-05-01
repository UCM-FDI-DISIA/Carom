#include "TextHelperScene.h"
#include "Entity.h"
#include "DialogueTextComponent.h"
#include "TransformComponent.h"
#include "WobblyRenderTextureComponent.h"
#include "RandomVibrationComponent.h"

TextHelperScene::TextHelperScene(Game* g, GameScene* bottom, std::string textToShow): HelperScene(g, bottom){
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

    auto dialogue = addComponent<DialogueTextComponent>(prueba, a, false);
    dialogue->addDialogue(textToShow);
}