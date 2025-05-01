#include "PauseScene.h"
#include "Entity.h"
#include "SDLUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "UnpauseComponent.h"
#include "TweenComponent.h"
#include "PhysicsUtils.h"
#include "InventoryManager.h"
#include "FollowComponent.h"
#include "StickInputComponent.h"

#include "ShadowComponent.h"

#include <iostream>
#include <fstream>
#include "BallInfoDisplayComponent.h"
#include "Button.h"

using body_t = BallInfoDisplayComponent::Body;

PauseScene::PauseScene(Game* g, GameScene* scene): GameScene(g){
    _bottomScene = scene;
    _ballIDs.reserve(InventoryManager::Instance()->MAX_BALLS);
    instantiateInventory();
}

void
PauseScene::instantiateInventory(){

    //fondo del cajon
    entity_t fondo = new Entity(*this, grp::UI);
    b2Vec2 initialPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer_initial_pos").x, sdlutils().height()/2);
    auto tr = addComponent<TransformComponent>(fondo, initialPos);

    float drawerScale =sdlutils().svgs().at("inventory").at("drawer").height/(float) sdlutils().images().at("drawer").getRect().h;

    addComponent<RenderTextureComponent>(fondo, &sdlutils().images().at("drawer"), renderLayer::BACKGROUND, drawerScale);
    auto tween = addComponent<TweenComponent>(fondo);

    //animacion
    b2Vec2 finalPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer").x, sdlutils().height()/2);
    tween->easePosition(finalPos, .5f, tween::EASE_OUT_ELASTIC, false, [=](){
        //UNPAUSE ENTITY
        Entity* unpause = new Entity(*this, grp::PAUSE_UNPAUSE);
        addComponent<UnpauseComponent>(unpause, tween);
    });
    
    std::ifstream f(InventoryManager::Instance()->pathToInventory);
    json data = json::parse(f);
    //balls
    float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;

    for(int i =0; i < InventoryManager::Instance()->MAX_BALLS; i++){
        std::string key = "ball_" + std::to_string(i+1);
        std::string slot = "slot" + std::to_string(i);

        
        std::string textureKey = "bola_blanca";
        if(data[slot]["components"][0]["atributes"]["effects"].size() >0){
            textureKey = data[slot]["components"][0]["atributes"]["effects"][0]["componentName"];
        }

        // We know which effect has the ball for its texture
        if(textureKey == "BowlingEffect") _ballIDs.push_back(BOWLING);
        else if(textureKey == "X2Effect") _ballIDs.push_back(X2);
        else if(textureKey == "AbacusEffect") _ballIDs.push_back(ABBACUS);
        else if(textureKey == "CristalEffect") _ballIDs.push_back(CRISTAL);
        else if(textureKey == "PetanqueEffect") _ballIDs.push_back(PETANQUE);
        else if(textureKey == "PokeballEffect") _ballIDs.push_back(POKEBALL);
        else if(textureKey == "QuanticEffect") _ballIDs.push_back(QUANTIC);
        else _ballIDs[i] = NORMAL;
    
        auto ballPos = sdlutils().svgs().at("inventory").at(key);
        auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");

        b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(ballPos.x - drawerPos.x), PhysicsConverter::pixel2meter(ballPos.y - drawerPos.y)};

        Entity* ball = new Entity(*this, grp::UI);

        addComponent<TransformComponent>(ball, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ball, &sdlutils().images().at(textureKey), renderLayer::EFFECT_BALL, ballScale);

        addComponent<FollowComponent>(ball, fondo, true, false, false, Vector2D(relativeDistance.x, relativeDistance.y));
        createBallShadow(ball);

        Button::TextureButton rButton = Button::TextureButton();
        auto button = addComponent<Button>(ball, rButton);

        button->setOnHover([this, i]() {
            #ifdef _DEBUG
            std::cout << "Hovering effect ball " << i << std::endl; 
            #endif

            showBall(i);
        });

        button->setOnExit([this, i]() {
            #ifdef _DEBUG
            std::cout << "Exiting effect ball " << i << std::endl; 
            #endif
    
                hideBall(i);
            });
    }

    //palo
    entity_t palo = InventoryManager::Instance()->getStick(*this);
    removeComponent<StickInputComponent>(palo);
    
    auto renderText = getComponent<RenderTextureComponent>(palo);
    float stickTextScale = renderText->getTexture()->width();
    float stickSVGScale = sdlutils().svgs().at("inventory").at("stick").width;
    float stickScale = stickSVGScale/stickTextScale;

    renderText->setScale(stickScale);

    auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");
    auto stickPos = sdlutils().svgs().at("inventory").at("stick");
    b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(stickPos.x - drawerPos.x), PhysicsConverter::pixel2meter(stickPos.y - drawerPos.y)};

    addComponent<FollowComponent>(palo, fondo, true, false, false, Vector2D(relativeDistance.x, relativeDistance.y));

    for(auto shadow : getComponent<ShadowComponent>(palo)->getShadows()){
        getComponent<RenderTextureComponent>(shadow)->setScale(stickScale);
        auto follow = getComponent<FollowComponent>(shadow);
        follow->setRelativeDistance(follow->getRelativeDistance()/2);
    }

    createBallInfo();
}

