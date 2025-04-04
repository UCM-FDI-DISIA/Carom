#pragma once

#include "Entity.h"
#include "ShadowComponent.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "FollowComponent.h"
#include "GameScene.h"
#include "SDLUtils.h"

void ShadowComponent::addShadow(b2Vec2 displacement, std::string imageName, int renderLayer, float scale, bool copyPosition, bool copyRotation, bool copyScale) {
    Entity* e = new Entity(_myEntity->getScene(), grp::SHADOWS);

    TransformComponent* t = new TransformComponent(e, displacement);
    e->addComponent<TransformComponent>(t);

    RenderTextureComponent* r = new RenderTextureComponent(e, &sdlutils().images().at(imageName), renderLayer, scale);
    e->addComponent<RenderTextureComponent>(r);

    FollowComponent* f = new FollowComponent(e, _myEntity, copyPosition, copyRotation, copyScale, Vector2D{displacement.x, displacement.y});
    e->addComponent<FollowComponent>(f);

    _shadows.push_back(e);
}