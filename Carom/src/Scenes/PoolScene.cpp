#include "PoolScene.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RewardInfoDisplayComponent.h"
#include "RigidBodyComponent.h"
#include "ColorHitManager.h"
#include "Entity.h"
#include "Button.h"
#include "PhysicsUtils.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "CaromScene.h"
#include "CowboyPoolScene.h"
#include "RussianPyramidScene.h" 

#include "InventoryManager.h"

#include "RewardScene.h"
#include "CowboyPoolScene.h"
#include "StickInputComponent.h"
#include "TweenComponent.h"
#include "ProgressionManager.h"

#include "BallHandler.h"

#include "AudioManager.h"
// #include ...Reward.h
#include "DialogueTextComponent.h"
#include "TextDisplayComponent.h"
#include "RandomVibrationComponent.h"
#include "WobblyRenderTextureComponent.h"

// --- ball effects ---
#include "AbacusEffect.h"
#include "BowlingEffect.h"
#include "CristalEffect.h"
#include "ExplosiveEffect.h"
#include "FrictionMultiplierEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "PopToOppositeSideEffect.h"
#include "QuanticEffect.h"
#include "SubdivisionEffect.h"
#include "X2Effect.h"
#include "BallEffect.h"

#include "StickRewardScene.h"
#include "FusionRewardScene.h"
#include "PermanentRewardScene.h"
#include "BossRewardScene.h"
#include "CauldronRewardScene.h"

// hola

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>

#include <iostream>


using body_t = RewardInfoDisplayComponent::Body;

PoolScene::PoolScene(Game* game) 
    : UIScene(game)
    , _rngm(RNG_Manager::Instance())
{
}

PoolScene::~PoolScene()
{
    #ifdef _DEBUG
    std::cout << "DESTRUCTOR POOLSCENE" << std::endl;
    #endif
    // Como son shareds los punteros ya no hace falta esta movida
}

void PoolScene::initObjects()
{
    createPauseEntity();

    // Create table with texture and colliders
    createBackground("suelo");
    createTable();
    createCurrentFloorUI();

    getEntitiesOfGroup(grp::TABLE_BACKGROUND)[0]->getComponent<RenderTextureComponent>()->changeColorTint(0, 255, 0);

    initRandomEffects();

    generateMatchHoles();
    generateBalls();
    generateFloorRewards();
    createBallInfoText();

    createCallbacks();
    setBossBallTexture();

    AudioManager::Instance()->changeToPauseTheme();
}

void PoolScene::generateMatchHoles()
{
    // Entre 0 y posiciones-1 elige un indice para que sea el boss.
    _bossHole = _rngm->randomRange(0, POSITIONS);
    #ifdef _DEBUG
    std::cout << "Boss hole: " << _bossHole << std::endl;
    #endif

    // coloca los agujeros de partida
    for(int i = 0; i < POSITIONS; i++){
        entity_t hole = generateHole(i);

        _holes.push_back(hole);
    }
}

entity_t 
PoolScene::generateHole(int i)
{
    // agujero.
    entity_t e = new Entity(*this, grp::POOL_HOLE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).x,
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).y
    );

    float scale = float(sdlutils().svgs().at("pool").at("hole 0").width) / float(sdlutils().images().at("hole").width());

    addComponent<TransformComponent>(e, pos);
    auto renderComp = addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    // color tint rojo en el agujero si es boss
    if (i == _bossHole)
        renderComp->changeColorTint(255, 0, 0);
        
    return e;
}

void PoolScene::setBossBallTexture(){
    auto bossBall = getEntitiesOfGroup(grp::POOL_BALLS)[_bossHole];
    
    bossBall->getComponent<RenderTextureComponent>()->setTexture(&sdlutils().images().at("boss_ball"));
}

void
PoolScene::chooseRewards(std::vector<RewardScene::Reward>& possibleRewards, int amount) {
    std::vector<RandomItem<RewardScene::Reward>> randomRewards;
    
    for(int i = 0; i < possibleRewards.size(); ++i) {
        randomRewards.push_back(RandomItem<RewardScene::Reward>(possibleRewards[i], 1.0f));
    }

    possibleRewards = _rngm->getRandomItems(randomRewards, amount, false);
}

