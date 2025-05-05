#include "RenderSpritesheetComponent.h"

#include "Entity.h"
#include "GameScene.h"
#include <exception>

RenderSpritesheetComponent::RenderSpritesheetComponent
    (entity_t ent,  Texture* tex, layerId_t renderLayer, float scale, int rows, int cols, int frame)
: RenderComponent(ent, renderLayer),
_texture(tex),
_scale(scale),
_rows(rows),
_cols(cols)
{

    assert(tex != nullptr);

    _width = tex->width() / cols;
    _height = tex->height() / rows;

    setFrame(frame);
}

void
RenderSpritesheetComponent::init() {
    _transform = _myEntity->getTransform();
}

void
RenderSpritesheetComponent::render() {
    _texture->render(
        {_xOriginFrame, _yOriginFrame, _width, _height}, 
        getRenderRect(),
        _transform->getRotation());
}

SDL_Rect 
RenderSpritesheetComponent::getRenderRect() const
{
    b2Vec2 physicalPosition = _transform->getPosition();
    //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
    auto [coordinateX, coordinateY] = 
        _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
    
    //Adapta el rect para que el objeto apareca en el centro de este
    coordinateX -= _scale * _width / 2;
    coordinateY -= _scale * _height / 2;

    SDL_Rect dest = {coordinateX, coordinateY, static_cast<int>(_width * _scale), static_cast<int>(_height * _scale)};

    return dest;
}

void 
RenderSpritesheetComponent::setFrame(int frame) {
    if(frame > _rows * _cols || frame < 0) {
        std::string err = "[RenderSpritesheetComponent::setFrame] FUERA DE RANGO: " + std::to_string(frame) + 
            " no esta en el rango de " + std::to_string(_rows) + "x" + std::to_string(_rows);
        throw std::out_of_range(err);
    }
    
    _xOriginFrame = _width  * (frame % _cols);
    _yOriginFrame = _height * (frame / _cols);

    _currentFrame = frame;
}