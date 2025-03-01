#pragma once 
#include <string>
#include <SDL.h>
#include "RenderComponent.h"
#include "Font.h"


class Font;
class Texture;
namespace ecs {
    class ITransform;
    class TextDisplayComponent : public RenderComponent{
        //Atributos del texto
        std::string _text;
        SDL_Color _color;
        std::string _key;

        //Necesidades de renderizado
        Texture* _texture;
        ITransform* _transform;
        float _scale;

        void reGenerateTexture();
    public:
        /// @brief Constructor del componente para mostrar texto
        /// @param entity La entidad a la que pertenece
        /// @param initialText El valor inicial del texto que renderiza
        /// @param color El color del texto a mostrar
        /// @param fontSize El tamaño de la fuente
        /// @param fileName La ruta al archivo de la fuente
        TextDisplayComponent(Entity* entity, std::string initialText, SDL_Color color, std::string key, float displayScale);

        void init() override;
        void render(Camera*) override;

        void changeFont(std::string key);
        void setColor(SDL_Color);
        void setDisplayedText(std::string text);
    };
}