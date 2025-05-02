#include "RewardInfoDisplayComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "CameraComponent.h"
#include "GameScene.h"
#include "SDLUtils.h"

RewardInfoDisplayComponent::RewardInfoDisplayComponent(
    Entity* entity, layerId_t renderLayer, 
    Body title, Body rewardName, Body rewardType, Body rewardDescription, 
    Uint32 wrapLength, int offsetX, int offsetY)

: RenderTextureComponent(entity, _texture, renderLayer, title.scale)
, _title(title)
, _rewardName(rewardName)
, _rewardType(rewardType)
, _rewardDescription(rewardDescription)
, _wrapLength(wrapLength)
, _offsetX(offsetX) 
, _offsetY(offsetY) 
{
    generateTextures();
}


// TODO
void 
RewardInfoDisplayComponent::render() {
    
    double rotation = _transform->getRotation();
    int offset = 0;

    if(_texture != nullptr) {
        _texture->changeColorTint(_color.r, _color.g, _color.b);
        _texture->render(getRenderRect(_texture, _title.scale), rotation);
        _texture->changeColorTint(255,255,255);
        
        offset += (getRenderRect(_texture, _title.scale).h 
                + getRenderRect(_texture, _title.scale).h * 2.f/5.f);
    }

    if(_rewardNameTexture != nullptr) {

        _rewardNameTexture->changeColorTint(_color.r, _color.g, _color.b);
        _rewardNameTexture->render(getRenderRect(_rewardNameTexture, _rewardName.scale, offset), rotation);
        _rewardNameTexture->changeColorTint(255,255,255);
        
        offset += getRenderRect(_rewardNameTexture, _rewardName.scale).h * 3.f/4.f;
    }
    else offset += _rewardName.scale * 15;

    if(_rewardTypeTexture != nullptr) {   
        
        _rewardTypeTexture->changeColorTint(_color.r, _color.g, _color.b);
        _rewardTypeTexture->render(getRenderRect(_rewardTypeTexture, _rewardType.scale, offset), rotation);
        _rewardTypeTexture->changeColorTint(255,255,255);
        
        offset += (getRenderRect(_rewardTypeTexture, _rewardType.scale).h 
                + getRenderRect(_rewardTypeTexture, _rewardType.scale).h/2);
    }

    if(_rewardDescTexture != nullptr) {

        _rewardDescTexture->changeColorTint(_color.r, _color.g, _color.b);
        _rewardDescTexture->render(getRenderRect(_rewardDescTexture, _rewardDescription.scale, offset), rotation);
        _rewardDescTexture->changeColorTint(255,255,255);
    }

}


/// @param t Text texture to get render rect from
/// @param offset Y offset between texts
SDL_Rect
RewardInfoDisplayComponent::getRenderRect(Texture* t, float scale, int offset) const {
    b2Vec2 physicalPosition = _transform->getPosition();

    //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
    auto [coordinateX, coordinateY] = _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
    coordinateY += (_offsetY + offset);
    
    //Adapta el rect para que el objeto apareca en el centro de este
    coordinateX += _offsetX;
    coordinateY -= scale*t->height() / 2;

    SDL_Rect dest = build_sdlrect(coordinateX, coordinateY, t->width()*scale, t->height()*scale);

    return dest;
}

void RewardInfoDisplayComponent::setTitle(Body title)
{
    _title.text = title.text;
    _title.scale = title.scale;
    _title.font = title.font;
    _title.color = title.color;
}

void RewardInfoDisplayComponent::setRewardName(Body name)
{
    _rewardName.text = name.text;
    _rewardName.scale = name.scale;
    _rewardName.font = name.font;
    _rewardName.color = name.color;

    generateTextures();
}

void RewardInfoDisplayComponent::setRewardType(Body type)
{
    _rewardType.text = type.text;
    _rewardType.scale = type.scale;
    _rewardType.font = type.font;
    _rewardType.color = type.color;

    generateTextures();
}

void RewardInfoDisplayComponent::setRewardDesc(Body desc)
{
    _rewardDescription.text = desc.text;
    _rewardDescription.scale = desc.scale;
    _rewardDescription.font = desc.font;
    _rewardDescription.color = desc.color;

    generateTextures();
}

void 
RewardInfoDisplayComponent::generateTextures() {
    _title.text != " " 
        ? _texture = new Texture(sdlutils().renderer(), _title.text, sdlutils().fonts().at(_title.font), _title.color)
        : _texture = nullptr;

    _rewardName.text != " "
        ? _rewardNameTexture = new Texture(sdlutils().renderer(), _rewardName.text, 
                                        sdlutils().fonts().at(_rewardName.font), _rewardName.color)
        : _rewardNameTexture = nullptr;

    _rewardType.text != " "
        ? _rewardTypeTexture = new Texture(sdlutils().renderer(), _rewardType.text, 
                                        sdlutils().fonts().at(_rewardType.font), _rewardType.color)
        : _rewardTypeTexture = nullptr;

    _rewardDescription.text != " "
        ? _rewardDescTexture = new Texture(sdlutils().renderer(), _rewardDescription.text, 
                                        sdlutils().fonts().at(_rewardDescription.font), _rewardDescription.color, _wrapLength)
        : _rewardDescTexture = nullptr;
}