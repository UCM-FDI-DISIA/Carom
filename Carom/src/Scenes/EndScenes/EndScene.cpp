#include "EndScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "CaromScene.h"
#include "CowboyPoolScene.h"
#include "PoolScene.h"
#include "TextDisplayComponent.h"
//#include "ScoreContainer.h"
//#include "StickInputComponent.h"

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>

namespace ecs{
    
    void EndScene::createTable()
    {
        entity_t table = new ecs::Entity(*this, grp::DEFAULT);
            b2Vec2 pos(0,0);
            addComponent<TransformComponent>(table, pos);
            addComponent<RenderTextureComponent>(table, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, 1);
    
            table = new ecs::Entity(*this, grp::DEFAULT);
            addComponent<TransformComponent>(table, pos);
            addComponent<RenderTextureComponent>(table, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, 1);
    }
    
    void EndScene::createText(std::string text)
    {
        entity_t winContainer = new Entity(*this, ecs::grp::SCORE);
        _entsRenderable.push_back(winContainer);

        b2Vec2 pos = PhysicsConverter::pixel2meter(
            sdlutils().width()/2,
            sdlutils().height()/2
        );

        winContainer->addComponent(new TransformComponent(winContainer, pos));
        TextDisplayComponent* currentDisplay = new TextDisplayComponent(
            winContainer,           // container
            renderLayer::SCORE,     // capa renderizado
            3,                      // tamano fuente
            text,         // text
            {255, 255, 255, 255},   // color (blanco)
            "Basteleur-Moonlight24" // fuente
        );
        winContainer->addComponent(currentDisplay);
    }
    
    void EndScene::createExitButton()
    {
        entity_t e = new ecs::Entity(*this, grp::DEFAULT);

        b2Vec2 pos = PhysicsConverter::pixel2meter(
            sdlutils().width()/2,
            (sdlutils().height()/2) + 250
        );    

        addComponent<TransformComponent>(e, pos);
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

        ecs::Button::TextureButton rButton = ecs::Button::TextureButton();
        addComponent<ecs::Button>(e, rButton);
  
        // Para cuando este la MainMenu scene, habria que ponerla aqui.
        e->getComponent<ecs::Button>()->setOnClick([this](){
            std::cout << "Carga escena PoolScene" << std::endl;
            NullState* state = new NullState(nullptr);
            ecs::PoolScene *ms = new ecs::PoolScene(state, game, nullptr); // ! tst  
            game->getScenesManager()->pushScene(ms);
        });          
    }
}
