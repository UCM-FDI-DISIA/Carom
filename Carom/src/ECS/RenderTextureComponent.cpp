#include "RenderTextureComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"

namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture) : RenderComponent(ent), _texture(texture), _transform(nullptr)
    {

    }

    void RenderTextureComponent::init(){
        _transform = _myEntity->getComponent<TransformComponent>();
    }

    void RenderTextureComponent::render() {
        //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
        auto [coordinateX, coordinateY] = PhysicsConverter::meter2pixel({_transform->getPosition().getX(), 
                                                                        _transform->getPosition().getY()}); 
        
        //Adapta el rect para que el objeto apareca en el centro de este
        coordinateX += _texture->width() / 2;
        coordinateY += _texture->height() / 2;

        _texture->render(coordinateX, coordinateY);
    }
} 