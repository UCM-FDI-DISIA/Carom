#include "EndGameScene.h"
#include "ScenesManager.h"
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
        ecs::GameScene *ms = new ecs::MainMenuScene(game); // ! tst 

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

    entity_t 
    EndGameScene::createExitButton(int x, int y, ecs::GameScene *scene){
        entity_t e = new ecs::Entity(*this, grp::DEFAULT);

        b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

        addComponent<TransformComponent>(e, pos);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

        ecs::Button::TextureButton rButton = ecs::Button::TextureButton();
        addComponent<ecs::Button>(e, rButton);
  
        e->getComponent<ecs::Button>()->setOnClick([this, scene](){

            game->getScenesManager()->popScene(); // Poppea la loose.
            game->getScenesManager()->popScene(); // Poppea la carom.
            game->getScenesManager()->popScene(); // Poppea la pool.
            game->getScenesManager()->popScene(); // Poppea la mainMenuScene.
            game->getScenesManager()->pushScene(scene);
        });   
        
        return e;
    }

    
}
