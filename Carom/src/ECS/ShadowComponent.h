#pragma once

#include "InfoComponent.h"
#include <vector>
#include "RenderTextureComponent.h"

class Entity;

class ShadowComponent: public InfoComponent{
    std::vector<entity_t> _shadows;
public:
    __CMPID_DECL__(cmp::SHADOW);

    inline ShadowComponent(entity_t e): InfoComponent(e){
        _shadows.resize(0);
    };

    ~ShadowComponent(){
        for(entity_t e : _shadows){
            e->removeComponent<RenderTextureComponent>();
            e->deactivate();
            e->setAlive(false);
        }
    }

    void addShadow(b2Vec2 displacement, std::string imageName, int renderLayer, float scale, bool copyPosition = true, bool copyRotation = true, bool copyScale = true);

    //si se desactiva sus sombras se desactivan, si se activan sus sombras lo hacen
    inline void setEnabled(bool b) override{
        Component::setEnabled(b);

        for(auto e : _shadows) {
            if(b) e->activate();
            else e->deactivate();
        }
    }

    
};