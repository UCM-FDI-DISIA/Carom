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
    game->setPaused(true);
}

QuitScene::~QuitScene()
{
    game->setPaused(false);
}

void 
QuitScene::render(){
   _bottomScene->render();
   GameScene::render();
} 

void 
QuitScene::initObjects() 
{
    entity_t blackScreen = createSVGImage("lose", "blackscreen", "blackscreen", false, grp::grpId::DEFAULT, renderLayer::UI_BACK);

    auto render = blackScreen->getComponent<RenderTextureComponent>();
    render->changeOpacity(0);
    auto opacity = render->getOpacity();

    TweenComponent* t = addComponent<TweenComponent>(blackScreen);
        t->easeValue(opacity, 150, 0.1, tween::LINEAR, false, [=](){
        createSVGImage("quit", "segurosalir", "segurosalir");

        //Buttons
        Button* quitButton = getComponent<Button>(createSVGImage("quit", "buttonSalir", "scoreSprite", true));
        createSVGImage("quit", "salir", "salir");

        Button* mainMenuButton = getComponent<Button>(createSVGImage("quit", "buttonMenu", "scoreSprite", true));
        createSVGImage("quit", "menu", "menu");

        Button* cancelButton = getComponent<Button>(createSVGImage("quit", "buttonCancelar", "scoreSprite", true));
        createSVGImage("quit", "cancelar", "cancelar");

        quitButton->setOnClick([=]{
            game->close();
        });

        mainMenuButton->setOnClick([=]{
            game->getScenesManager()->invokeLose();
        });

        cancelButton->setOnClick([=]{
            game->getScenesManager()->popScene();
        });
    });


}