void
PauseScene::createBallInfo() {
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("inventory_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

    // Cargamos primero las bolas
    for(int i = 0; i < InventoryManager::Instance()->MAX_BALLS; ++i) {
        // FONDO
        description = new Entity(*this, grp::BALL_INFO_BG);

        auto svgElem = *&sdlutils().svgs().at("inventory").at("ball_Info_" + std::to_string(i));
        pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);
        pos.y -= 0.5;

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, 101, scale * 1.5f);

        description->deactivate();

        // TEXTO
        // Añadir texto de recompensa / TODO: texto de partida de boss
        // en función de _floorRewards[i]
        Text title, desc;

        switch(_ballIDs[i]){
            case BOWLING:
                title = sdlutils().texts().at("bowling_ballName_pool");
                desc = sdlutils().texts().at("bowling_ballDesc_pool");
                break;
            case X2:
                title = sdlutils().texts().at("x2_ballName_pool");
                desc = sdlutils().texts().at("x2_ballDesc_pool");
                break;
            case ABBACUS:
                title = sdlutils().texts().at("abbacus_ballName_pool");
                desc = sdlutils().texts().at("abbacus_ballDesc_pool");
                break;
            case CRISTAL:
                title = sdlutils().texts().at("cristal_ballName_pool");
                desc = sdlutils().texts().at("cristal_ballDesc_pool");
                break;
            case PETANQUE:
                title = sdlutils().texts().at("petanque_ballName_pool");
                desc = sdlutils().texts().at("petanque_ballDesc_pool");
                break;
            case POKEBALL:
                title = sdlutils().texts().at("poke_ballName_pool");
                desc = sdlutils().texts().at("poke_ballDesc_pool");
                break;
            case QUANTIC:
                title = sdlutils().texts().at("quantic_ballName_pool");
                desc = sdlutils().texts().at("quantic_ballDesc_pool");
                break;
            default:
                title = sdlutils().texts().at("normal_ballName_pool");
                desc = sdlutils().texts().at("normal_ballDesc_pool");
                break;
        }

        description = new Entity(*this, grp::BALL_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<BallInfoDisplayComponent>(description, 101, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{desc.text, desc.font, desc.color, scale*1.5f}
                , texture->width() * scale - 60
                , -texture->width()/2 * scale, -texture->height()/2 * scale
            );
        description->deactivate();
    }
}

void
PauseScene::showBall(int i) {

    auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
    descriptions[i]->activate();
}

void
PauseScene::hideBall(int i) {

    auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
    descriptions[i]->deactivate();
}

void PauseScene::render(){
    _bottomScene->render();
    GameScene::render();
}

void PauseScene::createBallShadow(entity_t entity){
    addComponent<ShadowComponent>(entity);
    ShadowComponent* comp = getComponent<ShadowComponent>(entity);

    //sombra de reflejo de la bola
    float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;

    comp->addShadow({0,0}, "bola_cast_sombra", renderLayer::BALL_SHADOW_ON_BALL, ballScale, true, false, true);

    //sombra de la bola
    float a_imgScale = sdlutils().images().at("bola_cast_sombra").width();

    float a_svg_scale = sdlutils().svgs().at("game").at("bola_cast_sombra 1").width;
    float normal_ball_scale = a_svg_scale/a_imgScale;
    float scaleFactor = ballScale/normal_ball_scale;

    //sombra de la bola
    a_imgScale = sdlutils().images().at("bola_sombra").width();
    a_svg_scale = sdlutils().svgs().at("game").at("bola_sombra 1").width;
    float cast_scale = a_svg_scale/a_imgScale;
    cast_scale *= scaleFactor;


    Vector2D a_relPos{
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").x - sdlutils().svgs().at("game").at("bola_sombra 1").x - 10) *scaleFactor,
        
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").y - sdlutils().svgs().at("game").at("bola_sombra 1").y)*scaleFactor
    };
    comp->addShadow({a_relPos.getX(), a_relPos.getY()}, "bola_sombra", renderLayer::BALL_SHADOW_ON_TABLE, cast_scale, true, false, true);

}