#include "UIScene.h"

#include "TextDisplayComponent.h"
#include "ScenesManager.h"

void UIScene::init()
{
    initFunctionalities();
    initObjects();

    _initialized = true;
}

void UIScene::createTable()
{
    // !---- TEXTURES ----//
    // Set scale (same for all)
    float svgSize = *&sdlutils().svgs().at("game").at("mesa_marco").width;
    float textureSize = sdlutils().images().at("mesa1").width();
    float scale = svgSize/textureSize;

    // Entidad marco
    entity_t e_marco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_m = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("mesa_marco").x, *&sdlutils().svgs().at("game").at("mesa_marco").y);
    addComponent<TransformComponent>(e_marco, pos_m);
    addComponent<RenderTextureComponent>(e_marco, &sdlutils().images().at("mesa1"), renderLayer::TABLE_BORDER, scale);

    // Entidad suelo
    entity_t e_fondo = new Entity(*this, grp::TABLE_BACKGROUND);
    b2Vec2 pos_f = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("fondo_mesa").x, *&sdlutils().svgs().at("game").at("fondo_mesa").y);
    addComponent<TransformComponent>(e_fondo, pos_f);
    addComponent<RenderTextureComponent>(e_fondo, &sdlutils().images().at("fondo"), renderLayer::TABLE_BACKGOUND, scale);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_s = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("mesa_sombra").x, *&sdlutils().svgs().at("game").at("mesa_sombra").y);
    addComponent<TransformComponent>(e_sombraMarco, b2Vec2{pos_s.x - 0.2f, pos_s.y - 0.2f});
    addComponent<RenderTextureComponent>(e_sombraMarco, &sdlutils().images().at("mesa1_sombra"), renderLayer::TABLE_SHADOW, scale);
}

void UIScene::createText(std::string text, int x, int y, int size, SDL_Color color, layerId_t rlayer)
{
    entity_t winContainer = new Entity(*this, grp::grpId::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);

    winContainer->addComponent(new TransformComponent(winContainer, pos));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(
        winContainer,           // container
        rlayer,     // capa renderizado
        size,                   // tamano fuente
        text,                   // text
        color,   // color (blanco)
        "Basteleur-Moonlight60" // fuente
    );
    winContainer->addComponent(currentDisplay);
}

entity_t UIScene::createSVGImage(std::string svg, std::string tag, std::string image, 
    bool isButton, grp::grpId group, layerId_t renderlayer)
{
    entity_t e = new Entity(*this, group);

    auto a = *&sdlutils().svgs().at(svg);
    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at(svg).at(tag).x,
        *&sdlutils().svgs().at(svg).at(tag).y
    );

    float scale = float(sdlutils().svgs().at(svg).at(tag).width) / float(sdlutils().images().at(image).width());

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(image), renderlayer, scale);

    if(isButton){
        Button::TextureButton rButton = Button::TextureButton();
        addComponent<Button>(e, rButton);
    }

    return e;
}

void UIScene::createButton(int x, int y, std::string text, Texture* t, std::function<void ()> cb) {

        entity_t e = new Entity(*this, grp::UI);

        b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);
    
        // TODO cambiar escala real
        float scale = float(sdlutils().svgs().at("pool").at("hole 0").width) / float(sdlutils().images().at("hole").width());
    
        addComponent<TransformComponent>(e, pos);
        // TODO cambiar imagen real
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("reward_description_box"), renderLayer::UI, scale);
    
        Button::TextureButton button = Button::TextureButton();
        Button* b = addComponent<Button>(e, button);

        b->setOnClick(cb);
}