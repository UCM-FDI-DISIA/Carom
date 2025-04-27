
#include "WobblyRenderTextureComponent.h"
#include <vector>
#include <SDL.h>
#include "SDLUtils.h"

WobblyRenderTextureComponent::WobblyRenderTextureComponent(Entity* entity, layerId_t renderLayer, float displayScale, 
    std::string initialText, SDL_Color color, std::string key): TextDisplayComponent(entity, renderLayer, displayScale, initialText, color, key){

    }

void WobblyRenderTextureComponent::render(){
    SDL_Rect textureRect = getRenderRect();

    int pixelsBetween = textureRect.w/(VERTICES_BY_WIDTH-1);

    std::vector<SDL_Vertex> textureVertices;
    std::vector<int> indexes;
    
    for(int i =0; i <VERTICES_BY_WIDTH*2; i++){
        SDL_Vertex vertex;
        vertex.color = _color;
        float posX;
        float posY;
        if(i < VERTICES_BY_WIDTH) posX = textureRect.x + pixelsBetween* i;
        else posX= textureRect.x + pixelsBetween* (i-VERTICES_BY_WIDTH);

        if(i < VERTICES_BY_WIDTH) posY = textureRect.y;
        else posY = textureRect.y + textureRect.h;

        vertex.position = SDL_FPoint{posX, posY};
        vertex.tex_coord = SDL_FPoint{(posX - textureRect.x)/textureRect.w, (posY-textureRect.y)/textureRect.h};

        textureVertices.push_back(vertex);
    }

    for(int i =0; i < VERTICES_BY_WIDTH-1; i++){
        indexes.push_back(i);
        indexes.push_back(i+1);
        indexes.push_back(VERTICES_BY_WIDTH+i);
        indexes.push_back(VERTICES_BY_WIDTH+i);
        indexes.push_back(i+1);
        indexes.push_back(VERTICES_BY_WIDTH+i+1);
    }
    
    _texture->render(textureRect, textureVertices.data(), textureVertices.size(), indexes.data(), indexes.size());
}