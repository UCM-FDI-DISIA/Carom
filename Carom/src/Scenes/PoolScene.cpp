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
#include "RewardScene.h"
#include "CowboyPoolScene.h"
#include "StickInputComponent.h"

#include "DefaultReward.h"
#include "BossReward.h"
#include "FusionReward.h"
#include "GumballReward.h"
#include "StickReward.h"
#include "CauldronReward.h"
#include "SkillReward.h"
#include "CharismaReward.h"
#include "PowerReward.h"
#include "CunningReward.h"
#include "AudioManager.h"
// #include ...Reward.h

#include "Game.h"
#include "Vector2D.h"
#include <box2d/box2d.h>


using body_t = RewardInfoDisplayComponent::Body;

PoolScene::PoolScene(Game* g) : UIScene(g)
{
    createPauseEntity();
    _rngm = new RNG_Manager();
    _am = AudioManager::Instance();
    _am->changeToPauseTheme();

    // Create table with texture and colliders
    createBackground("suelo");
    createTable();
    generateMatchHoles();
    generateFloorRewards();
}

PoolScene::~PoolScene()
{
    delete _rngm;
}

void PoolScene::generateMatchHoles()
{
    // Entre 0 y posiciones-1 elige un indice para que sea el boss.
    _bossHole = _rngm->randomRange(0, HOLES);
    #ifdef _DEBUG
    std::cout << "Boss hole: " << _bossHole << std::endl;
    #endif

    // coloca los agujeros de partida
    for(int i = 0; i < HOLES; i++){

        // genera el agujero.
        entity_t hole = generateHole(i);

        auto button = hole->getComponent<Button>();

        if(i == _bossHole){ // --- POSICION BOSS.
            //createSceneButton(pos.x, pos.y, ms, grp::POOL_HOLE, renderLayer::POOL_HOLE, "hole", 0.2f)
            
            button->setOnClick([=](){
                hole->_components[cmp::BUTTON]->setEnabled(false); // Deshabilita el agujero si se ha jugado la partida
                
                NullState* state = new NullState(nullptr);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, true); // ! tst  
                
                RewardScene* rs = new RewardScene(game); // TODO: Escena de recompensas de boss (pasar de piso, bolas de la mesa)
                
                game->getScenesManager()->pushScene(rs);
                game->getScenesManager()->pushScene(ms);
            });
        }
        else{ // --- POSICION COLORES.
            button->setOnClick([this](){
                
                NullState* state = new NullState(nullptr);
                CowboyPoolScene *ms = new CowboyPoolScene(state, game, false); // ! tst  
                
                RewardScene* rs = new RewardScene(game);

                game->getScenesManager()->pushScene(rs);
                game->getScenesManager()->pushScene(ms);
            });
        }

        button->setOnHover([this, i]() {
            #ifdef _DEBUG
            std::cout << "Hovering pool hole " << i << std::endl; 
            #endif

            showReward(i);
        });

        button->setOnExit([this, i]() {
            #ifdef _DEBUG
            std::cout << "Exiting pool hole " << i << std::endl;
            #endif

            hideReward(i);
        });
    }
}

entity_t PoolScene::generateHole(int i)
{
    // agujero.
    entity_t e = new Entity(*this, grp::POOL_HOLE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).x,
        *&sdlutils().svgs().at("pool").at("hole " + std::to_string(i)).y
    );

    float scale = float(sdlutils().svgs().at("pool").at("hole 0").width) / float(sdlutils().images().at("hole").width());

    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

    Button::TextureButton rButton = Button::TextureButton();
    addComponent<Button>(e, rButton);

    return e;
}

void
PoolScene::loadRewards() {
    // TODO: parse all rewards from JSON

    // PROVISIONAL, para testear      
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<FusionReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<GumballReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<StickReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<CauldronReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<SkillReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<CharismaReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<PowerReward>(), 1.0f));
    _rewards.push_back(RandomItem<std::shared_ptr<Reward>>(std::make_shared<CunningReward>(), 1.0f));

}


void
PoolScene::generateFloorRewards() {
    // Generar array de todas las recompensas a partir del JSON
    loadRewards();

    _floorRewards = _rngm->getRandomItems(_rewards, HOLES, true); // Se puede repetir tipo de recompensa
    
    // Swaps boss hole assigned reward for a Boss Reward
    _floorRewards[_bossHole] = std::make_shared<BossReward>();

    createRewardInfo();
}

void
PoolScene::createRewardInfo() {
    entity_t description;
    b2Vec2 pos;

    auto texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("pool").at("box_0").width) / texture->width();

    for(int i = 0; i < HOLES; ++i) {
        // FONDO
        description = new Entity(*this, grp::REWARD_INFO_BG);

        auto svgElem = *&sdlutils().svgs().at("pool").at("box_" + std::to_string(i));
        pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale);

        description->deactivate();

        // TEXTO
        // TODO: Añadir texto de recompensa / texto de partida de boss
        // en función de _floorRewards[i]
        Text title, rewardName, rewardType, rewardDesc;

        switch(_floorRewards[i]->getType()) {
            case Reward::Type::INSTANT:
                title = sdlutils().texts().at("rewardTitle_pool");
                rewardType = sdlutils().texts().at("instantReward_pool");
                break;
            case Reward::Type::PERMANENT:
                title = sdlutils().texts().at("rewardTitle_pool");
                rewardType = sdlutils().texts().at("permanentReward_pool");
                break;
            case Reward::Type::BOSS:
                title = sdlutils().texts().at("bossTitle_pool");
                rewardType = sdlutils().texts().at("bossReward_pool");
                break;
            default:
                title = sdlutils().texts().at("rewardTitle_pool");
                rewardType = sdlutils().texts().at("reward_pool");
                break;
        }

        rewardName = sdlutils().texts().at(_floorRewards[i]->getName()+"_rewardName_pool");
        rewardDesc = sdlutils().texts().at(_floorRewards[i]->getName()+"_rewardDesc_pool");
        // rewardName = sdlutils().texts().at("cauldron_rewardName_pool");
        // rewardDesc = sdlutils().texts().at("cauldron_rewardDesc_pool");
        

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
    assert(i < HOLES);

    auto descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->activate();
}

void
PoolScene::hideReward(int i) {
    assert(i < HOLES);

    auto descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->deactivate();
}