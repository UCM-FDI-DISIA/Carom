#include "RewardScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"
namespace ecs{
    
    RewardScene::RewardScene(Game *g) : UIScene(g)
    {
        createBackground("suelo");

        createTable();

        createText("¡Has GANADO!", // text
            sdlutils().width()/2, // x
            sdlutils().height()/2, // y
            3 // size.
        );

        ecs::GameScene* ms = new ecs::PoolScene(game); // se crea una nueva poolscene.
        

        entity_t b = createContinueButton(
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
        RewardScene::createContinueButton(int x, int y, ecs::GameScene *scene){
        entity_t e = new ecs::Entity(*this, grp::DEFAULT);

        b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

        addComponent<TransformComponent>(e, pos);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

        ecs::Button::TextureButton rButton = ecs::Button::TextureButton();
        addComponent<ecs::Button>(e, rButton);
  
        e->getComponent<ecs::Button>()->setOnClick([this, scene](){

            game->getScenesManager()->popScene(); // Poppea la win.
            game->getScenesManager()->pushScene(scene); // 
        });   
        
        return e;
    }
}