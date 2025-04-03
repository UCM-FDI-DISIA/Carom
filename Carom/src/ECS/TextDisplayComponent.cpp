#include "TextDisplayComponent.h"

#include "ITransform.h"
#include "PhysicsUtils.h"
#include "Texture.h"
#include "Entity.h"
#include "SDLUtils.h"


TextDisplayComponent::TextDisplayComponent(Entity* entity, int renderLayer, float displayScale, std::string initialText, SDL_Color color, std::string key)
    : RenderTextureComponent(entity, _texture, renderLayer, displayScale), _text(initialText), _color(color), _key(key)
{
    reGenerateTexture();
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
    _texture = new Texture(sdlutils().renderer(), _text, sdlutils().fonts().at(_key), _color);
}