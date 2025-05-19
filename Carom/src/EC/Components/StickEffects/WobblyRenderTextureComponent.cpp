
#include "WobblyRenderTextureComponent.h"
#include <vector>
#include <SDL.h>
#include "SDLUtils.h"

#include <algorithm>

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

        posY += _height*sin(float(_speed*(float) posX / sdlutils().width()+ (float)sdlutils().currRealTime()/1000));

        vertex.position = SDL_FPoint{posX, posY};
        float yTexCoord;
        if(i < VERTICES_BY_WIDTH) yTexCoord = 0;
        else yTexCoord = 1;
        vertex.tex_coord = SDL_FPoint{(posX - textureRect.x)/textureRect.w, yTexCoord};
        vertex.tex_coord.x = std::clamp(vertex.tex_coord.x, 0.f, 1.f);
        vertex.tex_coord.y = std::clamp(vertex.tex_coord.y, 0.f, 1.f);

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