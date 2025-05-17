#include "RewardScene.h"
#include "ScenesManager.h"
#include "PoolScene.h"
#include "InventoryManager.h"

#include "SDLUtils.h"
#include "PhysicsUtils.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "UnpauseComponent.h"
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
    //
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
    //
    _exitButton = createSVGImage("win", "scoreSprite", "scoreSprite", true);
    _exitButton->getComponent<Button>()->setOnClick([this]() { exitCallback(); });
    _exitButton->deactivate();
    // Texto del boton
    _exitBttText = createSVGImage("win", "rewardButtonText", "rewardButtonText", false);
    _exitBttText->deactivate();
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

std::vector<RewardScene::ButtonWithSlot> 
RewardScene::openInventory()
{
    std::vector<RewardScene::ButtonWithSlot> a_returnVal;

    //fondo del cajon
    entity_t fondo = new Entity(*this, grp::UI);
    b2Vec2 initialPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer_initial_pos").x, sdlutils().height()/2);
    auto tr = addComponent<TransformComponent>(fondo, initialPos);

    float drawerScale =sdlutils().svgs().at("inventory").at("drawer").height/(float) sdlutils().images().at("drawer").getRect().h;

    addComponent<RenderTextureComponent>(fondo, &sdlutils().images().at("drawer"), renderLayer::CAJON, drawerScale);
    auto tween = addComponent<TweenComponent>(fondo);

    //animacion
    b2Vec2 finalPos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("inventory").at("drawer").x, sdlutils().height()/2);
    tween->easePosition(finalPos, 5.0f, tween::EASE_OUT_ELASTIC, false, [=](){
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

        //si no existe la bola en el slot i, no se renderiza
        if(data.find(slot) == data.end()) {
            _ballIDs.push_back(NORMAL_BALL);
            continue;
        }

        std::string textureKey = "bola_blanca";
        if(data[slot]["components"][0]["atributes"]["effects"].size() >0){
            textureKey = data[slot]["components"][0]["atributes"]["effects"][0]["componentName"];
            textureKey = "single_" + textureKey;
        }

        // We know which effect has the ball for its texture
        if(textureKey == "single_BowlingEffect") _ballIDs.push_back(BOWLING);
        else if(textureKey == "single_X2Effect") _ballIDs.push_back(X2);
        else if(textureKey == "single_AbacusEffect") _ballIDs.push_back(ABBACUS);
        else if(textureKey == "single_CristalEffect") _ballIDs.push_back(CRISTAL);
        else if(textureKey == "single_PetanqueEffect") _ballIDs.push_back(PETANQUE);
        else if(textureKey == "single_PokeballEffect") _ballIDs.push_back(POKEBALL);
        else if(textureKey == "single_QuanticEffect") _ballIDs.push_back(QUANTIC);
        else _ballIDs.push_back(NORMAL_BALL);
    
        auto ballPos = sdlutils().svgs().at("inventory").at(key);
        auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");

        b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(ballPos.x - drawerPos.x), PhysicsConverter::pixel2meter(ballPos.y - drawerPos.y)};

        Entity* ball = new Entity(*this, grp::UI);

        addComponent<TransformComponent>(ball, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ball, &sdlutils().images().at(textureKey), renderLayer::EFFECT_BALL, ballScale);

        if(textureKey == "bola_blanca"){
            //colores
            auto color = sdlutils().inventorySlotColor[i];
            ball->getRenderer()->changeColorTint(color.r, color.g, color.b);
        }

        addComponent<FollowComponent>(ball, fondo, true, false, false, Vector2D(relativeDistance.x, -relativeDistance.y));
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

        ButtonWithSlot b;
        b.button = button;
        b.slot = i;

        a_returnVal.push_back(b);
    }

    //palo
    entity_t palo = InventoryManager::Instance()->getStick(*this);
    removeComponent<StickInputComponent>(palo);
    
    auto renderText = getComponent<RenderTextureComponent>(palo);
    float stickTextScale = renderText->getTexture()->width();
    float stickSVGScale = sdlutils().svgs().at("inventory").at("stick").width;
    float stickScale = stickSVGScale/stickTextScale;

    renderText->setScale(stickScale);

    auto stickTextKey = data["stick"]["components"][0]["componentName"];

    if(stickTextKey == "DonutStickEffect") _stickID = DONUT;
    else if(stickTextKey == "MagicWandStickEffect") _stickID = WAND;
    else if(stickTextKey == "BoxingGloveStickEffect") _stickID = BOXING;
    else if(stickTextKey == "GrenadeLauncherStickEffect") _stickID = GRENADE;
    else _stickID = NORMAL_STICK;

    auto drawerPos = sdlutils().svgs().at("inventory").at("drawer");
    auto stickPos = sdlutils().svgs().at("inventory").at("stick");
    b2Vec2 relativeDistance = {PhysicsConverter::pixel2meter(stickPos.x - drawerPos.x), PhysicsConverter::pixel2meter(stickPos.y - drawerPos.y)};

    addComponent<FollowComponent>(palo, fondo, true, false, false, Vector2D(relativeDistance.x, relativeDistance.y));

    for(auto shadow : getComponent<ShadowComponent>(palo)->getShadows()){
        getComponent<RenderTextureComponent>(shadow)->setScale(stickScale);
        auto follow = getComponent<FollowComponent>(shadow);
        follow->setRelativeDistance(follow->getRelativeDistance()/2);
    }

    Button::TextureButton rButton = Button::TextureButton();
    auto button = addComponent<Button>(palo, rButton);

    button->setOnHover([this]() {
        #ifdef _DEBUG
        std::cout << "Hovering stick " << std::endl; 
        #endif

        showStick();
    });

    button->setOnExit([this]() {
        #ifdef _DEBUG
        std::cout << "Exiting stick" << std::endl; 
        #endif
    
        hideStick();
    });

    createBallInfo();
    createStickInfo();

    ButtonWithSlot b;
    b.button = button;
    b.slot = 0;
    a_returnVal.push_back(b);

    return a_returnVal;
}

