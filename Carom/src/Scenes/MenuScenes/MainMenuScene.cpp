#include "MainMenuScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"
#include "AudioManager.h"
#include "TutorialScene.h"
#include "InventoryManager.h"
#include "ControlsScene.h"

MainMenuScene::MainMenuScene(Game *g) 
    : UIScene(g)
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::initFunctionalities()
{
    auto inv = InventoryManager::Instance();
    inv->loadStartingInventory();
}

void MainMenuScene::initObjects()
{
    // tag del svg al que nos referimos segun el JSON.
    std::string SVGTag = "mainMenu";

    // --- BACKGROUND.
    entity_t x_bg = createBackground("fondoMainMenu"); // fondo.
    entity_t a_bg = createBackground("menuBackground"); // mesa fondo.

    // ajustando fondo.
    b2Vec2 pos = {
        a_bg->getTransform()->getPosition().x, 
        a_bg->getTransform()->getPosition().y
    };
    a_bg->getTransform()->setPosition(pos);

    // --- PANELES.
    std::vector<entity_t> pannels;
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleMENU", "RectangleMENU")); 
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleTitle", "RectangleTitle")); 
    pannels.emplace_back(createSVGImage(SVGTag, "RectanglePlay", "RectanglePlay", true)); 
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleTutorial", "RectangleTutorial", true)); 
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleControls", "RectangleControls", true)); 
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleCredits", "RectangleCredits", true)); 
    pannels.emplace_back(createSVGImage(SVGTag, "RectangleExit", "RectangleExit", true)); 

    // rtmp = render texture menu pannel.
    RenderTextureComponent* rtmp = pannels[0]->getComponent<RenderTextureComponent>(); 
    rtmp->setScale(1.3 * rtmp->getScale());
    
    // Hacer que se pueda accionar el boton de PLAY
    pannels[2]->getComponent<Button>()->setOnClick([this](){
        // Se crea POOLSCENE
        std::shared_ptr<PoolScene> _poolScene = std::make_shared<PoolScene>(game);
        InventoryManager::Instance()->loadStartingInventory();
        getGame()->getScenesManager()->pushScene(_poolScene);
    });  

    // Hacer que se pueda accionar el boton de TUTORIAL
    pannels[3]->getComponent<Button>()->setOnClick([this](){
        // Se crea POOLSCENE
        std::shared_ptr<PoolScene> _poolScene = std::make_shared<PoolScene>(game);
        getGame()->getScenesManager()->pushScene(_poolScene);
        TutorialScene* tutorial = new TutorialScene(game, _poolScene.get());
        getGame()->getScenesManager()->pushScene(std::shared_ptr<TutorialScene>(tutorial));
    });  

    // Hacer que se pueda accionar el boton de CONTROLS
    pannels[4]->getComponent<Button>()->setOnClick([this](){
        // Se crea CONTROLSSCENE
        std::shared_ptr<ControlsScene> _ctrlScene = std::make_shared<ControlsScene>(game);
        getGame()->getScenesManager()->pushScene(_ctrlScene);
    }); 

    // Hacer que se pueda accionar el boton de EXIT
    pannels[6]->getComponent<Button>()->setOnClick([this](){
        getGame()->close();
    }); 

    //Empieza la musica
    _am = AudioManager::Instance();
    
    _am->playMusicTrack(PAUSE_THEME);
    _am->playMusicTrack(MAIN_THEME);

    _am->changeToPauseTheme();
    
    // --- TEXTOS.
    std::vector<entity_t> texts;
    texts.emplace_back(createSVGImage(SVGTag, "C", "C"));
    texts.emplace_back(createSVGImage(SVGTag, "AROM", "AROM"));
    texts.emplace_back(createSVGImage(SVGTag, "Play", "Play"));
    texts.emplace_back(createSVGImage(SVGTag, "Tutorial", "Tutorial"));
    texts.emplace_back(createSVGImage(SVGTag, "Controls", "Controls"));
    texts.emplace_back(createSVGImage(SVGTag, "Credits", "Credits"));
    texts.emplace_back(createSVGImage(SVGTag, "Exit", "Exit"));
}
