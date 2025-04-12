#include "MainMenuScene.h"
#include "PoolScene.h"
#include "ScenesManager.h"

MainMenuScene::MainMenuScene(Game *g) : UIScene(g)
{
    entity_t a_bg = createBackground("menuBackground");

    // --- PANELES.
    std::vector<entity_t> button;
    button.emplace_back(createSVGSceneButton("mainMenu", "RectangleMENU", "RectangleMENU")); // no se acciona [0]
    button.emplace_back(createSVGSceneButton("mainMenu", "RectangleTitle", "RectangleTitle")); // no se acciona [1]
    button.emplace_back(createSVGSceneButton("mainMenu", "RectanglePlay", "RectanglePlay")); // [2]
    button.emplace_back(createSVGSceneButton("mainMenu", "RectangleSettings", "RectangleSettings")); // [3]
    button.emplace_back(createSVGSceneButton("mainMenu", "RectangleControls", "RectangleControls")); // [4]
    button.emplace_back(createSVGSceneButton("mainMenu", "RectangleCredits", "RectangleCredits")); // [5]

    // ajustando fondo.
    b2Vec2 pos = {a_bg->getTransform()->getPosition().x, a_bg->getTransform()->getPosition().y - PhysicsConverter::pixel2meter(147)};
    a_bg->getTransform()->setPosition(pos);
    
    // --- TEXTOS.
    createText("Carom", // text
        button[1]->getTransform()->getPosition().x, // x
        button[1]->getTransform()->getPosition().y, // y
        2 // size.
    );

    createText("Play", // text
        button[2]->getTransform()->getPosition().x, // x
        button[2]->getTransform()->getPosition().y, // y
        1 // scale
    );
    
    button[2]->getComponent<Button>()->setOnClick([this](){
        // !!! SE CREA POOLSCENE
        GameScene *ms = new PoolScene(game); // ! tst 
        getGame()->getScenesManager()->pushScene(ms);
    });  

    createText("Settings", // text
        button[3]->getTransform()->getPosition().x, // x
        button[3]->getTransform()->getPosition().y, // y
        1 // scale
    );

    createText("Controls", // text
        button[4]->getTransform()->getPosition().x, // x
        button[4]->getTransform()->getPosition().y, // y
        1 // scale
    );

    createText("Credits", // text
        button[5]->getTransform()->getPosition().x, // x
        button[5]->getTransform()->getPosition().y, // y
        1 // scale
    );

    for(int i = 1; i < 6; i++){
        std::cout << "b" << i << ". x: " << button[i]->getTransform()->getPosition().x << "y: " << button[i]->getTransform()->getPosition().y << std::endl;
    }
}
