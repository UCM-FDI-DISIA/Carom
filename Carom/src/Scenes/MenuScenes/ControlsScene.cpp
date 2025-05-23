#include "ControlsScene.h"
#include "ScenesManager.h"
#include "AudioManager.h"
#include "MainMenuScene.h"

ControlsScene::ControlsScene(Game *g) 
    : UIScene(g)
{
}

ControlsScene::~ControlsScene()
{
}

void ControlsScene::initFunctionalities()
{
    _mainMenuScene = std::make_shared<MainMenuScene>(game);
}

void ControlsScene::initObjects()
{
    // tag del svg al que nos referimos segun el JSON.
    std::string SVGTag = "controlsMenu";

    // --- BACKGROUND.
    entity_t x_bg = createBackground("fondoControls"); 

    // ajustando fondo.
    b2Vec2 pos = {
        x_bg->getTransform()->getPosition().x, 
        x_bg->getTransform()->getPosition().y
    };
    x_bg->getTransform()->setPosition(pos);

    // --- PANELES DEL FONDO
    std::vector<entity_t> bgPannels;
    bgPannels.emplace_back(createSVGImage(SVGTag, "RectangleTitle", "RectangleTitle"));  
    bgPannels.emplace_back(createSVGImage(SVGTag, "RectangleInteraccionGrande", "RectangleInteraccionGrande"));
    bgPannels.emplace_back(createSVGImage(SVGTag, "RectangleInventarioGrande", "RectangleInventarioGrande"));  
    bgPannels.emplace_back(createSVGImage(SVGTag, "RectangleMenuPausaGrande", "RectangleMenuPausaGrande"));  

    // --- PANELES DE TITULOS
    std::vector<entity_t> titlePannels;
    titlePannels.emplace_back(createSVGImage(SVGTag, "RectangleInteraccionNombre", "RectangleInteraccionNombre"));  
    titlePannels.emplace_back(createSVGImage(SVGTag, "RectangleInventario", "RectangleInventario"));
    titlePannels.emplace_back(createSVGImage(SVGTag, "RectangleMenuPausa", "RectangleMenuPausa"));

    // --- IMAGENES Y DEMAS
    std::vector<entity_t> imgs;
    imgs.emplace_back(createSVGImage(SVGTag, "scoreSprite", "scoreSprite"));
    imgs.emplace_back(createSVGImage(SVGTag, "imagenMenuPausa", "imagenMenuPausa"));
    imgs.emplace_back(createSVGImage(SVGTag, "drawer", "drawer"));
    imgs.emplace_back(createSVGImage(SVGTag, "palo_sombra", "SeletionArrow"));
    imgs.emplace_back(createSVGImage(SVGTag, "bola_blanca ", "bola_montada"));
    imgs.emplace_back(createSVGImage(SVGTag, "regresar", "scoreSprite", true));    
    imgs.emplace_back(createSVGImage(SVGTag, "cursor 1", "cursor"));    
    
    // --- TEXTOS DE TITULOS
    std::vector<entity_t> titleTexts;
    titleTexts.emplace_back(createSVGImage(SVGTag, "Interaccion", "Interaccion"));  
    titleTexts.emplace_back(createSVGImage(SVGTag, "Inventario", "Inventario"));  
    titleTexts.emplace_back(createSVGImage(SVGTag, "MenuPausa", "MenuPausa"));  
    titleTexts.emplace_back(createSVGImage(SVGTag, "C", "C"));  
    titleTexts.emplace_back(createSVGImage(SVGTag, "AROM", "AROM"));  
    titleTexts.emplace_back(createSVGImage(SVGTag, "rewardButtonText", "rewardButtonText"));  
    titleTexts.emplace_back(createSVGImage(SVGTag, "regresarText", "regresarText"));  
    
    // --- TEXTOS NORMALES
    std::vector<entity_t> nTexts;
    nTexts.emplace_back(createSVGImage(SVGTag, "InteraccionTextPalo", "InteraccionTextPalo"));
    nTexts.emplace_back(createSVGImage(SVGTag, "InventarioTextPalo1", "InventarioTextPalo1"));
    nTexts.emplace_back(createSVGImage(SVGTag, "InventarioTextClic", "InventarioTextClic"));
    nTexts.emplace_back(createSVGImage(SVGTag, "ControlesDe", "ControlesDe"));
    nTexts.emplace_back(createSVGImage(SVGTag, "InventarioText", "InventarioText"));
    nTexts.emplace_back(createSVGImage(SVGTag, "MenuPausaText", "MenuPausaText"));  
    
    // Hacer que se pueda accionar el boton de REGRESARR
    imgs[5]->getComponent<Button>()->setOnClick([this](){
        getGame()->getScenesManager()->popScene();
    });  
}
