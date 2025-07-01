#include "RewardScene.h"
#include "ScenesManager.h"
#include "PoolScene.h"
#include "Inventory.h"

#include "SDLUtils.h"
#include "PhysicsUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "FollowComponent.h"
#include "StickInputComponent.h"
#include "ShadowComponent.h"
#include "RNG_Manager.h"

#include <iostream>
#include <fstream>
#include "BallInfoDisplayComponent.h"
#include "Button.h"


using body_t = BallInfoDisplayComponent::Body;

RewardScene::RewardScene(Game* game, Reward reward) 
    : UIScene(game)
    , _reward(reward)
    , _atReward(false)
{
}

RewardScene::~RewardScene() {
}

void RewardScene::atRender()
{
}

void RewardScene::render()
{
    // Para que se puede hacer el tween del cajon
    if(!_atReward) {
        atRender();
        _atReward = true;
    }

    GameScene::render();
}

void 
RewardScene::init() 
{
    RewardScene::initObjects(); // fondo comun a todas las escenas y boton continuar para salir

    initObjects();
    initFunctionalities();
    //showExitButton(); 
}

void 
RewardScene::initObjects() 
{
    // Background
    createBackground("suelo");
    createTable();

    // Pantalla negra con alpha
    entity_t blackScreen = createSVGImage("lose", "blackscreen", "blackscreen", false, grp::grpId::DEFAULT, renderLayer::UI_BACK);
    auto render = blackScreen->getComponent<RenderTextureComponent>();
    render->changeOpacity(100);

    // Texto de descripcion de recompensa
    // 
    int txtPosX = sdlutils().width()/2;

    std::string r0, rName, rType;
    r0 = "Recompensa";
    rName = _reward.translateName(_reward.getName());
    rType = _reward.translateType(_reward.getType());

    createText(r0, txtPosX, 80, 1.5, {255, 255, 255, 255}, renderLayer::UI);
    createText(rName, txtPosX, 150, 1.5, {102, 0, 0, 255}, renderLayer::UI);
    createText(rType, txtPosX, 220, 1.5, {194, 197, 204, 255}, renderLayer::UI);
    createText(rType, txtPosX, 220, 1.5, {194, 197, 204, 255}, renderLayer::UI);

    // Boton de continuar 
    _exitButton = createSVGImage("reward", "scoreSprite_center", "scoreSprite", 
        true, grp::DEFAULT, renderLayer::UI_MID);
    _exitButton->getComponent<Button>()->setOnClick([this]() { exitCallback(); });
    _exitButton->deactivate();

    // Texto del boton
    _exitBttText = createSVGImage("reward", "rewardButtonText_center", "rewardButtonText", false);
    _exitBttText->deactivate();
}

void
RewardScene::moveExitButtonToRight() 
{
    b2Vec2 pos = PhysicsConverter::pixel2meter(
    *&sdlutils().svgs().at("reward").at("scoreSprite_right").x,
    *&sdlutils().svgs().at("reward").at("scoreSprite_right").y
    );
    auto tr = _exitButton->getTransform();
    tr->setPosition(pos);

    // Texto del boton también se mueve a la derecha
    pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("reward").at("rewardButtonText_right").x,
        *&sdlutils().svgs().at("reward").at("rewardButtonText_right").y
    );
    tr = _exitBttText->getTransform();
    tr->setPosition(pos);
}

void 
RewardScene::showExitButton() 
{
    _exitButton->activate();
    _exitBttText->activate();
}

void 
RewardScene::hideExitButton() 
{
    _exitButton->deactivate();
    _exitBttText->deactivate();
}

// Applies reward y sale de reward scene
void 
RewardScene::exitCallback()
{
    applyReward();

    game->getScenesManager()->popScene(); // Poppea esta escena
    // vuelve a poolscene
    if(_reward.getType() == Reward::Type::BOSS) {
        game->getScenesManager()->popScene(); // popea poolscene
        game->getProgressionManager()->anteUp();
        game->getScenesManager()->pushScene(std::make_shared<PoolScene>(game)); // Nueva PoolScene
    }
}

/// @brief Crea todos los carteles con la info de las bolas y los esconde. También añade eventos para mostrarlos al pasar el ratón por encima
// void
// RewardScene::createBallInfo() {
//     entity_t description;
//     b2Vec2 pos;

//     auto texture = &sdlutils().images().at("inventory_description_box");
//     float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

//     // Cargamos primero las bolas
//     for(int i = 0; i < InventoryManager::Instance()->MAX_BALLS; ++i) {
//         // FONDO
//         description = new Entity(*this, grp::BALL_INFO_BG);