/// @brief Crea todos los carteles con la info de las bolas y los esconde. También añade eventos para mostrarlos al pasar el ratón por encima
void
RewardScene::createBallInfo() {
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

/// @brief Crea el cartel con la info del palo y lo esconde. También añade eventos para mostrarlo al pasar el ratón por encima
void RewardScene::createStickInfo(){
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("inventory_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("inventory").at("ball_Info_0").width) / texture->width();

    // FONDO
    description = new Entity(*this, grp::STICK_INFO_BG);

    auto svgElem = *&sdlutils().svgs().at("inventory").at("stick_info");
    pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);
    pos.y -= 0.5;

    addComponent<TransformComponent>(description, pos);
    addComponent<RenderTextureComponent>(description, texture, 101, scale * 1.5f);

    description->deactivate();

    // TEXTO
    // Añadir texto de recompensa / TODO: texto de partida de boss
    // en función de _floorRewards[i]
    Text title, desc;

    switch(_stickID){
        case GRENADE:
            title = sdlutils().texts().at("grenade_stickName_pool");
            desc = sdlutils().texts().at("grenade_stickDesc_pool");
            break;
        case DONUT:
            title = sdlutils().texts().at("donut_stickName_pool");
            desc = sdlutils().texts().at("donut_stickDesc_pool");
            break;
        case BOXING:
            title = sdlutils().texts().at("boxing_stickName_pool");
            desc = sdlutils().texts().at("boxing_stickDesc_pool");
            break;
        case WAND:
            title = sdlutils().texts().at("wand_stickName_pool");
            desc = sdlutils().texts().at("wand_stickDesc_pool");
            break;
        default:
            title = sdlutils().texts().at("normal_stickName_pool");
            desc = sdlutils().texts().at("normal_stickDesc_pool");
            break;
        }

        description = new Entity(*this, grp::STICK_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<BallInfoDisplayComponent>(description, 101, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{desc.text, desc.font, desc.color, scale*1.5f}
                , texture->width() * scale - 60
                , -texture->width()/2 * scale, -texture->height()/2 * scale
            );
        description->deactivate();
}

/// @brief muestra la info de determinada bola
/// @param i el id de la bola cuya info que queremos enseñar
void
RewardScene::showBall(int i) {

    auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
    descriptions[i]->activate();
}

/// @brief esconde la info de determinada bola
/// @param i el id de la bola cuya info que queremos esconder
void
RewardScene::hideBall(int i) {

    auto descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
    descriptions[i]->deactivate();
}

/// @brief muestra la info del palo
void
RewardScene::showStick(){
    auto stickInfo = getEntitiesOfGroup(grp::STICK_INFO_BG);
    stickInfo[0]->activate();

    stickInfo = getEntitiesOfGroup(grp::STICK_INFO_TEXT);
    stickInfo[0]->activate();
}

/// @brief esconde la info del palo
void
RewardScene::hideStick(){
    auto stickInfo = getEntitiesOfGroup(grp::STICK_INFO_BG);
    stickInfo[0]->deactivate();

    stickInfo = getEntitiesOfGroup(grp::STICK_INFO_TEXT);
    stickInfo[0]->deactivate();
}

void RewardScene::createBallShadow(entity_t entity){
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


// selecciona una bola del cajon
void RewardScene::selectBall(int i) {

}

// cambia el stick actual por reward
void RewardScene::changeStick(int i) {

}