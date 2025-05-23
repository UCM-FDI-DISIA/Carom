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

// truconsejo, si en el inicializador de RenderTextureComponent le metes _texture (que es miembro sin inicializar)
// le estas metiendo memoria no inicializada, que es como meterle nada pero que además te jode (porque no puedes 
// evaluar que es nulo), si quieres inicializar con nada para eso está nullptr
: RenderTextureComponent(entity, nullptr, renderLayer, title.scale)
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


RewardInfoDisplayComponent::~RewardInfoDisplayComponent() {

    deleteTextures();

    _rewardNameTexture = nullptr;
    _rewardTypeTexture = nullptr;
    _rewardDescTexture = nullptr;
    _texture = nullptr;
}

void
RewardInfoDisplayComponent::deleteTextures() {

    if(_rewardNameTexture != nullptr) delete _rewardNameTexture;
    if(_rewardTypeTexture != nullptr) delete _rewardTypeTexture;
    if(_rewardDescTexture != nullptr) delete _rewardDescTexture;

    // En efecto así es, estoy borrando memoria que no es de este componente,
    // en este caso particular no pasa nada porque RenderTextureComponent no borra
    // su textura, de eso se suele encargar sdlutils
    if(_texture != nullptr) delete _texture;
}

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
    _title = title;
    generateTextures();
}

void RewardInfoDisplayComponent::setRewardName(Body name)
{
   _rewardName = name;
    generateTextures();
}

void RewardInfoDisplayComponent::setRewardType(Body type)
{
    _rewardType = type;
    generateTextures();
}

void RewardInfoDisplayComponent::setRewardDesc(Body desc)
{
   _rewardDescription = desc;
    generateTextures();
}

void 
RewardInfoDisplayComponent::generateTextures() {

    // Puesto que se estan generando nuevas texturas aquí (crear memoria en ejecución no mola mucho)
    // pues hay que mantener esto limpio, muy importante borrar las texturas antiguas antes de regenerarlas
    deleteTextures();

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