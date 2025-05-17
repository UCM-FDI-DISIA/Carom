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

    _obtainedBallsInfo = ballsInfo;
}

BossRewardScene::~BossRewardScene()
{

}

bool BossRewardScene::checkIfBallIsObtained(PoolScene::BallInfo ballInfo) {
    for(PoolScene::BallInfo ball : _selectedBalls) {
        if(ballInfo == ball) {
            return true;
        }
    }
    return false;
}

void BossRewardScene::initObjects()
{
    auto ballsPos = sdlutils().svgs().at("boss_reward_balls_pos");

    #ifdef _DEBUG
        std::cout << "SKIBIDI" << std::endl;
    #endif
     int p = 0;

    for(auto svgInfo : ballsPos) {
        for(int i = 0; i < _obtainedBallsInfo.size(); i++) {
            if(!_obtainedBallsInfo[i].free) continue;
            Entity* ball = new Entity(*this, grp::UI);
            float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;
            b2Vec2 pos = {PhysicsConverter::pixel2meter(svgInfo.second.x, svgInfo.second.y)};
            pos.x += p * ballScale * 1.1f;

            addComponent<TransformComponent>(ball, pos);

            std::string textureKey = "bola_blanca";

            PoolScene::EffectType firstBallEffect = _obtainedBallsInfo[i].effects[0];
            switch(firstBallEffect) {
                case ABBACUS: textureKey = "single_AbacusEffect"; break;
                case BOWLING: textureKey = "single_BowlingEffect"; break;
                case CRISTAL: textureKey = "single_CristalEffect"; break;
                case PETANQUE: textureKey = "single_PetanqueEffect"; break;
                case POKEBALL: textureKey = "single_PokeballEffect"; break;
                case QUANTIC: textureKey = "single_QuanticEffect"; break;
                case X2: textureKey = "single_X2Effect"; break;
            }

            addComponent<RenderTextureComponent>(ball, &sdlutils().images().at(textureKey), renderLayer::EFFECT_BALL, ballScale);

            createBallShadow(ball);

            Button::TextureButton rButton = Button::TextureButton();
            auto button = addComponent<Button>(ball, rButton);

            button->setOnClick([this, ball, i]() {
                if(checkIfBallIsObtained(_obtainedBallsInfo[i])) {
                    ball->getComponent<RenderTextureComponent>()->resetColorTint();
                    _selectedBalls.erase(std::remove(_selectedBalls.begin(), _selectedBalls.end(), _obtainedBallsInfo[i]));
                }else{
                    ball->getComponent<RenderTextureComponent>()->changeColorTint(0, 255, 0);
                    _selectedBalls.push_back(_obtainedBallsInfo[i]);
                }

                checkIfValid();
            });

            p++;
        }
    }

    auto ballButtons = openInventory();

    for(auto& ballButton : ballButtons) {
        ballButton.button->setOnClick([this, ballButton]() {
            if(checkIfBallIsSelected(ballButton.slot)) {
                _ballsToRemove.erase(std::remove(_ballsToRemove.begin(), _ballsToRemove.end(), ballButton.slot));
                ballButton.button->getEntity()->getComponent<RenderTextureComponent>()->resetColorTint();
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
        _inventory->removeBall(index-1);
    }

    for(PoolScene::BallInfo ball : _selectedBalls) {
        std::vector<int> ids;
        for(PoolScene::EffectType effect : ball.effects) ids.push_back((int)effect);
        InventoryManager::Instance()->addBall(ids);
    }
}