void
PoolScene::generateFloorRewards() {

    _floorRewards.push_back(RewardScene::Reward("cunning", RewardScene::Reward::Type::PERMANENT));
    _floorRewards.push_back(RewardScene::Reward("skill", RewardScene::Reward::Type::PERMANENT));
    _floorRewards.push_back(RewardScene::Reward("charisma", RewardScene::Reward::Type::PERMANENT));
    _floorRewards.push_back(RewardScene::Reward("power", RewardScene::Reward::Type::PERMANENT));
    _floorRewards.push_back(RewardScene::Reward("fusion", RewardScene::Reward::Type::INSTANT));
    _floorRewards.push_back(RewardScene::Reward("stick", RewardScene::Reward::Type::INSTANT));
    _floorRewards.push_back(RewardScene::Reward("cauldron", RewardScene::Reward::Type::INSTANT));

    chooseRewards(_floorRewards, POSITIONS);

    // Swaps boss hole assigned reward for a Boss Reward
    _floorRewards[_bossHole] = RewardScene::Reward("boss", RewardScene::Reward::Type::BOSS);
    #ifdef _DEBUG
    std::cout << "floorrewards size: " << _floorRewards.size() << std::endl;
    #endif

    createRewardInfo();
}

void
PoolScene::createRewardInfo() {
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("pool").at("box_0").width) / texture->width();

    for(int i = 0; i < POSITIONS; ++i) {
        // FONDO
        description = new Entity(*this, grp::REWARD_INFO_BG);

        auto svgElem = *&sdlutils().svgs().at("pool").at("box_" + std::to_string(i));
        pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale);

        description->deactivate();

        // TEXTO
        Text title, rewardName, rewardType, rewardDesc;

        switch(_floorRewards[i].getType()) {
            case RewardScene::Reward::Type::INSTANT:
                title = sdlutils().texts().at("rewardTitle_pool");
                rewardType = sdlutils().texts().at("instantReward_pool");
                break;
            case RewardScene::Reward::Type::PERMANENT:
                title = sdlutils().texts().at("rewardTitle_pool");
                rewardType = sdlutils().texts().at("permanentReward_pool");
                break;
            case RewardScene::Reward::Type::BOSS:
                title = sdlutils().texts().at("bossTitle_pool");
                rewardType = sdlutils().texts().at("bossReward_pool");
                break;
            default:
                title = sdlutils().texts().at("rewardTitle_pool");
                rewardType = sdlutils().texts().at("reward_pool");
                break;
        }

        rewardName = sdlutils().texts().at(_floorRewards[i].getName()+"_rewardName_pool");
        rewardDesc = sdlutils().texts().at(_floorRewards[i].getName()+"_rewardDesc_pool");
        

        description = new Entity(*this, grp::REWARD_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<RewardInfoDisplayComponent>(description, renderLayer::UI, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{rewardName.text, rewardName.font, rewardName.color, scale*1.5f},
                body_t{rewardType.text, rewardType.font, rewardType.color, scale*2.f},
                body_t{rewardDesc.text, rewardDesc.font, rewardDesc.color, scale*2.f}
                , texture->width() * scale - 25
                , -texture->width()/2 * scale + 15, -texture->height()/2 * scale + 35
            );
        description->deactivate();
    }
}

void
PoolScene::showReward(int i) {
    assert(i < POSITIONS);

    auto descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->activate();
}

void
PoolScene::hideReward(int i) {
    assert(i < POSITIONS);

    auto descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->deactivate();
}

std::string 
PoolScene::randomBallEffect()
{
    // TODO: hacer los random ball effects pero con el BallCompsInfo.
    int n = _rngm->randomRange(0, 7); // numero aleatorio entre 0 y 7.
    std::string be;
    switch (n) {
        case 0: be = "ABACUS_EFFECT"; break;
        case 1: be = "BOWLING_EFFECT"; break;
        case 2: be = "CRISTAL_EFFECT"; break;
        case 3: be = "PETANQUE_EFFECT"; break;
        case 4: be = "POKEBALL_EFFECT"; break;
        case 5: be = "QUANTIC_EFFECT"; break;
        case 6: be = "X2_EFFECT"; break;
        default: break;
    }

    return be;
}

void 
PoolScene::generateBalls()
{
    // coloca los agujeros de partida
    for(int i = 0; i < POSITIONS; i++) {
        // genera la bola
        entity_t ball = createSVGImage(
            "ballspool",                 // svg
            "bola_" + std::to_string(i), // tag
            getTextureName(_ballsInfo[i].effects[0]),              // image
            true,                        // button
            grp::POOL_BALLS,             // group
            renderLayer::WHITE_BALL      // renderlayer
        );
        addComponent<TweenComponent>(ball);
        
        _balls.push_back(ball);
    }
}

