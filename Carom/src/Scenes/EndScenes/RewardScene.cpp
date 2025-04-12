#include "RewardScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"

    
RewardScene::RewardScene(Game *g) : UIScene(g)
{
    createBackground("suelo");

    createTable();

    createText("¡Has GANADO!", // text
        sdlutils().width()/2, // x
        sdlutils().height()/2, // y
        3 // size.
    );

    GameScene* ms = new PoolScene(game); // se crea una nueva poolscene.
    

    entity_t b = createSVGContinueButton("scoreSprite", "scoreSprite", ms);

    createText("Terminar.", // text
        sdlutils().width()/2 , // x
        (sdlutils().height()/2 + 150), // y
        2 // size
    );
}

entity_t 
    RewardScene::createContinueButton(int x, int y, GameScene *scene){
    entity_t e = new Entity(*this, grp::DEFAULT);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    e->getComponent<Button>()->setOnClick([this, scene](){

        game->getScenesManager()->popScene(); // Poppea la win.
        game->getScenesManager()->pushScene(scene); // 
    });   
    
    return e;
}

entity_t RewardScene::createSVGContinueButton(std::string tag, std::string image, GameScene *scene)
{
    // agujero.
    entity_t e = new Entity(*this, grp::DEFAULT);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("win").at(tag).x + 145, // mirar lo de +145 y +160 pq tiene q hacerse si en svg esta colocao??
        *&sdlutils().svgs().at("win").at(tag).y + 160
    );

    float scale = float(sdlutils().svgs().at("win").at(tag).width) / float(sdlutils().images().at(image).width());

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(image), renderLayer::UI, scale);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    e->getComponent<Button>()->setOnClick([this, scene](){

        game->getScenesManager()->popScene(); // Poppea la win.
        game->getScenesManager()->pushScene(scene);
    }); 

    return e;
}
