#include "MainMenuScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"
#include "TutorialScene.h"

MainMenuScene::MainMenuScene(Game *g) 
    : UIScene(g)
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::initFunctionalities()
{
    _poolScene = std::make_shared<PoolScene>(game);
}

void MainMenuScene::initObjects()
{
    // tag del svg al que nos referimos segun el JSON.
    std::string SVGTag = "mainMenu";

    // --- BACKGROUND.
    entity_t x_bg = createBackground("fondoMainMenu"); // fondo.
    entity_t a_bg = createBackground("menuBackground"); // mesa fondo.

    // ajustando fondo.
    b2Vec2 pos = {a_bg->getTransform()->getPosition().x, a_bg->getTransform()->getPosition().y};
    a_bg->getTransform()->setPosition(pos);

    // --- PANELES.
    std::vector<entity_t> pannels;
    //pannels.emplace_back(createSVGImage(SVGTag, "RectangleMENUCorner", "RectangleMENUCorner", false)); // [0]
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleMENU", "RectangleMENU")); // [1]
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleTitle", "RectangleTitle")); // [2]
    pannels.emplace_back(createSVGImage(SVGTag, "RectanglePlay", "RectanglePlay", true)); // [3]
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleSettings", "RectangleSettings", true)); // [4]
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleControls", "RectangleControls", true)); // [5]
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleCredits", "RectangleCredits", true)); // [6]

    // Hacer que se pueda accionar el boton de Play
    pannels[2]->getComponent<Button>()->setOnClick([this](){
        // !!! SE CREA POOLSCENE
        getGame()->getScenesManager()->pushScene(_poolScene);
        TutorialScene* tutorial = new TutorialScene(game, _poolScene.get());
        getGame()->getScenesManager()->pushScene(std::shared_ptr<TutorialScene>(tutorial));
    });  

    // TODO: Hacer que se pueda accionar el boton de Settings
    // TODO: Hacer que se pueda accionar el boton de Controls
    // TODO: Hacer que se pueda accionar el boton de Credits
    
    // --- TEXTOS.
    std::vector<entity_t> texts;
    texts.emplace_back(createSVGImage(SVGTag, "C", "C"));
    texts.emplace_back(createSVGImage(SVGTag, "AROM", "AROM"));
    texts.emplace_back(createSVGImage(SVGTag, "Play", "Play"));
    texts.emplace_back(createSVGImage(SVGTag, "Settings", "Settings"));
    texts.emplace_back(createSVGImage(SVGTag, "Controls", "Controls"));
    texts.emplace_back(createSVGImage(SVGTag, "Credits", "Credits"));
}
