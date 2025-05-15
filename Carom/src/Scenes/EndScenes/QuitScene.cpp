#include "QuitScene.h"

#include "Button.h"
#include "ScenesManager.h"
#include "Game.h"
#include "TextDisplayComponent.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "SDLUtils.h"
#include "ecs.h"
#include <SDL.h>

QuitScene::QuitScene(Game* game, std::shared_ptr<GameScene> sceneToRenderBelow) : UIScene(game), _bottomScene(sceneToRenderBelow) 
{
    initObjects();
}

QuitScene::~QuitScene(){}

void 
QuitScene::render(){
   _bottomScene->render();
   GameScene::render();
} 

void 
QuitScene::initObjects() {
    //Text
    createTextObject("¿Seguro que quieres salir?", "quit", "quitText");

    //Buttons
    Button* quitButton = getComponent<Button>(createSVGImage("quit", "button1", "scoreSprite", true));
    createTextObject("Salir", "quit", "text1");

    Button* mainMenuButton = getComponent<Button>(createSVGImage("quit", "button2", "scoreSprite", true));
    createTextObject("Menu", "quit", "text1");

    Button* cancelButton = getComponent<Button>(createSVGImage("quit", "button3", "scoreSprite", true));
    createTextObject("Cancelar", "quit", "text1");

    quitButton->setOnClick([=]{
        game->close();
    });

    mainMenuButton->setOnClick([=]{
        game->getScenesManager()->invokeLose();
    });

    cancelButton->setOnClick([=]{
        game->getScenesManager()->popScene();
    });
}

void 
QuitScene::createTextObject(std::string text, std::string svg, std::string key) {
   entity_t textEntity = new Entity(*this, grp::UI); 
   auto map = sdlutils().svgs().at(svg);
   b2Vec2 pos = {PhysicsConverter::pixel2meter(map.at(key).x), PhysicsConverter::pixel2meter(map.at(key).y )};
   addComponent<TransformComponent>(textEntity, pos);

   addComponent<TextDisplayComponent>(
    textEntity, 
    layerId_t(renderLayer::UI),
    float(sdlutils().svgs().at(svg).at(key).width),
    std::string(text),
    SDL_Color(255, 255, 255, 255),
    std::string("Basteleur-Moonlight60")
   );

   _entities.push_back(textEntity);
}