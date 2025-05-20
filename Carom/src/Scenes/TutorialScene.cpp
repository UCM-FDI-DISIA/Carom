#include "TutorialScene.h"

#include "TransformComponent.h"
#include "WobblyRenderTextureComponent.h"
#include "RandomVibrationComponent.h"
#include "DialogueTextComponent.h"
#include "ScenesManager.h"
#include "CaromScene.h"
#include "NullState.h"
#include "RussianPyramidScene.h"
#include "InventoryManager.h"
#include "TutorialOneStartMatchState.h"
#include "TutorialTwoStartMatchState.h"
#include "TextHelperScene.h"
#include "PhysicsUtils.h"

TutorialScene::TutorialScene(Game* game, GameScene* sceneToRenderOnTop) : GameScene(game), _bottomScene(sceneToRenderOnTop){

    InventoryManager::Instance()->loadInventoryNamed("tutorialInventory1");

    //!tst borrar
    Entity* prueba = new Entity(*this, grp::UI);

    addComponent<TransformComponent>(prueba, b2Vec2{0.f,0.f});
    auto a = addComponent<WobblyRenderTextureComponent>(prueba,           // container
        renderLayer::UI,     // capa renderizado
        1.f,                   // tamano fuente
        " ",                   // text
        SDL_Color{255, 255, 255, 255},   // color (blanco)
        "Basteleur-Moonlight60" // fuente
    );

    addComponent<RandomVibrationComponent>(prueba, .05f, 5);

    auto dialogue = addComponent<DialogueTextComponent>(prueba, a);
    dialogue->addDialogue("Hola ");
    dialogue->addDialogue("Veo que has despertado ");
    dialogue->addDialogue("¿sabes cuánto tiempo llevas inconsciente? ");
    dialogue->addDialogue("207 años ");
    dialogue->addDialogue("Te hemos estado esperando durante todo este tiempo ");
    dialogue->addDialogue("y por fin estás aquí ");
    dialogue->addDialogue("Primero lo importante: ¿sabes jugar? ", [=](){

        CaromScene* caromOne = new CaromScene(game);
        
        auto a = std::shared_ptr<CaromScene>(caromOne);
        a.get()->setNewState(new TutorialOneStartMatchState(a.get()));

        game->getScenesManager()->pushScene(a);

        game->getScenesManager()->pushScene(std::shared_ptr<TextHelperScene>(new TextHelperScene(game, a, "Golpeas arrastrando el ratón")));
        caromOne->setScoreToBeat(1);
    });

    dialogue->addDialogue("Veo que sí que te acuerdas...");
    dialogue->addDialogue("Perfecto ");
    dialogue->addDialogue("Ahora, veamos si puedes hacer algún truco ");
    dialogue->addDialogue("Haz una carambola ",[=](){
        InventoryManager::Instance()->loadInventoryNamed("tutorialInventory2");
        auto caromOne = new CaromScene(game);
        auto a = std::shared_ptr<CaromScene>(caromOne);
        a.get()->setNewState(new TutorialTwoStartMatchState(a.get()));

        game->getScenesManager()->pushScene(a);

        game->getScenesManager()->pushScene(std::shared_ptr<TextHelperScene>(new TextHelperScene(game, a, "Golpea dos bolas consecutivamente con la bola blanca")));
    });
    dialogue->addDialogue("Si quieres sobrevivir, deberás ganar partidas ");
    dialogue->addDialogue("Para hacerlo, escucha atentamente: ");
    dialogue->addDialogue("Reúne los puntos necesarios antes de agotarse los golpes");
    dialogue->addDialogue("Para ganarlos, choca la bola blanca con las demás", [=](){

        CaromScene* caromOne = new CaromScene(game);
        
        auto a = std::shared_ptr<CaromScene>(caromOne);
        a.get()->setNewState(new TutorialOneStartMatchState(a.get()));

        game->getScenesManager()->pushScene(a);

        game->getScenesManager()->pushScene(std::shared_ptr<TextHelperScene>(new TextHelperScene(game, a, "Pruébalo")));
        caromOne->setScoreToBeat(30);
    });


    dialogue->addDialogue("Impresionante ");
    dialogue->addDialogue("Una última cosa ");
    dialogue->addDialogue("Te encuentras sobre una mesa de billar ");
    dialogue->addDialogue("Aquí puedes elegir tu próxima partida, ");
    dialogue->addDialogue("y siempre que termines una partida volverás aquí ");
    
    dialogue->addDialogue("Para elegir una partida, haz click sobre un hoyo ");
    dialogue->addDialogue("Usa el cursor para ver tu premio si ganas la partida ");
    dialogue->addDialogue("Recuerda, la informacion es poder");
    dialogue->addDialogue("Jugar una partida destruye la bola que cae al hoyo ");
    dialogue->addDialogue("Supera al jefe y recibirás las bolas restantes del billar ");

    dialogue->addDialogue("Bien, ya estás preparado ");
    dialogue->addDialogue("Pero recuerda, ");
    dialogue->addDialogue("si pierdes, ", [=](){

        Entity* boss = new Entity(*this, grp::BOSS_SHADOW);
    b2Vec2 pos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").x, sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").y);
    auto tr = addComponent<TransformComponent>(boss, b2Vec2{2.f,2.f});
    tr->setRotation(25);
    Texture* bossImage = &sdlutils().images().at("cowboy_table_shadow");

    float scale = sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").width/ (float)sdlutils().images().at("cowboy_table_shadow").width();
    addComponent<RenderTextureComponent>(boss, bossImage, renderLayer::BOSS_SHADOW, scale);

    auto tweens = addComponent<TweenComponent>(boss);
    tweens->easePosition(pos, .5f, tween::EASE_IN_OUT_CUBIC, false, [=](){
        addComponent<RandomVibrationComponent>(boss, .05f, 1.f);
    });

    });

    dialogue->addDialogue("eres nuestro para siempre", [=](){
        game->getScenesManager()->popScene();
    });
}


void TutorialScene::render(){
    _bottomScene->render();
    GameScene::render();
}