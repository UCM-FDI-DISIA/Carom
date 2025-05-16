#include "EndGameScene.h"
#include "ScenesManager.h"
#include "WobblyRenderTextureComponent.h"
#include "RandomVibrationComponent.h"
#include "DialogueTextComponent.h"



EndGameScene::EndGameScene(Game *g, bool win, bool isBoss)
    : UIScene(g)
    , _win(win)
    , _isBoss(isBoss)
{
}

void EndGameScene::initObjects()
{
    createBackground("suelo");

    createTable();

    if (_win)
        hasWon();
    else
        hasLost();
}

void EndGameScene::hasWon()
{
    if (_isBoss)
        bossWin();
    else
        standardWin();
    // // mitad de la pantalla en x.
    // int midWinX = sdlutils().width()/2;

    // createText("¡Has GANADO!", // text
    //     midWinX, // x
    //     sdlutils().height()/3, // y
    //     2 // size.
    // );
    
    // entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);

    // // Vuelve a reward
    // b->getComponent<Button>()->setOnClick([this]()
    // {
    //     game->getScenesManager()->popScene(); // Poppea esta escena
    //     // va a reward scene
    // }); 
}

void EndGameScene::standardWin()
{
    std::cout << "WIN" << std::endl;

    createSVGImage("win", "youwin", "youwin");

    entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);
    createSVGImage("win", "rewardButtonText", "rewardButtonText");

    // Vuelve a reward
    b->getComponent<Button>()->setOnClick([this]()
    {
        game->getScenesManager()->popScene(); // Poppea esta escena
        // va a reward scene
    }); 
}

void EndGameScene::bossWin()
{
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

    dialogue->addDialogue("Enhorabuena...", [=](){

    Entity* boss = new Entity(*this, grp::BOSS_SHADOW);
    b2Vec2 pos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").x, sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").y);
    auto tr = addComponent<TransformComponent>(boss, b2Vec2{2.f,2.f});
    tr->setRotation(25);
    Texture* bossImage = &sdlutils().images().at("cowboy_table_shadow"); // ! CAMBIAR A BOSS CURRENT

    float scale = sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").width/ (float)sdlutils().images().at("cowboy_table_shadow").width();
    addComponent<RenderTextureComponent>(boss, bossImage, renderLayer::BOSS_SHADOW, scale);

    auto tweens = addComponent<TweenComponent>(boss);
    tweens->easePosition(pos, .5f, tween::EASE_IN_OUT_CUBIC, false, [=](){
        addComponent<RandomVibrationComponent>(boss, .05f, 1.f);
    });

    });

    dialogue->addDialogue("Listo para el proximo piso?");
    dialogue->addDialogue("Vas a necesitar toda la ayuda que puedas...");
    dialogue->addDialogue("Aquí está tu regalo", [=](){
        game->getScenesManager()->popScene();
    });

}

void EndGameScene::hasLost()
{
    if (_isBoss)
        bossLose();
    else
        standardLose();
}

void EndGameScene::standardLose()
{
    createSVGImage("lose", "losetext", "citacionlose1");

    entity_t blackScreen = createSVGImage("lose", "blackscreen", "blackscreen", false, grp::grpId::DEFAULT, renderLayer::UI_BACK);

    auto render = blackScreen->getComponent<RenderTextureComponent>();
    render->changeOpacity(0);
    auto opacity = render->getOpacity();

    TweenComponent* t = addComponent<TweenComponent>(blackScreen);
    t->easeValue(opacity, 255, 4, tween::LINEAR, false, [=](){
        entity_t b = createSVGImage("win", "scoreSprite", "scoreSprite", true);
        createSVGImage("lose", "loseButtonText", "loseButtonText");
        // Vuelve a main scene
        b->getComponent<Button>()->setOnClick([this]()
        {
            game->getScenesManager()->invokeLose(); // vuelve a main scene
        }); 
    });
}

void EndGameScene::bossLose()
{
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

    dialogue->addDialogue("MUAHAHAHAHAHAUAHAUHAAAAAAAA", [=](){

    Entity* boss = new Entity(*this, grp::BOSS_SHADOW);
    b2Vec2 pos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").x, sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").y);
    auto tr = addComponent<TransformComponent>(boss, b2Vec2{2.f,2.f});
    tr->setRotation(25);
    Texture* bossImage = &sdlutils().images().at("cowboy_table_shadow"); // ! CAMBIAR A BOSS CURRENT

    float scale = sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").width/ (float)sdlutils().images().at("cowboy_table_shadow").width();
    addComponent<RenderTextureComponent>(boss, bossImage, renderLayer::BOSS_SHADOW, scale);

    auto tweens = addComponent<TweenComponent>(boss);
    tweens->easePosition(pos, .5f, tween::EASE_IN_OUT_CUBIC, false, [=](){
        addComponent<RandomVibrationComponent>(boss, .05f, 1.f);
    });

    });

    dialogue->addDialogue("Eres nuestro");
    dialogue->addDialogue("PARA SIEMPRE", [=](){
        standardLose();
    });

}
