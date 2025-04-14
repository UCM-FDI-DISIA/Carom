#include "RewardInfoDisplayComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "CameraComponent.h"
#include "GameScene.h"
#include "SDLUtils.h"

RewardInfoDisplayComponent::RewardInfoDisplayComponent(
    Entity* entity, layerId_t renderLayer, float scale, 
    Body title, Body rewardName, Body rewardType, Body rewardDescription, 
    Uint32 wrapLength)

: RenderTextureComponent(entity, _texture, renderLayer, scale)
, _title(title)
, _rewardName(rewardName)
, _rewardType(rewardType)
, _rewardDescription(rewardDescription)
, _wrapLength(wrapLength) 
{
    generateTextures();
}


// TODO
void 
RewardInfoDisplayComponent::render() {
    
    double rotation = _transform->getRotation();

    _texture->changeColorTint(_color.r, _color.g, _color.b);
    _texture->render(getRenderRect(_texture), rotation);
    _texture->changeColorTint(255,255,255);
    
    int offset = getRenderRect(_texture).h;

    _rewardNameTexture->changeColorTint(_color.r, _color.g, _color.b);
    _rewardNameTexture->render(getRenderRect(_rewardNameTexture, offset), rotation);
    _rewardNameTexture->changeColorTint(255,255,255);

    offset += getRenderRect(_rewardNameTexture).h;

    _rewardTypeTexture->changeColorTint(_color.r, _color.g, _color.b);
    _rewardTypeTexture->render(getRenderRect(_rewardTypeTexture, offset), rotation);
    _rewardTypeTexture->changeColorTint(255,255,255);

    offset += getRenderRect(_rewardDescTexture).h;

    _rewardDescTexture->changeColorTint(_color.r, _color.g, _color.b);
    _rewardDescTexture->render(getRenderRect(_rewardDescTexture, offset), rotation);
    _rewardDescTexture->changeColorTint(255,255,255);

}


SDL_Rect
RewardInfoDisplayComponent::getRenderRect(Texture* t, int offset) const {
    b2Vec2 physicalPosition = _transform->getPosition();

    //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
    auto [coordinateX, coordinateY] = _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
    coordinateY += offset;
    
    //Adapta el rect para que el objeto apareca en el centro de este
    coordinateX -= _scale*t->width() / 2;
    coordinateY -= _scale*t->height() / 2;

    SDL_Rect dest = build_sdlrect(coordinateX, coordinateY, t->width()*_scale, t->height()*_scale);

    return dest;
}


void 
RewardInfoDisplayComponent::generateTextures() {
    _texture = new Texture(sdlutils().renderer(), _title.text, sdlutils().fonts().at(_title.font), _title.color);
    _rewardNameTexture = new Texture(sdlutils().renderer(), _rewardName.text, 
                    sdlutils().fonts().at(_rewardName.font), _rewardName.color);
    _rewardTypeTexture = new Texture(sdlutils().renderer(), _rewardType.text, 
                    sdlutils().fonts().at(_rewardType.font), _rewardType.color);
    _rewardDescTexture = new Texture(sdlutils().renderer(), _rewardDescription.text, 
                    sdlutils().fonts().at(_rewardDescription.font), _rewardDescription.color);
}