#include "CauldronRewardScene.h"
#include "BowlingEffect.h"
#include "X2Effect.h"
#include "AbacusEffect.h"
#include "CristalEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "QuanticEffect.h"
#include "TextDisplayComponent.h"
#include "Inventory.h"
#include "AudioManager.h"
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

/// @brief applies the effect to the selected ball
void CauldronRewardScene::applyReward()
{
    int inventoryBallId = getSelectedItems()[0]-1;
    std::vector<effectId_t> chosenBallEffects = Inventory::Instance()->getEffectsFromBall(inventoryBallId);

    for( effectId_t effect : chosenBallEffects)
        if(effect == _randomEffect) return;
    
    chosenBallEffects.push_back(_randomEffect);

    std::vector<effectId_t> intParsedEffects;
    for(effectId_t effect : chosenBallEffects)
        intParsedEffects.push_back(int(effect));

    Inventory::Instance()->removeBall(inventoryBallId);
    Inventory::Instance()->addBall(intParsedEffects);
}

/// @brief Selects a random effect to apply and displays its description.
void CauldronRewardScene::initObjects()
{
    RewardScene::initObjects();

    _randomEffect = effectId_t(RNG_Manager::Instance()->randomRange(1, effect::_LAST_EFFECT_ID));

    Text title, desc;

    switch(_randomEffect){
        case effect::BOWLING:
            title = sdlutils().texts().at("bowling_ballName_pool");
            desc = sdlutils().texts().at("bowling_ballDesc_pool");
            break;
        case effect::X2:
            title = sdlutils().texts().at("x2_ballName_pool");
            desc = sdlutils().texts().at("x2_ballDesc_pool");
            break;
        case effect::ABBACUS:
            title = sdlutils().texts().at("abbacus_ballName_pool");
            desc = sdlutils().texts().at("abbacus_ballDesc_pool");
            break;
        case effect::CRYSTAL:
            title = sdlutils().texts().at("cristal_ballName_pool");
            desc = sdlutils().texts().at("cristal_ballDesc_pool");
            break;
        case effect::PETANQUE:
            title = sdlutils().texts().at("petanque_ballName_pool");
            desc = sdlutils().texts().at("petanque_ballDesc_pool");
            break;
        case effect::POKEBALL:
            title = sdlutils().texts().at("poke_ballName_pool");
            desc = sdlutils().texts().at("poke_ballDesc_pool");
            break;
        case effect::QUANTIC:
            title = sdlutils().texts().at("quantic_ballName_pool");
            desc = sdlutils().texts().at("quantic_ballDesc_pool");
            break;
        default:
            title = sdlutils().texts().at("normal_ballName_pool");
            desc = sdlutils().texts().at("normal_ballDesc_pool");
            break;
    };

    title.text = "Se añadira el siguiente efecto: \n";

    auto svgElem = *&sdlutils().svgs().at("reward").at("textArea_center");
    auto pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);

    //Entity* entity, layerId_t renderLayer, float displayScale, 
    //std::string initialText, SDL_Color color, std::string key
    
    entity_t text = new Entity(*this, grp::SCORE);

    text->addComponent(new TransformComponent(text, pos));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(text, renderLayer::SCORE, 1, title.text + desc.text, 
        desc.color, desc.font);
    text->addComponent(currentDisplay);
}

/// @brief When a ball is clicked it is the selected ball and the continue button is displayed
void CauldronRewardScene::atRender() 
{
    auto balls = instantiateInventory();

    for(auto ball : balls){
        if(ball.slot == 0) continue;

        getComponent<RenderTextureComponent>((ball.button)->getEntity())->changeColorTint(64, 64, 64);

        ball.button->setOnClick([ball, this](){
            selectItem(ball.slot);
            
            if(!isSelected(ball.slot)) {
                getComponent<RenderTextureComponent>((ball.button)->getEntity())->changeColorTint(64, 64, 64);
                AudioManager::Instance()->playSoundEfect("unpick");
            }
            else {
                getComponent<RenderTextureComponent>((ball.button)->getEntity())->resetColorTint();
                AudioManager::Instance()->playSoundEfect("pick");
            }
            toggleExitButton();
        });
    }
}