void 
PoolScene::createBallInfoText()
{
    entity_t description;
    b2Vec2 pos;

    Texture* texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("ballspool").at("bolamsg_0").width) / texture->width();
    // TODO: al ballspool accede bien
    

    for(int i = 0; i < POSITIONS; ++i) {
        // --- FONDO
        description = new Entity(*this, grp::BALL_INFO_BG);

        pos = PhysicsConverter::pixel2meter(
            *&sdlutils().svgs().at("ballspool").at("bolamsg_" + std::to_string(i)).x, 
            *&sdlutils().svgs().at("ballspool").at("bolamsg_" + std::to_string(i)).y
        );

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale);

        description->deactivate();

        
        // --- TEXTO
        Text title, ballName, ballDesc, ballType;

        title = sdlutils().texts().at("ballEffectTitle_pool");

        bool isBoss = i == _bossHole;
        std::string ballEffect;
        if(!isBoss) ballEffect = getEffectName(_ballsInfo[i].effects[0]);
        else ballEffect = "boss";

        ballName = sdlutils().texts().at(ballEffect + "_name_pool");
        ballDesc = sdlutils().texts().at(ballEffect + "_desc_pool");
        ballType = sdlutils().texts().at("ballEffectType_pool");

        // usa rewardInfoDisplayComponent porque en esencia es para lo mismo.
        description = new Entity(*this, grp::BALL_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        RewardInfoDisplayComponent* a_desc = addComponent<RewardInfoDisplayComponent>(description, renderLayer::UI, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{ballType.text, ballType.font, ballType.color, scale*2.f},
                body_t{ballName.text, ballName.font, ballName.color, scale*1.5f},
                body_t{ballDesc.text, ballDesc.font, ballDesc.color, scale*2.f}
                , texture->width() * scale - 25
                , -texture->width()/2 * scale + 15, -texture->height()/2 * scale + 35
            );
        description->deactivate();

        _effectRewardBoxes.push_back(a_desc);
    }
}

void 
PoolScene::showBallEffect(int i)
{
    assert(i < POSITIONS);

    std::vector<entity_t> descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
    descriptions[i]->activate();
}

void 
PoolScene::hideBallEffect(int i)
{
    assert(i < POSITIONS);

    std::vector<entity_t> descriptions = getEntitiesOfGroup(grp::BALL_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::BALL_INFO_TEXT);
    descriptions[i]->deactivate();
}

void 
PoolScene::scrollBallEffect(int i) {
    
    if(_ballsInfo[i].scrollIndex == (_ballsInfo[i].effects.size() - 1)) _ballsInfo[i].scrollIndex = 0;
    else _ballsInfo[i].scrollIndex += 1; //No pongo ++ porque se me hacía ilegible
    
    std::string ballEffect = getEffectName(_ballsInfo[i].effects[_ballsInfo[i].scrollIndex]);
    
    auto texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("ballspool").at("bolamsg_0").width) / texture->width();

    Text ballName = sdlutils().texts().at(ballEffect + "_name_pool");
    Text ballDesc = sdlutils().texts().at(ballEffect + "_desc_pool");

    body_t nameBody = {ballName.text, ballName.font, ballName.color, scale * 1.5f};
    _effectRewardBoxes[i]->setRewardType(nameBody);

    body_t descBody = {ballDesc.text, ballDesc.font, ballDesc.color, scale * 2.0f};
    _effectRewardBoxes[i]->setRewardDesc(descBody);
}

void
PoolScene::createCallbacks() {
    CaromScene::Boss floorBoss = (CaromScene::Boss)game->getProgressionManager()->getNextBoss();

    for(int i = 0; i < POSITIONS; ++i) {
        Button* holeButton = getComponent<Button>(_holes[i]);
        Button* ballButton = getComponent<Button>(_balls[i]);

        TweenComponent* tween = getComponent<TweenComponent>(_balls[i]);

        bool isBoss = i == _bossHole;
        holeButton->setOnClick([=](){
            hideReward(i);
            hideBallEffect(i);
            tween->easePosition(_holes[i]->getTransform()->getPosition(), 0.5f, tween::EASE_IN_OUT_CUBIC, false, [=]{


                _balls[i]->setAlive(false); // Quita la bola si se ha jugado la partida.
                _ballsInfo[i].free = false;
    
                std::shared_ptr<CaromScene> ms = nullptr;

                switch (floorBoss)
                {
                    case CaromScene::Boss::COWBOY_POOL:
                    {
                        ms = std::make_shared<CowboyPoolScene>(game, isBoss);
                        break;
                    }
                    case CaromScene::Boss::RUSSIAN_PYRAMID:
                    {
                        ms = std::make_shared<RussianPyramidScene>(game, isBoss);
                        break;
                    }
                    default:
                    {
                        ms = std::make_shared<CowboyPoolScene>(game, isBoss);
                        #ifdef _DEBUG
                        std::cout << "Error: no se ha podido cargar la escena de boss, cargando boss por defecto" << std::endl;
                        #endif
                        break;
                    }
                }
                
                auto rs = createRewardScene(_floorRewards[i]);
                game->getScenesManager()->pushScene(rs);
                game->getScenesManager()->pushScene(ms);

                holeButton->setOnClick([=]{});
                holeButton->setOnHover([=]{});
                hideBallEffect(i);
            });
        });

        holeButton->setOnHover([this, i]() {
            showReward(i);
        });

        holeButton->setOnExit([this, i]() {
            hideReward(i);
        });
        
        ballButton->setOnHover([this, i]() {
             showBallEffect(i);
        });

        ballButton->setOnExit([this, i]() {
             hideBallEffect(i);
        });

        ballButton->setOnRightClick([this, i]() {
            if(i == _bossHole) return;
            scrollBallEffect(i);
        });

    }
}

