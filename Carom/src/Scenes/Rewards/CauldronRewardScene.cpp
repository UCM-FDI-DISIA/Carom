#include "CauldronRewardScene.h"
#include "BowlingEffect.h"
#include "X2Effect.h"
#include "AbacusEffect.h"
#include "CristalEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "QuanticEffect.h"
#include "InventoryManager.h"
#include "ecs.h"

using body_t = BallInfoDisplayComponent::Body;

CauldronRewardScene::CauldronRewardScene(Game* game, Reward reward)
    : InstantRewardScene(game, reward, 1)
{
    #ifdef _DEBUG
        std::cout << "CAULDRON" << std::endl;
    #endif
}

CauldronRewardScene::~CauldronRewardScene()
{

}

void CauldronRewardScene::applyReward()
{
    int inventoryBallId = getSelectedItems()[0]-1;
    std::vector<PoolScene::EffectType> chosenBallEffects = InventoryManager::Instance()->getEffectsFromBall(inventoryBallId);

    for(PoolScene::EffectType effect : chosenBallEffects)
        if(effect == _randomEffect) return;
    
    chosenBallEffects.push_back(_randomEffect);

    std::vector<int> intParsedEffects;
    for(PoolScene::EffectType effect : chosenBallEffects)
        intParsedEffects.push_back(int(effect));

    InventoryManager::Instance()->removeBall(inventoryBallId);
    InventoryManager::Instance()->addBall(intParsedEffects);
}

void CauldronRewardScene::initObjects()
{
    RewardScene::initObjects();

    createSVGImage("win", "Cauldron_Info", "inventory_description_box");

    _randomEffect = PoolScene::EffectType(RNG_Manager::Instance()->randomRange(0, int(PoolScene::NUM_EFFECTS)));

    Text title, desc;

    switch(_randomEffect){
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
    };
    
    title.text = "Efecto a añadir";

    float scale = static_cast<float>(*&sdlutils().svgs().at("reward").at("textArea").width);
    auto svgElem = *&sdlutils().svgs().at("reward").at("textArea");
    auto pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

    auto description = new Entity(*this, grp::BALL_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<BallInfoDisplayComponent>(description, 101, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{desc.text, desc.font, desc.color, scale*1.5f}
                , scale - 60
                , scale, scale/2
            );
}

void CauldronRewardScene::initFunctionalities() 
{
    auto balls = openInventory();

    for(auto ball : balls){
        if(ball.slot == 0) continue;

        ball.button->setOnClick([ball, this](){
            selectItem(ball.slot);
            showExitButton();
        });
    }
}