//         auto svgElem = *&sdlutils().svgs().at("inventory").at("ball_Info_" + std::to_string(i));
//         pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);
//         pos.y -= 0.5;

//         addComponent<TransformComponent>(description, pos);
//         addComponent<RenderTextureComponent>(description, texture, 101, scale * 1.5f);

//         description->deactivate();

//         // TEXTO
//         // Añadir texto de recompensa / TODO: texto de partida de boss
//         // en función de _floorRewards[i]
//         Text title, desc;

//         switch(_ballIDs[i]){
//             case BOWLING:
//                 title = sdlutils().texts().at("bowling_ballName_pool");
//                 desc = sdlutils().texts().at("bowling_ballDesc_pool");
//                 break;
//             case X2:
//                 title = sdlutils().texts().at("x2_ballName_pool");
//                 desc = sdlutils().texts().at("x2_ballDesc_pool");
//                 break;
//             case ABBACUS:
//                 title = sdlutils().texts().at("abbacus_ballName_pool");
//                 desc = sdlutils().texts().at("abbacus_ballDesc_pool");
//                 break;
//             case CRISTAL:
//                 title = sdlutils().texts().at("cristal_ballName_pool");
//                 desc = sdlutils().texts().at("cristal_ballDesc_pool");
//                 break;
//             case PETANQUE:
//                 title = sdlutils().texts().at("petanque_ballName_pool");
//                 desc = sdlutils().texts().at("petanque_ballDesc_pool");
//                 break;
//             case POKEBALL:
//                 title = sdlutils().texts().at("poke_ballName_pool");
//                 desc = sdlutils().texts().at("poke_ballDesc_pool");
//                 break;
//             case QUANTIC:
//                 title = sdlutils().texts().at("quantic_ballName_pool");
//                 desc = sdlutils().texts().at("quantic_ballDesc_pool");
//                 break;
//             default:
//                 title = sdlutils().texts().at("normal_ballName_pool");
//                 desc = sdlutils().texts().at("normal_ballDesc_pool");
//                 break;
//         }

//         description = new Entity(*this, grp::BALL_INFO_TEXT);
//         addComponent<TransformComponent>(description, pos);
//         addComponent<BallInfoDisplayComponent>(description, 101, 
//                 body_t{title.text, title.font, title.color, scale*1.5f},
//                 body_t{desc.text, desc.font, desc.color, scale*1.5f}
//                 , texture->width() * scale - 60
//                 , -texture->width()/2 * scale, -texture->height()/2 * scale
//             );
//         description->deactivate();
//     }
// }

// /// @brief Crea el cartel con la info del palo y lo esconde. También añade eventos para mostrarlo al pasar el ratón por encima
// void RewardScene::createStickInfo(){
//     entity_t description;
//     b2Vec2 pos;

//     auto texture = &sdlutils().images().at("inventory_description_box");
//     float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

//     // FONDO
//     description = new Entity(*this, grp::STICK_INFO_BG);

//     auto svgElem = *&sdlutils().svgs().at("inventory").at("stick_info");
//     pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);
//     pos.y -= 0.5;

//     addComponent<TransformComponent>(description, pos);
//     addComponent<RenderTextureComponent>(description, texture, 101, scale * 1.5f);

//     description->deactivate();

//     // TEXTO
//     // Añadir texto de recompensa / TODO: texto de partida de boss
//     // en función de _floorRewards[i]
//     Text title, desc;

//     switch(_stickID){
//         case GRENADE:
//             title = sdlutils().texts().at("grenade_stickName_pool");
//             desc = sdlutils().texts().at("grenade_stickDesc_pool");
//             break;
//         case DONUT:
//             title = sdlutils().texts().at("donut_stickName_pool");
//             desc = sdlutils().texts().at("donut_stickDesc_pool");
//             break;
//         case BOXING:
//             title = sdlutils().texts().at("boxing_stickName_pool");
//             desc = sdlutils().texts().at("boxing_stickDesc_pool");
//             break;
//         case WAND:
//             title = sdlutils().texts().at("wand_stickName_pool");
//             desc = sdlutils().texts().at("wand_stickDesc_pool");
//             break;
//         default:
//             title = sdlutils().texts().at("normal_stickName_pool");
//             desc = sdlutils().texts().at("normal_stickDesc_pool");
//             break;
//         }