void 
PoolScene::initRandomEffects() {
    _ballsInfo = std::vector<BallInfo>(POSITIONS);
    std::vector<RandomItem<BallId>> allEffects;
    constexpr float equalChance = 1.0 / int(NUM_BALLS);

    for(int i = 0; i < POSITIONS; ++i) {
        for(int i = 1; i < NUM_BALLS; ++i) allEffects.push_back({BallId(i), equalChance});
        addNewEffect(i, 1.0f, allEffects);
    }
}

void 
PoolScene::addNewEffect(int index, float chance, std::vector<RandomItem<BallId>>& possibleEffects) {
    if(_rngm->randomRange(0.0f, 1.0f) >= chance) return;

    if(possibleEffects.size() == 0) return;
    _ballsInfo[index].effects.push_back(_rngm->getRandomItem(possibleEffects, true));

    addNewEffect(index, _chanceForMultipleEffect, possibleEffects);
}

std::string 
PoolScene::getTextureName(BallId effect) {
    return "single_" + getEffectName(effect);
}

std::string 
PoolScene::getEffectName(BallId effect) {
    switch(effect){
        case ABBACUS: return "AbacusEffect";
        case BOWLING: return "BowlingEffect";
        case CRISTAL: return "CristalEffect";
        case PETANQUE: return "PetanqueEffect";
        case POKEBALL: return "PokeballEffect";
        case QUANTIC: return "QuanticEffect";
        case X2: return "X2Effect";
        default: return "";
    }
}

void
PoolScene::createCurrentFloorUI() {

    int currFloor = game->getProgressionManager()->getAnte();

    entity_t floorFrameObject = new Entity(*this, grp::SCORE);

    auto floorSVG = sdlutils().svgs().at("pool").at("floor");
    float floorSVGSize = floorSVG.width;
    float textureSize = sdlutils().images().at("floor").width();
    float scale = floorSVGSize / textureSize;

    b2Vec2 framePos = PhysicsConverter::pixel2meter( floorSVG.x, floorSVG.y );

    floorFrameObject->addComponent(new TransformComponent(floorFrameObject, framePos));
    floorFrameObject->addComponent(new RenderTextureComponent(floorFrameObject, &sdlutils().images().at("floor"), renderLayer::UI, scale));
    entity_t floorObject = new Entity(*this, grp::SCORE);

    auto shotsLeftText = sdlutils().svgs().at("pool").at("floor");
    b2Vec2 textPos = PhysicsConverter::pixel2meter( floorSVG.x, floorSVG.y );

    floorObject->addComponent(new TransformComponent(floorObject, textPos));
    TextDisplayComponent* floorDisplay = new TextDisplayComponent(floorObject, renderLayer::UI, 1.0, 
        std::to_string(currFloor), {255, 255, 255, 255}, "Basteleur-Bold72");
    floorObject->addComponent(floorDisplay);

    addComponent<TweenComponent>(floorObject);
}

std::shared_ptr<RewardScene> 
PoolScene::createRewardScene(RewardScene::Reward r) {
    
    std::string name = r.getName();
    auto type = r.getType();

    if (type == RewardScene::Reward::Type::INSTANT){
        if (name == "fusion")
            return std::make_shared<FusionRewardScene>(game, r);
        else if (name == "stick")
            return std::make_shared<StickRewardScene>(game, r);
        else // (name == "cauldron")
            return std::make_shared<CauldronRewardScene>(game, r);
    }
    else if (type == RewardScene::Reward::Type::BOSS) {
        return std::make_shared<BossRewardScene>(game, r);
    }
    else 
        return std::make_shared<PermanentRewardScene>(game, r);
}
