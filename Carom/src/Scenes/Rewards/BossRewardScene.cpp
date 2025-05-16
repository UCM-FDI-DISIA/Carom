#include "BossRewardScene.h"
#include "ScenesManager.h"
#include "InventoryManager.h"

#include "AbacusEffect.h"
#include "BowlingEffect.h"
#include "CristalEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "QuanticEffect.h"
#include "X2Effect.h"
#include "BallHandler.h"

BossRewardScene::BossRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "BOSS REWARD" << std::endl;
    #endif

    _inventory = InventoryManager::Instance();
    auto ballsInfo = game->getScenesManager()->getPoolScene()->getBallsInfo();

     for(auto ballInfo : ballsInfo) {
        if(!ballInfo.free) {
            _obtainedBallsInfo.push_back(ballInfo);
        }
    }
}

BossRewardScene::~BossRewardScene()
{

}

bool BossRewardScene::checkIfBallIsObtained(PoolScene::BallInfo ballInfo) {
    for(PoolScene::BallInfo ball : _obtainedBallsInfo) {
        if(ballInfo.effects == ball.effects) {
            return true;
        }
    }
    return false;
}

void BossRewardScene::initObjects()
{
    auto ballsPos = sdlutils().svgs().at("boss_reward_balls_pos");
    int i = 0;

    for(auto svgInfo : ballsPos) {
        Entity* ball = new Entity(*this, grp::UI);
        auto pos = svgInfo.second;
        addComponent<TransformComponent>(ball, b2Vec2(pos.x, pos.y));

        std::string textureKey = "bola_blanca";

        PoolScene::EffectType firstBallEffect = _obtainedBallsInfo[i].effects[0];
        switch(firstBallEffect) {
            case ABBACUS: textureKey = "single_AbbacusEffect"; break;
            case BOWLING: textureKey = "single_BowlingEffect"; break;
            case CRISTAL: textureKey = "single_CristalEffect"; break;
            case PETANQUE: textureKey = "single_PetanqueEffect"; break;
            case POKEBALL: textureKey = "single_PokeballEffect"; break;
            case QUANTIC: textureKey = "single_QuanticEffect"; break;
            case X2: textureKey = "single_X2Effect"; break;
        }

        addComponent<RenderTextureComponent>(ball, &sdlutils().images().at(textureKey), renderLayer::EFFECT_BALL, pos.height);

        createBallShadow(ball);

        Button::TextureButton rButton = Button::TextureButton();
        auto button = addComponent<Button>(ball, rButton);

        button->setOnClick([this, ball, i]() {
            if(checkIfBallIsObtained(_obtainedBallsInfo[i])) {
                ball->getComponent<RenderTextureComponent>()->changeColorTint(0, 0, 0);
                _selectedBalls.erase(std::remove(_selectedBalls.begin(), _selectedBalls.end(), _obtainedBallsInfo[i]));
            }else{
                ball->getComponent<RenderTextureComponent>()->changeColorTint(0, 255, 0);
                _selectedBalls.push_back(_obtainedBallsInfo[i]);
            }
        });

        i++;
    }

    auto ballButtons = openInventory();

    for(auto& ballButton : ballButtons) {
        ballButton.button->setOnClick([this, ballButton]() {
            if(checkIfBallIsSelected(ballButton.slot)) {
                _ballsToRemove.erase(std::remove(_ballsToRemove.begin(), _ballsToRemove.end(), ballButton.slot));
                ballButton.button->getEntity()->getComponent<RenderTextureComponent>()->changeColorTint(255, 255, 255);
            }
            else {
                _ballsToRemove.push_back(ballButton.slot);
                ballButton.button->getEntity()->getComponent<RenderTextureComponent>()->changeColorTint(255, 0, 0);
            }

            checkIfValid();
        });
    }
}

bool BossRewardScene::checkIfBallIsSelected(int ballId) {
    for(auto& ball : _ballsToRemove) {
        if(ball == ballId) {
            return true;
        }
    }
    return false;
}

void BossRewardScene::initFunctionalities() 
{

}

void BossRewardScene::checkIfValid()
{
    if(_inventory->getNumberOfEffectBalls() + _selectedBalls.size() - _ballsToRemove.size() > InventoryManager::MAX_BALLS) {
        hideExitButton();
        return;
    }
    else {
        showExitButton();
    }
}

void BossRewardScene::applyReward() {
    for(int index : _ballsToRemove) {
        _inventory->removeBall(index);
    }

    entity_t ball = new Entity(*this, grp::POOL_BALLS);
    addComponent<BallHandler>(ball);

    for(auto ballInfo : _selectedBalls) {
        if(ballInfo.free) continue;
        for(auto effect : ballInfo.effects) {
            switch(effect) {
                case ABBACUS: addComponent<AbacusEffect>(ball); break;
                case BOWLING: addComponent<BowlingEffect>(ball); break;
                case CRISTAL: addComponent<CristalEffect>(ball); break;
                case PETANQUE: addComponent<PetanqueEffect>(ball); break;
                case POKEBALL: addComponent<PokeballEffect>(ball); break;
                case QUANTIC: addComponent<QuanticEffect>(ball); break;
                case X2: addComponent<X2Effect>(ball); break;
            }
        }
    }
    
    InventoryManager::Instance()->addBall(ball);
    delete ball;
}