//         description = new Entity(*this, grp::STICK_INFO_TEXT);
//         addComponent<TransformComponent>(description, pos);
//         addComponent<BallInfoDisplayComponent>(description, 101, 
//                 body_t{title.text, title.font, title.color, scale*1.5f},
//                 body_t{desc.text, desc.font, desc.color, scale*1.5f}
//                 , texture->width() * scale - 60
//                 , -texture->width()/2 * scale, -texture->height()/2 * scale
//             );
//         description->deactivate();
// }

/// @brief muestra la info de determinada bola
/// @param i el id de la bola cuya info que queremos enseñar
// void
// RewardScene::showBall(int i) {

//     auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
//     descriptions[i]->activate();

//     descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
//     descriptions[i]->activate();
// }

/// @brief esconde la info de determinada bola
/// @param i el id de la bola cuya info que queremos esconder
// void
// RewardScene::hideBall(int i) {

//     auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
//     descriptions[i]->deactivate();

//     descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
//     descriptions[i]->deactivate();
// }

// /// @brief scrollea por los distintos efecto de las bolas
// /// @param i id de la bola sobre la que se está mostrando info
// void 
// RewardScene::scrollBall(int i)
// {
//     // if(_obtainedBallsInfo[i].scrollIndex == (_obtainedBallsInfo[i].effects.size() - 1)) _obtainedBallsInfo[i].scrollIndex = 0;
//     // else _obtainedBallsInfo[i].scrollIndex += 1; //No pongo ++ porque se me hacía ilegible
    
//     // std::string ballEffect = PoolScene::getEffectName(_obtainedBallsInfo[i].effects[_obtainedBallsInfo[i].scrollIndex]);
    
//     // auto texture = &sdlutils().images().at("reward_description_box");
//     // float scale = static_cast<float>(*&sdlutils().svgs().at("reward").at("boss_reward_info").width) / texture->width();

//     // Text ballName = sdlutils().texts().at(ballEffect + "_name_pool");
//     // Text ballDesc = sdlutils().texts().at(ballEffect + "_desc_pool");

//     // body_t nameBody = {ballName.text, ballName.font, ballName.color, scale * 1.5f};
//     // _effectRewardBoxes[i]->setRewardType(nameBody);

//     // body_t descBody = {ballDesc.text, ballDesc.font, ballDesc.color, scale * 2.0f};
//     // _effectRewardBoxes[i]->setRewardDesc(descBody);
// }

// /// @brief muestra la info del palo
// void
// RewardScene::showStick(){
//     auto stickInfo = getEntitiesOfGroup(grp::STICK_INFO_BG);
//     stickInfo[0]->activate();

//     stickInfo = getEntitiesOfGroup(grp::STICK_INFO_TEXT);
//     stickInfo[0]->activate();
// }

// /// @brief esconde la info del palo
// void
// RewardScene::hideStick(){
//     auto stickInfo = getEntitiesOfGroup(grp::STICK_INFO_BG);
//     stickInfo[0]->deactivate();

//     stickInfo = getEntitiesOfGroup(grp::STICK_INFO_TEXT);
//     stickInfo[0]->deactivate();
// }

// void RewardScene::createBallShadow(entity_t entity){
//     addComponent<ShadowComponent>(entity);
//     ShadowComponent* comp = getComponent<ShadowComponent>(entity);

//     //sombra de reflejo de la bola
//     float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;

//     comp->addShadow({0,0}, "bola_cast_sombra", renderLayer::BALL_SHADOW_ON_BALL, ballScale, true, false, true);

//     //sombra de la bola
//     float a_imgScale = sdlutils().images().at("bola_cast_sombra").width();

//     float a_svg_scale = sdlutils().svgs().at("game").at("bola_cast_sombra 1").width;
//     float normal_ball_scale = a_svg_scale/a_imgScale;
//     float scaleFactor = ballScale/normal_ball_scale;

//     //sombra de la bola
//     a_imgScale = sdlutils().images().at("bola_sombra").width();
//     a_svg_scale = sdlutils().svgs().at("game").at("bola_sombra 1").width;
//     float cast_scale = a_svg_scale/a_imgScale;
//     cast_scale *= scaleFactor;


//     Vector2D a_relPos{
//         PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").x - sdlutils().svgs().at("game").at("bola_sombra 1").x - 10) *scaleFactor,
        
//         PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").y - sdlutils().svgs().at("game").at("bola_sombra 1").y)*scaleFactor
//     };
//     comp->addShadow({a_relPos.getX(), a_relPos.getY()}, "bola_sombra", renderLayer::BALL_SHADOW_ON_TABLE, cast_scale, true, false, true);

// }