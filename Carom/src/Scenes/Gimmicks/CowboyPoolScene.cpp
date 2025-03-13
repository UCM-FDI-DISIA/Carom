#include "CowboyPoolScene.h"
#include "Entity.h"
#include "ecs.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"

namespace ecs{
    void CowboyPoolScene::initGimmick(){
        //comportamiento (anyadir entidades de arena en la mesa)
        std::cout<< "CowboyPool Gimmick Instantiated" << std::endl;
    }

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward): CaromScene(state, g, reward){
        initGimmick();
    }
}

