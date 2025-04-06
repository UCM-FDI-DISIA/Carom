#include "UIScene.h"

#include "TextDisplayComponent.h"
#include "ScenesManager.h"


void UIScene::createTable()
{
    entity_t table = new Entity(*this, grp::DEFAULT);
        b2Vec2 pos(0,0);
        addComponent<TransformComponent>(table, pos);
        addComponent<RenderTextureComponent>(table, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, 1);

        table = new Entity(*this, grp::DEFAULT);
        addComponent<TransformComponent>(table, pos);
        addComponent<RenderTextureComponent>(table, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, 1);
}

void UIScene::createText(std::string text, int x, int y, int size)
{
    entity_t winContainer = new Entity(*this, grp::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);

    winContainer->addComponent(new TransformComponent(winContainer, pos));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(
        winContainer,           // container
        renderLayer::SCORE,     // capa renderizado
        size,                      // tamano fuente
        text,         // text
        {255, 255, 255, 255},   // color (blanco)
        "Basteleur-Moonlight60" // fuente
    );
    winContainer->addComponent(currentDisplay);
}

entity_t UIScene::createSceneButton(int x, int y, GameScene* scene, grpId_t g, layerId_t r, std::string tex, float size)
{
    entity_t e = new Entity(*this, g);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(tex), r, size);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    e->getComponent<Button>()->setOnClick([this, scene](){
        game->getScenesManager()->pushScene(scene);
    });   
    
    return e;
}

entity_t UIScene::createSceneButton(int x, int y, GameScene* scene)
{
    entity_t e = new Entity(*this, grp::DEFAULT);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    e->getComponent<Button>()->setOnClick([this, scene](){
        game->getScenesManager()->pushScene(scene);
    });   
    
    return e;
}
