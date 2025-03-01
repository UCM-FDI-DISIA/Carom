#include "TextDisplayComponent.h"

#include "ITransform.h"
#include "PhysicsUtils.h"
#include "Texture.h"
#include "Camera.h"
#include "Entity.h"
#include "SDLUtils.h"

namespace ecs {
    TextDisplayComponent::TextDisplayComponent(Entity* entity, std::string initialText, SDL_Color color, std::string key, float displayScale)
        : RenderComponent(entity), _text(initialText), _color(color), _key(key), _scale(displayScale)
    {
        reGenerateTexture();
    }

    void 
    TextDisplayComponent::init() {
        _transform = _myEntity->getTransform();
    }

    void 
    TextDisplayComponent::render(Camera* camera) {
        b2Vec2 physicalPosition = _transform->getPosition();
        //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
        auto [coordinateX, coordinateY] = camera->getRenderPos({physicalPosition.x, physicalPosition.y});
        
        //Adapta el rect para que el objeto apareca en el centro de este
        coordinateX -= _scale * _texture->width() / 2;
        coordinateY -= _scale * _texture->height() / 2;

        SDL_Rect dest = {coordinateX, coordinateY, (int)(_texture->width()*_scale), (int)(_texture->height()*_scale)};
        _texture->render(dest, _transform->getRotation());
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
}