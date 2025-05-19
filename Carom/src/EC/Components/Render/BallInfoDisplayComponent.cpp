#include "BallInfoDisplayComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "CameraComponent.h"
#include "GameScene.h"
#include "SDLUtils.h"

BallInfoDisplayComponent::BallInfoDisplayComponent(
    Entity* entity, layerId_t renderLayer, 
    Body title, Body ballDescription, 
    Uint32 wrapLength, int offsetX, int offsetY)

: RenderTextureComponent(entity, nullptr, renderLayer, title.scale)
, _title(title)
, _ballDescription(ballDescription)
, _wrapLength(wrapLength)
, _offsetX(offsetX) 
, _offsetY(offsetY) 
{
    generateTextures();
}

BallInfoDisplayComponent::~BallInfoDisplayComponent() {
    // esto se hace porque esta clase no pilla texturas del utils, las crea ella misma
    if (_texture != nullptr) delete _texture; 
    if (_ballDescTexture != nullptr) delete _ballDescTexture; 

    _texture = nullptr;
}

// TODO
void 
BallInfoDisplayComponent::render() {
    
    double rotation = _transform->getRotation();

    _texture->changeColorTint(_color.r, _color.g, _color.b);
    _texture->render(getRenderRect(_texture, _title.scale), rotation);
    _texture->changeColorTint(255,255,255);
    
    int offset = getRenderRect(_texture, _title.scale).h + getRenderRect(_texture, _title.scale).h * 2.5f/5.f;

    _ballDescTexture->changeColorTint(_color.r, _color.g, _color.b);
    _ballDescTexture->render(getRenderRect(_ballDescTexture, _ballDescription.scale, offset), rotation);
    _ballDescTexture->changeColorTint(255,255,255);

}


/// @param t Text texture to get render rect from
/// @param offset Y offset between texts
SDL_Rect
BallInfoDisplayComponent::getRenderRect(Texture* t, float scale, int offset) const {
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


void 
BallInfoDisplayComponent::generateTextures() {
    _texture = new Texture(sdlutils().renderer(), _title.text, sdlutils().fonts().at(_title.font), _title.color);
    _ballDescTexture = new Texture(sdlutils().renderer(), _ballDescription.text, 
                    sdlutils().fonts().at(_ballDescription.font), _ballDescription.color, _wrapLength);
}