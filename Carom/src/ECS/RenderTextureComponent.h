#pragma once
#include "ecs.h"
#include "RenderComponent.h"

class Texture;
<<<<<<< HEAD
class TransformComponent;
=======
>>>>>>> 2425fccc605626d92f6da6cbdb270c719588af23

namespace ecs {
    class TransformComponent;
    
    class RenderTextureComponent : public RenderComponent {
    private:
        Texture* _texture;
        TransformComponent* _transform;
    public:
        __CMPID_DECL__(cmp::RENDER_TEXTURE);

        RenderTextureComponent(Entity*, Texture*);
        ~RenderTextureComponent() {};

        void render() override;
        void init() override;
    };
}