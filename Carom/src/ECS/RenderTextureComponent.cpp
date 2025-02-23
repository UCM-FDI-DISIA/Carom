#include "RenderTextureComponent.h"

#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "Camera.h"
#include "GameScene.h"

namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderOrder) 
    : RenderComponent(ent),
    _texture(texture),
    _transform(nullptr),
    renderOrder(renderOrder)
    {

    }

    void RenderTextureComponent::init(){

        // Chapucilla para que el render funcione siempre
        if (_myEntity->tryGetComponent<RigidBodyComponent>()) 
            _transform = _myEntity->getComponent<RigidBodyComponent>();
        else
            _transform = _myEntity->getComponent<TransformComponent>();

        _myEntity->getScene().sortRenderOrder();
    }

    void RenderTextureComponent::render(Camera* camera) {
        Vector2D physicalPosition = _transform->getPosition();
        //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
        auto [coordinateX, coordinateY] = camera->getRenderPos({physicalPosition.getX(), physicalPosition.getY()});
        
        //Adapta el rect para que el objeto apareca en el centro de este
        coordinateX += _texture->width() / 2;
        coordinateY += _texture->height() / 2;

        SDL_Rect dest = {coordinateX, coordinateY, _texture->width(), _texture->height()};
        _texture->render(dest, _transform->getRotation());
    }
} 