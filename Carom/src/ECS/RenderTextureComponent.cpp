#include "RenderTextureComponent.h"
#include "Texture.h"

#include "Entity.h"
#include "TransformComponent.h"

namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Entity* e, Texture* texture) : RenderComponent(e), _texture(texture), _transform(nullptr)
    {
        init(_e);
    }

    void RenderTextureComponent::init(Entity* entity){
        // std::cout << "aqui1" << entity->isAlive();
        _transform = entity->getComponent<TransformComponent>();
    }

    void RenderTextureComponent::render(Entity* entity) {
        // _texture->render(_transform->getPosition()->getX(), _transform->getPosition()->getY());
        // SDL_Rect dest = build_sdlrect(_transform->getPosition(), _transform->getWidth(), _transform->getHeight());
        // _texture->render(dest, _transform->getRotation());
        Vector2D vec2d = {20, 20}; 
        SDL_Rect dest = build_sdlrect(vec2d, 50, 50);
        _texture->render(dest, 0);
        std::cout << "aqui: " << _texture->height() << std::endl;
    }
}