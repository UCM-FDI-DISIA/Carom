#include "CauldronRewardScene.h"
#include "BowlingEffect.h"
#include "X2Effect.h"
#include "AbacusEffect.h"
#include "CristalEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "QuanticEffect.h"
#include "InventoryManager.h"
#include "TextDisplayComponent.h"
#include "ecs.h"

using body_t = BallInfoDisplayComponent::Body;

CauldronRewardScene::CauldronRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward), _randomEffect(RewardScene::ballID::NORMAL_BALL)
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
    std::vector<RewardScene::ballID> effects;
    effects = InventoryManager::Instance()->getEffectsFromBall(_selectedBallId - 1);

    switch(_randomEffect){
        case RewardScene::ballID::BOWLING:
            effects.push_back(RewardScene::ballID::BOWLING);
            break;
        case RewardScene::ballID::X2:
            effects.push_back(RewardScene::ballID::X2);
            break;
        case RewardScene::ballID::ABBACUS:
            effects.push_back(RewardScene::ballID::ABBACUS);
            break;
        case RewardScene::ballID::CRISTAL:
            effects.push_back(RewardScene::ballID::CRISTAL);
            break;
        case RewardScene::ballID::PETANQUE:
            effects.push_back(RewardScene::ballID::PETANQUE);
            break;
        case RewardScene::ballID::POKEBALL:
            effects.push_back(RewardScene::ballID::POKEBALL);
            break;
        case RewardScene::ballID::QUANTIC:
            effects.push_back(RewardScene::ballID::QUANTIC);
            break;
        default:
            std::cout << "MAL NOSEQUE" << std::endl;
            break;
    };

    InventoryManager::Instance()->removeBall(_selectedBallId-1);

    std::vector<int> effectsToInt;
    for(auto effect : effects){
        effectsToInt.push_back(int (effect));
    }
    
    InventoryManager::Instance()->addBall(effectsToInt);
}

/// @brief Selects a random effect to apply and displays its description.
void CauldronRewardScene::initObjects()
{
    RewardScene::initObjects();

    // Text with info to load

    _randomEffect = RewardScene::ballID (1 + (rand() % 7));

    Text title, desc;

    switch(_randomEffect){
        case RewardScene::ballID::BOWLING:
            title = sdlutils().texts().at("bowling_ballName_pool");
            desc = sdlutils().texts().at("bowling_ballDesc_pool");
            break;
        case RewardScene::ballID::X2:
            title = sdlutils().texts().at("x2_ballName_pool");
            desc = sdlutils().texts().at("x2_ballDesc_pool");
            break;
        case RewardScene::ballID::ABBACUS:
            title = sdlutils().texts().at("abbacus_ballName_pool");
            desc = sdlutils().texts().at("abbacus_ballDesc_pool");
            break;
        case RewardScene::ballID::CRISTAL:
            title = sdlutils().texts().at("cristal_ballName_pool");
            desc = sdlutils().texts().at("cristal_ballDesc_pool");
            break;
        case RewardScene::ballID::PETANQUE:
            title = sdlutils().texts().at("petanque_ballName_pool");
            desc = sdlutils().texts().at("petanque_ballDesc_pool");
            break;
        case RewardScene::ballID::POKEBALL:
            title = sdlutils().texts().at("poke_ballName_pool");
            desc = sdlutils().texts().at("poke_ballDesc_pool");
            break;
        case RewardScene::ballID::QUANTIC:
            title = sdlutils().texts().at("quantic_ballName_pool");
            desc = sdlutils().texts().at("quantic_ballDesc_pool");
            break;
        default:
            title = sdlutils().texts().at("normal_ballName_pool");
            desc = sdlutils().texts().at("normal_ballDesc_pool");
            break;
    };

    title.text = "Se añadira el siguiente efecto: ";

    auto svgElem = *&sdlutils().svgs().at("reward").at("textArea");
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
void CauldronRewardScene::initFunctionalities() 
{
    auto balls = openInventory();

    for(auto ball : balls){
        if(ball.slot == 0) continue;

        ball.button->setOnClick([ball, this](){
            _selectedBallId = ball.slot;
            showExitButton();
        });
    }
}