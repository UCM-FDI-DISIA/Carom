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

#include "RewardInfoDisplayComponent.h"


using body_t = RewardInfoDisplayComponent::Body;

BossRewardScene::BossRewardScene(Game* game, Reward reward)
    : RewardScene(game, reward)
{
    #ifdef _DEBUG
        std::cout << "BOSS REWARD" << std::endl;
    #endif

    _inventory = InventoryManager::Instance();

    _obtainedBallsInfo = game->getScenesManager()->getPoolScene()->getFreeBallsInfo();
}

BossRewardScene::~BossRewardScene()
{

}

bool BossRewardScene::checkIfBallIsObtained(int ballId) {
    for(int ball : _selectedBalls) {
        if(ballId == ball) {
            return true;
        }
    }
    return false;
}

void BossRewardScene::initObjects()
{
    // Mover el botón de continuar más a la derecha
    moveExitButtonToRight();

    //Mostramos el botón de salir por defecto
    showExitButton();
    
    createObtainedBalls(); // Bolas restantes de la PoolScene

    createBallInfoText(); //
    

    auto ballButtons = openInventory();

    //Se añaden a los botones las funciones para las bolas a eliminar
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

//Checkea si la selección de bolas es válida, en caso de serlo muestra el botón de salir
// y en caso contrario lo oculta
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

//Aplica la recompensa, elimina las bolas seleccionadas del inventario y añade las bolas seleccionadas de la recompensa
void BossRewardScene::applyReward() {
    for(int index : _ballsToRemove) {
        _inventory->removeBall(index-1);
    }

    for(int index : _selectedBalls) {
        PoolScene::BallInfo ball = _obtainedBallsInfo[index];
        std::vector<int> ids;
        for(BallId effect : ball.effects) {
            if(!hasElement(ids, (int)effect))ids.push_back((int)effect);
        }
        InventoryManager::Instance()->addBall(ids);
    }
}

void
BossRewardScene::createObtainedBalls() {
    auto ballsPos = sdlutils().svgs().at("reward");

    //  int p = 0;
    std::string s = "boss_reward_";

    for(int i = 0; i < _obtainedBallsInfo.size(); i++) {
        // if(!_obtainedBallsInfo[i].free) continue;
        Entity* ball = new Entity(*this, grp::UI);
        float ballScale = sdlutils().svgs().at("inventory").at("ball_1").width/ (float) sdlutils().images().at("bola_blanca").getRect().w;

        b2Vec2 pos = {PhysicsConverter::pixel2meter(ballsPos.at(s+std::to_string(i)).x,ballsPos.at(s+std::to_string(i)).y)};
        // pos.x += p * ballScale * 1.1f;

        addComponent<TransformComponent>(ball, pos);

        std::string textureKey = "bola_blanca";

        BallId firstBallEffect = _obtainedBallsInfo[i].effects[0];
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
            if(checkIfBallIsObtained(i)) {
                ball->getComponent<RenderTextureComponent>()->resetColorTint();
                _selectedBalls.erase(std::remove(_selectedBalls.begin(), _selectedBalls.end(), i));
            }else{
                ball->getComponent<RenderTextureComponent>()->changeColorTint(0, 255, 0);
                _selectedBalls.push_back(i);
            }

            checkIfValid();
        });

        button->setOnHover([this, i]() {
            showBallEffect(i);
        });

        button->setOnExit([this, i]() {
            hideBallEffect(i);
        });

        button->setOnRightClick([this, i]() {
            scrollObtainedBallEffect(i);
        });
    }
}

void 
BossRewardScene::createBallInfoText()
{
    entity_t description;
    b2Vec2 pos;

    Texture* texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("reward").at("boss_reward_info").width) / texture->width();
    
    pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("reward").at("boss_reward_info").x, 
        *&sdlutils().svgs().at("reward").at("boss_reward_info").y
        );

    for(int i = 0; i < _obtainedBallsInfo.size(); ++i) {
        // --- FONDO
        description = new Entity(*this, grp::REWARD_INFO_BG);


        addComponent<TransformComponent>(description, pos);
        addComponent<RenderTextureComponent>(description, texture, renderLayer::UI, scale);

        description->deactivate();

        
        // --- TEXTO
        Text title, ballName, ballDesc, ballType;

        title = sdlutils().texts().at("ballEffectTitle_pool");

        std::string ballEffect = PoolScene::getEffectName(_obtainedBallsInfo[i].effects[0]);

        ballName = sdlutils().texts().at(ballEffect + "_name_pool");
        ballDesc = sdlutils().texts().at(ballEffect + "_desc_pool");
        ballType = sdlutils().texts().at("ballEffectType_pool");

        // usa rewardInfoDisplayComponent porque en esencia es para lo mismo.
        description = new Entity(*this, grp::REWARD_INFO_TEXT);
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
BossRewardScene::showBallEffect(int i)
{
    assert(i < _obtainedBallsInfo.size());

    std::vector<entity_t> descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->activate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->activate();
}

void 
BossRewardScene::hideBallEffect(int i)
{
    assert(i < _obtainedBallsInfo.size());

    std::vector<entity_t> descriptions = getEntitiesOfGroup(grp::REWARD_INFO_BG);
    descriptions[i]->deactivate();

    descriptions = getEntitiesOfGroup(grp::REWARD_INFO_TEXT);
    descriptions[i]->deactivate();
}

void 
BossRewardScene::scrollObtainedBallEffect(int i) {
    
    if(_obtainedBallsInfo[i].scrollIndex == (_obtainedBallsInfo[i].effects.size() - 1)) _obtainedBallsInfo[i].scrollIndex = 0;
    else _obtainedBallsInfo[i].scrollIndex += 1; //No pongo ++ porque se me hacía ilegible
    
    std::string ballEffect = PoolScene::getEffectName(_obtainedBallsInfo[i].effects[_obtainedBallsInfo[i].scrollIndex]);
    
    auto texture = &sdlutils().images().at("reward_description_box");
    float scale = static_cast<float>(*&sdlutils().svgs().at("reward").at("boss_reward_info").width) / texture->width();

    Text ballName = sdlutils().texts().at(ballEffect + "_name_pool");
    Text ballDesc = sdlutils().texts().at(ballEffect + "_desc_pool");

    body_t nameBody = {ballName.text, ballName.font, ballName.color, scale * 1.5f};
    _effectRewardBoxes[i]->setRewardType(nameBody);

    body_t descBody = {ballDesc.text, ballDesc.font, ballDesc.color, scale * 2.0f};
    _effectRewardBoxes[i]->setRewardDesc(descBody);
}
