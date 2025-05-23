#include "TextDisplayComponent.h"

#include "ITransform.h"
#include "PhysicsUtils.h"
#include "Texture.h"
#include "Entity.h"
#include "SDLUtils.h"


TextDisplayComponent::TextDisplayComponent(Entity* entity, layerId_t renderLayer, float displayScale, 
    std::string initialText, SDL_Color color, std::string key, Uint32 wrapLength)

: RenderTextureComponent(entity, nullptr, renderLayer, displayScale), 
_text(initialText), 
_color(color), 
_key(key),
_wrapLength(wrapLength)
{
    reGenerateTexture();
}

TextDisplayComponent::~TextDisplayComponent()
{
    delete _texture;
}

void 
TextDisplayComponent::changeFont(std::string key) {
    _key = key;
    reGenerateTexture();
}

void
TextDisplayComponent::setColor(SDL_Color color) {
    _color = color;
    reGenerateTexture();
}

void 
TextDisplayComponent::setDisplayedText(std::string text) {
    _text = text;
    reGenerateTexture();
}

void 
TextDisplayComponent::reGenerateTexture() {
    if(_texture != nullptr) delete _texture;

    if (_wrapLength == 0)
        _texture = new Texture(sdlutils().renderer(), _text, sdlutils().fonts().at(_key), _color);
    else 
        _texture = new Texture(sdlutils().renderer(), _text, sdlutils().fonts().at(_key), _color, _wrapLength);
}