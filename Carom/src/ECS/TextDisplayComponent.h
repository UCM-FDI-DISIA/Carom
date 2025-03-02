#pragma once 
#include <string>
#include <SDL.h>
#include "RenderTextureComponent.h"
#include "Font.h"


class Font;
class Texture;
namespace ecs {
    class ITransform;
    class TextDisplayComponent : public RenderTextureComponent{
        //Atributos del texto
        std::string _text;
        SDL_Color _color;
        std::string _key;

        void reGenerateTexture();
    public:
        __CMPID_DECL__(cmp::TEXT_DISPLAY);
        /// @brief Constructor del componente para mostrar texto
        /// @param entity La entidad a la que pertenece
        /// @param initialText El valor inicial del texto que renderiza
        /// @param color El color del texto a mostrar
        /// @param key La key con la que buscar la fuente en el resources.json
        /// @param displayScale la escala del rect donde se crea el texto
        TextDisplayComponent(Entity* entity, int renderOrder, float displayScale, std::string initialText, SDL_Color color, std::string key);

        void changeFont(std::string key);
        void setColor(SDL_Color);
        void setDisplayedText(std::string text);
    };
}