#include "RenderTextureComponent.h"

#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "Camera.h"
#include "GameScene.h"

namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderOrder, float scale) 
    : RenderComponent(ent),
    _texture(texture),
    _transform(nullptr),
    renderOrder(renderOrder),
    _scale(scale)
    {

    }

    void RenderTextureComponent::init(){
        _transform = _myEntity->getTransform();
        _myEntity->getScene().sortRenderOrder();
    }

    void RenderTextureComponent::render(Camera* camera) {
        b2Vec2 physicalPosition = _transform->getPosition();
        //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
        auto [coordinateX, coordinateY] = camera->getRenderPos({physicalPosition.x, physicalPosition.y});
        
        //Adapta el rect para que el objeto apareca en el centro de este
        coordinateX -= _scale*_texture->width() / 2;
        coordinateY -= _scale*_texture->height() / 2;

        SDL_Rect dest = {coordinateX, coordinateY, (int)(_texture->width()*_scale), (int)(_texture->height()*_scale)};
        _texture->render(dest, _transform->getRotation());
    }

    SDL_Rect RenderTextureComponent::getRect()
    {
        b2Vec2 physicalPosition = _transform->getPosition();
        //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
        auto [coordinateX, coordinateY] = _myEntity->getScene().getWorldCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
        
        //Adapta el rect para que el objeto apareca en el centro de este
        coordinateX -= _scale*_texture->width() / 2;
        coordinateY -= _scale*_texture->height() / 2;

        SDL_Rect dest = {coordinateX, coordinateY, (int)(_texture->width()*_scale), (int)(_texture->height()*_scale)};

        return dest;
    }
} 