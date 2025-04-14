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

void UIScene::createText(std::string text, int x, int y, int size)
{
    entity_t winContainer = new Entity(*this, grp::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);

    winContainer->addComponent(new TransformComponent(winContainer, pos));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(
        winContainer,           // container
        renderLayer::SCORE,     // capa renderizado
        size,                      // tamano fuente
        text,         // text
        {255, 255, 255, 255},   // color (blanco)
        "Basteleur-Moonlight60" // fuente
    );
    winContainer->addComponent(currentDisplay);
}

entity_t UIScene::createSceneButton(int x, int y, GameScene* scene, grpId_t g, layerId_t r, std::string tex, float size)
{
    entity_t e = new Entity(*this, g);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(tex), r, size);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    e->getComponent<Button>()->setOnClick([this, scene](){
        game->getScenesManager()->pushScene(scene);
    });   
    
    return e;
}

entity_t UIScene::createSceneButton(int x, int y, GameScene* scene)
{
    entity_t e = new Entity(*this, grp::DEFAULT);

    b2Vec2 pos = PhysicsConverter::pixel2meter(x, y);    

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::UI, 0.75f);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    e->getComponent<Button>()->setOnClick([this, scene](){
        game->getScenesManager()->pushScene(scene);
    });   
    
    return e;
}
