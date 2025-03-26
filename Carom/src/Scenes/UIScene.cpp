#include "UIScene.h"

#include "TextDisplayComponent.h"
#include "ScenesManager.h"

namespace ecs{
    
    void UIScene::createTable()
    {
        entity_t table = new ecs::Entity(*this, grp::DEFAULT);
            b2Vec2 pos(0,0);
            addComponent<TransformComponent>(table, pos);
            addComponent<RenderTextureComponent>(table, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, 1);
    
            table = new ecs::Entity(*this, grp::DEFAULT);
            addComponent<TransformComponent>(table, pos);
            addComponent<RenderTextureComponent>(table, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, 1);
    }
    
    void UIScene::createText(std::string text, int x, int y, int size)
    {
        entity_t winContainer = new Entity(*this, ecs::grp::SCORE);
        _entsRenderable.push_back(winContainer);

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
    
    entity_t UIScene::createSceneButton(int x, int y, ecs::GameScene* scene)
    {
        entity_t e = new ecs::Entity(*this, grp::DEFAULT);

        b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

        addComponent<TransformComponent>(e, pos);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

        ecs::Button::TextureButton rButton = ecs::Button::TextureButton();
        addComponent<ecs::Button>(e, rButton);
  
        e->getComponent<ecs::Button>()->setOnClick([this, scene](){
            game->getScenesManager()->pushScene(scene);
        });   
        
        return e;
    }
}
