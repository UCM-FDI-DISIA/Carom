#include "CauldronRewardScene.h"
#include "BowlingEffect.h"
#include "X2Effect.h"
#include "AbacusEffect.h"
#include "CristalEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "QuanticEffect.h"
#include "InventoryManager.h"

CauldronRewardScene::CauldronRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward), _randomEffect(NONE)
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
    std::vector<b2Vec2> vector = std::vector<b2Vec2>();
    auto balls = InventoryManager::Instance()->getEffectBalls(*this, vector);

    auto target = balls[_selectedBallId - 1];

    switch(_randomEffect){
        case BOWLING:
            target->addComponent<BowlingEffect>(new BowlingEffect(target));
            break;
        case X2:
            target->addComponent<X2Effect>(new X2Effect(target));
                break;
        case ABBACUS:
            target->addComponent<AbacusEffect>(new AbacusEffect(target));
            break;
        case CRISTAL:
            target->addComponent<CristalEffect>(new CristalEffect(target));
            break;
        case PETANQUE:
            target->addComponent<PetanqueEffect>(new PetanqueEffect(target));
            break;
        case POKEBALL:
            target->addComponent<PokeballEffect>(new PokeballEffect(target));
            break;
        case QUANTIC:
            target->addComponent<QuanticEffect>(new QuanticEffect(target));
            break;
        default:
            std::cout << "MAL NOSEQUE" << std::endl;
            break;
    };

    InventoryManager::Instance()->saveBalls(balls);
    balls.clear();
}

void CauldronRewardScene::initObjects()
{
    RewardScene::initObjects();

    // Text with info to load

    createSVGImage("win", "Cauldron_Info", "inventory_description_box");

    _randomEffect = Effects (rand() % 7);

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

    title.text = "Efecto nuevo";

    auto texture = &sdlutils().images().at("inventory_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("win").at("Cauldron_Info").width) / texture->width();
    auto svgElem = *&sdlutils().svgs().at("win").at("Cauldron_Info");
    auto pos = PhysicsConverter::pixel2meter(svgElem.x, svgElem.y);
    pos.y -= 0.5;

    auto description = new Entity(*this, grp::BALL_INFO_TEXT);
        addComponent<TransformComponent>(description, pos);
        addComponent<BallInfoDisplayComponent>(description, 101, 
                body_t{title.text, title.font, title.color, scale*1.5f},
                body_t{desc.text, desc.font, desc.color, scale*1.5f}
                , texture->width() * scale - 60
                , -texture->width()/2 * scale, -texture->height()/2 * scale
            );
}

void CauldronRewardScene::initFunctionalities() 
{
    auto balls = openInventory();

    for(auto ball : balls){
        if(ball.slot == 0) continue;

        ball.button->setOnClick([ball, this](){
            _selectedBallId = ball.slot;
            _exitButton->activate();
            _exitBttText->activate();
        });
    }
}