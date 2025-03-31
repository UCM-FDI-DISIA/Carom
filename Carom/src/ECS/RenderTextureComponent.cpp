#include "RenderTextureComponent.h"

#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "CameraComponent.h"
#include "GameScene.h"


namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderLayer, float scale) 
    : RenderComponent(ent),
    _texture(texture),
    _transform(nullptr),
    _renderLayer(renderLayer),
    _defaultRenderLayer(renderLayer),
    _scale(scale)
    {

    }

    RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderLayer, float scale, SDL_Color tint) 
    : RenderTextureComponent(ent, texture, renderLayer, scale)
    {
        changeColorTint(tint.r, tint.g, tint.b);
    }

    void RenderTextureComponent::init(){
        _transform = _myEntity->getTransform();
        _myEntity->getScene().sortRenderOrder();
    }

    void RenderTextureComponent::render() {
        _texture->changeColorTint(_color.r, _color.g, _color.b);
        _texture->render(getRect(), _transform->getRotation());
        _texture->changeColorTint(255,255,255);
    }

    SDL_Rect RenderTextureComponent::getRect() const
    {
        b2Vec2 physicalPosition = _transform->getPosition();
        //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
        auto [coordinateX, coordinateY] = _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
        
        //Adapta el rect para que el objeto apareca en el centro de este
        coordinateX -= _scale*_texture->width() / 2;
        coordinateY -= _scale*_texture->height() / 2;

        SDL_Rect dest = build_sdlrect(coordinateX, coordinateY, _texture->width()*_scale, _texture->height()*_scale);

        return dest;
    }

    void RenderTextureComponent::setRenderLayer(layerId_t layer)
    {
        _renderLayer = layer;
        _myEntity->getScene().sortRenderOrder();
    }

    void RenderTextureComponent::changeColorTint(int r, int g, int b){
        _color.r = r;
        _color.g = g;
        _color.b = b;
    }

    void RenderTextureComponent::resetColorTint(){
        _color.r = 255;
        _color.g = 255;
        _color.b = 255;
    }
} 