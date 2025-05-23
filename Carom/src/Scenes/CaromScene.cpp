#include "CaromScene.h"

#include <box2d/box2d.h>
#include "PhysicsUtils.h"
#include "Vector2D.h"
#include "Game.h"
#include "InputHandler.h"


#include "TransformComponent.h"
#include "FollowComponent.h"
#include "RenderTextureComponent.h"
#include "CircleRBComponent.h"
#include "PolygonRBComponent.h"
#include "ColorHitManager.h"
#include "WhiteBallScorerComponent.h"
#include "StickInputComponent.h"
#include "Button.h"
#include "TextDisplayComponent.h"
#include "ColorBallScorerComponent.h"
#include "RNG_Manager.h"
#include "AudioManager.h"
#include "RandomItem.h"
#include "StartMatchState.h"
#include "BallHandler.h"
#include "AbacusEffect.h"
#include "BowlingEffect.h"
#include "PetanqueEffect.h"
#include "QuanticEffect.h"
#include "MagicWandStickEffect.h"
#include "GranadeLauncherStickEffect.h"
#include "DonutStickEffect.h"
#include "NullState.h"
#include "UIScene.h"
#include "EndGameScene.h"
#include "ScenesManager.h"
#include "WinMatchState.h"
#include "RenderArrayComponent.h"

#include "InventoryManager.h"
#include "JsonEntityParser.h"

#include "ShadowComponent.h"
#include "RandomVibrationComponent.h"

#include "Animation.h"
#include "RenderSpritesheetComponent.h"
#include "AnimatorComponent.h"
#include "RoundScoreAnimComponent.h"

void shakeEntity(entity_t, bool reverse);

CaromScene::CaromScene( Game* game, State* s) 
    : GameScene(game)
    , _updatePhysics(true)
    , _currentScore()
    , _scoreToBeat()
    , _currentState(s)
    , _rngManager(RNG_Manager::Instance())
    , _remainingHits(5 + InventoryManager::Instance()->getPower())
    , _scoreToBeatDisplay(nullptr)
{
}

void CaromScene::init()
{
    // Boss match requires a different score to beat
    int baseScore;
    if(isBossMatch()) baseScore = 6;
    else baseScore = 4; 

    baseScore *= InventoryManager::Instance()->getCunning();
    if (baseScore == 0) baseScore = 1;
    _currentScore = InventoryManager::Instance()->getCharisma();

    // Set the score to beat based on the current ante
    setScoreToBeat(game->getProgressionManager()->getScoreToBeat(baseScore));

    initFunctionalities();
    initGimmick();
    initObjects();
    initBoss();

    //SFX DE JEFE
    if(isBossMatch()){
        AudioManager::Instance()->playMusicTrack(trackName::BOSS_WHISPER);
    }

    if(_currentState == nullptr)
        setNewState(new StartMatchState(this));

    _initialized = true;

    AudioManager::Instance()->changeToMainTheme();
}

void CaromScene::initFunctionalities()
{
    _sceneManager = game->getScenesManager();

    _rngManager = RNG_Manager::Instance();

    // Creación del mundo físico
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _myB2WorldId = b2CreateWorld(&worldDef);
    b2World_SetRestitutionThreshold(_myB2WorldId, 0.01); // para la bola rebotear más realisticamente
    _hitManager = new ColorHitManager(this);
}

void CaromScene::initObjects()
{
    //TODAS las caromScene se pueden pausar
    createPauseEntity();

    createScoreEntity();
    
    createStick();
    
    // WHITE BALL
    // Converts (x, y) from screen(svg) to meters and to meter coordinates
    b2Vec2 wb_pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("bola_blanca").x,
        *&sdlutils().svgs().at("game").at("bola_blanca").y
    );
    auto ball = createWhiteBall(wb_pos, b2_dynamicBody, 1, 0.2, 1);
    createIndicator(ball);
        
    // EFFECT BALLS
    createEffectBalls();

    // Create table with texture and colliders
    createTable();
    getEntitiesOfGroup(grp::TABLE_BACKGROUND)[0]->getComponent<RenderTextureComponent>()->changeColorTint(0, 191, 255);
    createBackground("suelo");

    _currentScoreDisplay = createScoreUI();
    _roundScoreDisplay = createRoundScoreUI();
    _remainingHitsDisplay = createRemainingHitsUI();
}

entity_t
CaromScene::createWhiteBall(const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution) 
{
    // SCALE
    float svgSize = *&sdlutils().svgs().at("game").at("bola_blanca").width;
    float textureSize = sdlutils().images().at("bola_blanca").width();
    float scale = svgSize/textureSize;

    entity_t e = new Entity(*this, grp::WHITEBALL);

    float radius = PhysicsConverter::pixel2meter(static_cast<float>(*&sdlutils().svgs().at("game").at("bola_blanca").width)/2);
    addComponent<CircleRBComponent>(e, pos, b2_dynamicBody, radius); 

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), renderLayer::WHITE_BALL, scale);
    addComponent<WhiteBallScorerComponent>(e);

    Button::RadialButton rButton = Button::RadialButton(2.0);
    addComponent<Button>(e, rButton);
    e->getComponent<Button>()->setOnClick([this](){
        for (auto& e : getEntitiesOfGroup(grp::PALO)) {
            e->activate();

            e->getComponent<RenderTextureComponent>()->setEnabled(false);
            e->getComponent<ShadowComponent>()->setEnabled(false);
        }
        for (auto& e : getEntitiesOfGroup(grp::AIM_LINE))
            e->activate();
    });

    addComponent<BallHandler>(e);
    
    _entsByGroup[grp::PALO][0]->getComponent<StickInputComponent>()->registerWhiteBall(e);

    createBallShadow(e);

    return e;
}

entity_t CaromScene::createStick()
{
    auto stick = InventoryManager::Instance()->getStick(*this);

    stick->deactivate();

    return stick;
}

/// @brief Creates and randomly places as many effect balls as specified
/// @param n Number of balls to place
void 
CaromScene::createEffectBalls() {
    

    //----GENERACION DE POSICIONES----
    int npos = sdlutils().svgs().at("positions").size();

    std::vector<RandomItem<int>> positions;
    for(int i = 1; i <= npos; ++i)
        positions.push_back(RandomItem(i, 1.0f));

    std::vector<int> eb_selected_pos = _rngManager->getRandomItems(positions, InventoryManager::MAX_BALLS, false);
    std::vector<b2Vec2> randomPositions;

    for(int i = 0; i < InventoryManager::MAX_BALLS; ++i) {
        std::string s = "bola";
        if(eb_selected_pos[i] > 1)
            s += ("_" + std::to_string(eb_selected_pos[i]));
        
        auto& eb = sdlutils().svgs().at("positions").at(s);
        auto eb_pos = PhysicsConverter::pixel2meter(eb.x, eb.y);
        randomPositions.push_back(eb_pos);
    }

    //CREA LAS BOLAS DEL JSON DE INVENTARIO Y LAS PONE EN LAS POSICIONES
    auto ballsVector = InventoryManager::Instance()->getEffectBalls(*this, randomPositions);

    //colores
    for(int i = 0; i < ballsVector.size(); i++){
        auto ball = ballsVector[i];
        if(ball!=nullptr){
            auto color = sdlutils().inventorySlotColor[i];
            ball->getRenderer()->changeDefaultColorTint(color.r, color.g, color.b);
        }
    }

    //AÑADIR SOMBRAS
    for(auto ball : ballsVector){
        if(ball!= nullptr){
            createBallShadow(ball);
        }
    }
}


void CaromScene::createBallShadow(entity_t entity){
    addComponent<ShadowComponent>(entity);
    ShadowComponent* comp = getComponent<ShadowComponent>(entity);

    //sombra de reflejo de la bola
    float a_imgScale = sdlutils().images().at("bola_cast_sombra").width();

    float a_svg_scale = sdlutils().svgs().at("game").at("bola_cast_sombra 1").width;
    float cast_scale = a_svg_scale/a_imgScale;

    comp->addShadow({0,0}, "bola_cast_sombra", renderLayer::BALL_SHADOW_ON_BALL, cast_scale, true, false, true);

    //sombra de la bola
    a_imgScale = sdlutils().images().at("bola_sombra").width();
    a_svg_scale = sdlutils().svgs().at("game").at("bola_sombra 1").width;
    cast_scale = a_svg_scale/a_imgScale;

    Vector2D a_relPos{
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").x - sdlutils().svgs().at("game").at("bola_sombra 1").x - 10),
        
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").y - sdlutils().svgs().at("game").at("bola_sombra 1").y)
    };
    comp->addShadow({a_relPos.getX(), a_relPos.getY()}, "bola_sombra", renderLayer::BALL_SHADOW_ON_TABLE, cast_scale, true, false, true);
}

void CaromScene::createScoreEntity(){
    //current score
    entity_t e = new Entity(*this, grp::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreSpriteL").x,
        *&sdlutils().svgs().at("game").at("scoreSpriteL").y
    );

    float scale = float(sdlutils().svgs().at("game").at("scoreSpriteL").width) / float(sdlutils().images().at("scoreSprite").width());


    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("current_score"), renderLayer::SCORE_CONTAINER, scale);

    // score to beat

    entity_t e1 = new Entity(*this, grp::SCORE);

    b2Vec2 pos1 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreSpriteR").x,
        *&sdlutils().svgs().at("game").at("scoreSpriteR").y
    );

    addComponent<TransformComponent>(e1, pos1);
    addComponent<RenderTextureComponent>(e1, &sdlutils().images().at("to_beat_score"), renderLayer::SCORE_CONTAINER, scale);

    // round score

    entity_t e2 = new Entity(*this, grp::SCORE);

    b2Vec2 pos2 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("roundScoreSpriteL").x,
        *&sdlutils().svgs().at("game").at("roundScoreSpriteL").y
    );

    addComponent<TransformComponent>(e2, pos2);
    addComponent<RenderTextureComponent>(e2, &sdlutils().images().at("roundScorerPup"), renderLayer::SCORE_CONTAINER, scale);
    _roundScorer = addComponent<RoundScoreAnimComponent>(e2, 10, 100);

    //plus sprite
    entity_t plus = new Entity(*this, grp::SCORE);

    b2Vec2 pos3 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("plus 1").x,
        *&sdlutils().svgs().at("game").at("plus 1").y
    );

    addComponent<TransformComponent>(plus, pos3);
    float plusScale = float(sdlutils().svgs().at("game").at("plus 1").width) / float(sdlutils().images().at("plus").width());

    addComponent<RenderTextureComponent>(plus, &sdlutils().images().at("plus"), renderLayer::SCORE_CONTAINER, plusScale);
}

void CaromScene::createFeedbackTest(b2Vec2 pos, float rot) {
    //audio
    AudioManager::Instance()->playSoundEfect("hit");

    entity_t e = new Entity(*this, grp::FEEDBACK);

    Animation* a_anim = &sdlutils().animations().at("normal_collide_animation");

    TransformComponent* eTr = new TransformComponent(e, pos);
    eTr->setRotation(rot);
    e->addComponent<TransformComponent>(eTr);

    e->addComponent<RenderSpritesheetComponent> (
        new RenderSpritesheetComponent(e, a_anim->_spriteSheet, renderLayer::FEEDBACK_EFFECT, 
            a_anim->_scale, a_anim->_spriteRows, a_anim->_spriteCols, a_anim->_frameList[0].frame));
    
    e->addComponent<AnimatorComponent>(new AnimatorComponent(e, a_anim));
}

void CaromScene::setNewState(State* s){
    if (_currentState != nullptr) {
        _currentState->onStateExit();
        delete _currentState;
        _currentState = nullptr;
    }

    #if defined (_DEBUG)
    _fastForwardPhysics = false;
    #endif

    _currentState = s;
    _currentState->onStateEnter();
}

CaromScene::~CaromScene()
{
    if(isInitialized()) 
    {
        if(_currentState != nullptr) {
            delete _currentState;
            _currentState = nullptr;
        }

        if(isBossMatch()){
            AudioManager::Instance()->pauseMusicTrack(trackName::BOSS_WHISPER);
        }

        // Deletes entities before destroyWorld
        clearEntities();
    
        // el mundo debe destruirse aquí, recordad que los ids son punteros con sombrero y gabardina
        b2DestroyWorld(_myB2WorldId);
    
        delete _hitManager;
        _hitManager = nullptr;
        AudioManager::Instance()->changeToPauseTheme();
    }
}

void CaromScene::handleEvent()
{
    GameScene::handleEvent();
    #ifdef _DEBUG    
    // input to fast forward physics
    if (_canFastForwardPhysics && ih().isKeyDown(SDLK_s))
        _fastForwardPhysics = true;
    else
        _fastForwardPhysics = false;

    // ! DEBUG
    if(ih().isKeyDown(SDLK_e) && !_canRestart){
        _canRestart = true;
    }
    if (ih().isKeyDown(SDLK_r) && _canRestart){
        _canRestart = false;
        game->requestRestart();
    }

    if(ih().keyDownEvent() && ih().isKeyDown(SDLK_l)){ 
        // Al presionar la "L" te lleva a la escena de perder.
            /*std::cout << "Carga escena de PERDER." << std::endl;
            NullState* state = new NullState(nullptr);

            // !!! CREA ENDGAMESCENE.
            GameScene*ms = new EndGameScene(game); // ! tst  
            game->getScenesManager()->pushScene(ms);*/

            // para activar invokeLose();
            _remainingHits = 0;
    }
    #endif

    if(ih().keyDownEvent() && ih().isKeyDown(SDLK_w)){
        // Al presionar la "W" te lleva a la escena de ganar.
        // para activar roundwins();
        _currentScore = 2 * _scoreToBeat;
    }

}

#if defined(_DEBUG)
void CaromScene::setCanFastForward(bool active)
{
    _canFastForwardPhysics = active;
    _fastForwardPhysics = false;
}
#endif

void CaromScene::updatePhysics()
{
    b2World_Step(_myB2WorldId, _b2timeSteps, _b2Substeps);

    b2ContactEvents a_contactEvents = b2World_GetContactEvents(_myB2WorldId);
    manageEnterCollisions(a_contactEvents);
    manageExitCollisions(a_contactEvents);

    b2SensorEvents a_sensorEvents = b2World_GetSensorEvents(_myB2WorldId);
    manageEnterTriggers(a_sensorEvents);
    manageExitTriggers(a_sensorEvents);
}

void CaromScene::updateScene()
{
    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    
    _hitManager->clearAllHits();

    GameScene::update();
}

void CaromScene::update()
{
    // Iterations purpose for fast forwarding
    int iterations = 1;
    #if defined (_DEBUG)
    if (_fastForwardPhysics)
        iterations = _fastForwardIterations;
    #endif
    for (int i = 0; i < iterations; ++i){
        updatePhysics();
        updatePhysics();
        updateScene(); 
    }
}

b2BodyId CaromScene::addBodyToWorld(b2BodyDef bodyDef){
    return b2CreateBody(_myB2WorldId, &bodyDef);
}

b2RayResult 
CaromScene::castRayToWorld(b2Vec2 origin, b2Vec2 translation) {
    return b2World_CastRayClosest(_myB2WorldId, origin, translation, b2DefaultQueryFilter());
}

void CaromScene::drawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }

    }
}

void
CaromScene::manageEnterCollisions(b2ContactEvents contactEvents){
    if(!_updatePhysics) return;

    for(int i = 0; i < contactEvents.beginCount; ++i){
        b2ContactBeginTouchEvent* a_enter = contactEvents.beginEvents + i;

        // Validity check
        if (!b2Shape_IsValid(a_enter->shapeIdA) || !b2Shape_IsValid(a_enter->shapeIdB))
            continue;

        entity_t ent1 = static_cast<entity_t>(b2Shape_GetUserData(a_enter->shapeIdA));
        entity_t ent2 = static_cast<entity_t>(b2Shape_GetUserData(a_enter->shapeIdB));
        b2Manifold contactData = a_enter->manifold;

        // Null check: entities might have been destroyed
        if (ent1 && ent2) {
            ent1->getComponent<RigidBodyComponent>()->onCollisionEnter(ent2, contactData);
            ent2->getComponent<RigidBodyComponent>()->onCollisionEnter(ent1, contactData);
        }
    }
}

void
CaromScene::manageExitCollisions(b2ContactEvents contactEvents){
    if(!_updatePhysics) return;

    for(int i = 0; i < contactEvents.endCount; ++i){
        b2ContactEndTouchEvent* a_exit = contactEvents.endEvents + i;

        // Validity check
        if (!b2Shape_IsValid(a_exit->shapeIdA) || !b2Shape_IsValid(a_exit->shapeIdB))
            continue;

        entity_t ent1 = static_cast<entity_t>(b2Shape_GetUserData(a_exit->shapeIdA));
        entity_t ent2 = static_cast<entity_t>(b2Shape_GetUserData(a_exit->shapeIdB));

        // Null check: entities might have been destroyed
        if (ent1 && ent2) {
            ent1->getComponent<RigidBodyComponent>()->onCollisionExit(ent2);
            ent2->getComponent<RigidBodyComponent>()->onCollisionExit(ent1);
        }
    }
}

void
CaromScene::manageEnterTriggers(b2SensorEvents sensorEvents){
    if(!_updatePhysics) return;

    for(int i = 0; i < sensorEvents.beginCount; ++i){
        b2SensorBeginTouchEvent* a_enter = sensorEvents.beginEvents + i;

        // Validity check
        if (!b2Shape_IsValid(a_enter->sensorShapeId) || !b2Shape_IsValid(a_enter->visitorShapeId))
            continue;

        entity_t sensor = static_cast<entity_t>(b2Shape_GetUserData(a_enter->sensorShapeId));
        entity_t visitor = static_cast<entity_t>(b2Shape_GetUserData(a_enter->visitorShapeId));

        // Null check: entities might have been destroyed
        if (sensor && visitor) {
            sensor->getComponent<RigidBodyComponent>()->onTriggerEnter(visitor);
        }
    }
}

void 
CaromScene::manageExitTriggers(b2SensorEvents sensorEvents) {
    if(!_updatePhysics) return;

    for(int i = 0; i < sensorEvents.endCount; ++i) {
        b2SensorEndTouchEvent* a_exit = sensorEvents.endEvents + i;
        
        // Validity check
        if (!b2Shape_IsValid(a_exit->sensorShapeId) || !b2Shape_IsValid(a_exit->visitorShapeId)){
            #ifdef _DEBUG
            std::cout << "Invalid shape in manageExitTriggers" << std::endl;
            #endif
            continue;
        }
        
        entity_t sensor = static_cast<entity_t>(b2Shape_GetUserData(a_exit->sensorShapeId));
        entity_t visitor = static_cast<entity_t>(b2Shape_GetUserData(a_exit->visitorShapeId));
        
        // Null check: entities might have been destroyed
        if (sensor && visitor) {
            sensor->getComponent<RigidBodyComponent>()->onTriggerExit(visitor);
                visitor->getComponent<RigidBodyComponent>()->onTriggerExit(sensor);
        }
    } 
}

TextDisplayComponent* 
CaromScene::createRemainingHitsUI() {

    entity_t hitsFrameObject = new Entity(*this, grp::SCORE);

    auto shotsLeftSprite = sdlutils().svgs().at("game").at("shotsLeftSprite");
    b2Vec2 framePos = PhysicsConverter::pixel2meter( shotsLeftSprite.x, shotsLeftSprite.y);

    float svgSize = shotsLeftSprite.width;
    float textureSize = sdlutils().images().at("shotsSprite").width();
    float scale = svgSize/textureSize;

    // no entiendo por que crear el transform component así, lo he copiado del método createScoreUI()
    hitsFrameObject->addComponent(new TransformComponent(hitsFrameObject, framePos));
    hitsFrameObject->addComponent(new RenderTextureComponent(hitsFrameObject, &sdlutils().images().at("shotsSprite"), 0, scale));
    //ShotsLeft text
    entity_t remainingHitsObject = new Entity(*this, grp::SCORE);

    auto shotsLeftText = sdlutils().svgs().at("game").at("shotsLeftText");
    b2Vec2 textPos = PhysicsConverter::pixel2meter( shotsLeftText.x, shotsLeftText.y);

    // no entiendo por que crear el transform component así, lo he copiado del método createScoreUI()
    remainingHitsObject->addComponent(new TransformComponent(remainingHitsObject, textPos));
    TextDisplayComponent* remainingHitsDisplay = new TextDisplayComponent(remainingHitsObject, 1, 1.0, 
        std::to_string(_remainingHits), {255, 255, 255, 255}, "Basteleur-Bold72");
    remainingHitsObject->addComponent(remainingHitsDisplay);

    addComponent<TweenComponent>(remainingHitsObject);

    return remainingHitsDisplay;
}

TextDisplayComponent*
CaromScene::createScoreUI() {
    //CurrentScore
    entity_t currentScoreObject = new Entity(*this, grp::SCORE);

    b2Vec2 pos1 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreTextL").x,
        *&sdlutils().svgs().at("game").at("scoreTextL").y
    );

    currentScoreObject->addComponent(new TransformComponent(currentScoreObject, pos1));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(currentScoreObject, renderLayer::SCORE, 1, "0", 
        {255, 255, 255, 255}, "Basteleur-Moonlight48");
    currentScoreObject->addComponent(currentDisplay);

    //Score to beat
    entity_t scoreToBeatObject = new Entity(*this, grp::SCORE);

    b2Vec2 pos2 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreTextR").x,
        *&sdlutils().svgs().at("game").at("scoreTextR").y
    );

    scoreToBeatObject->addComponent(new TransformComponent(scoreToBeatObject, pos2));         
    _scoreToBeatDisplay = new TextDisplayComponent(scoreToBeatObject, renderLayer::SCORE, 1, std::to_string(_scoreToBeat), 
        {255, 255, 255, 255}, "Basteleur-Moonlight48");
    
    scoreToBeatObject->addComponent<TextDisplayComponent>(_scoreToBeatDisplay);

    return currentDisplay;
}

/// @brief creates the text of the round score label
/// @return the entity with the text
TextDisplayComponent*
CaromScene::createRoundScoreUI(){

    entity_t roundScoreObject = new Entity(*this, grp::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("roundScoreTextL").x,
        *&sdlutils().svgs().at("game").at("roundScoreTextL").y
    );

    roundScoreObject->addComponent(new TransformComponent(roundScoreObject, pos));
    TextDisplayComponent* roundDisplay = new TextDisplayComponent(roundScoreObject, renderLayer::SCORE, 1, "0", 
        {255, 255, 255, 255}, "Basteleur-Moonlight48");
    roundScoreObject->addComponent(roundDisplay);

    addComponent<TweenComponent>(roundScoreObject);

    return roundDisplay;
}

void CaromScene::addScore(int score) {
    _roundScore += score;
    _roundScoreDisplay->setDisplayedText(std::to_string(_roundScore));
    _roundScorer->setRoundScore(_roundScore);

    //sfx
    int rand = sdlutils().rand().nextInt(1, 3);
    std::string key = "point_up" + std::to_string(rand);

    AudioManager::Instance()->playSoundEfect(key);

    //tween 
    shakeEntity(_roundScoreDisplay->getEntity(), false);
    
}

void shakeEntity(entity_t ent, bool reverse){
    int factor = 1;
    if(reverse) factor = -1;
    //tween
    auto tween = ent->getComponent<TweenComponent>();

    if(!tween->isTweening()){
        auto previousPos = tween->getEntity()->getTransform()->getPosition();
        tween->easePosition(previousPos + b2Vec2{0.f, factor* 0.05f}, 0.2f, tween::EASE_OUT_QUINT, false, [=](){
            tween->easePosition(previousPos, 0.2f, tween::EASE_OUT_QUINT);
        });
        tween->easeRotation(factor*45, 0.1f, tween::EASE_OUT_QUINT, false, [=](){
            tween->easeRotation(factor*-30, 0.1f, tween::EASE_OUT_QUINT, false, [=](){
                tween->easeRotation(factor*15, 0.1f, tween::EASE_OUT_QUINT, false, [=](){
                    tween->easeRotation(0, 0.1f, tween::EASE_OUT_QUINT);
                });
            });
        });

    }
}

void CaromScene::addToTotalScore(int score) {
    _currentScore += score;
    _currentScoreDisplay->setDisplayedText(std::to_string(_currentScore));
}

void CaromScene::removeScore(int score) {
    _roundScore -= score;
    _roundScoreDisplay->setDisplayedText(std::to_string(_roundScore));
    _roundScorer->setRoundScore(_roundScore);
}

void CaromScene::removeFromTotalScore(int score) {
    _currentScore -= score;
    _currentScoreDisplay->setDisplayedText(std::to_string(_currentScore));
}

void CaromScene::addPointsFromRound(){
    addToTotalScore(_roundScore);
    removeScore(_roundScore);
}

void CaromScene::setScoreToBeat(int score){
    _scoreToBeat = score; 
    if(_scoreToBeatDisplay != nullptr) _scoreToBeatDisplay->setDisplayedText(std::to_string(score));
}

void CaromScene::decrementRemainingHits()
{
    if (_remainingHits > 0) {
        --_remainingHits;
        _remainingHitsDisplay->setDisplayedText(std::to_string(_remainingHits));
    }

    shakeEntity(_remainingHitsDisplay->getEntity(), true);
}

//---------------------------BOSS---------------------------------

void CaromScene::playBossTurn() {
    #ifdef _DEBUG
    std::cout<< "Play Boss Turn" << std::endl;
    #endif
    clearBossModifiers();
    applyBossModifiers();
}

void CaromScene::clearBossModifiers() {
    for(auto& e: getEntitiesOfGroup(grp::BOSS_MODIFIERS))
        setAlive(e, false); // delete boss modifiers
}

/// @brief Virtual method, subtypes of CaromScene must implement this method.
/// After this is done, _currentState->finish() must be called
void CaromScene::applyBossModifiers() {
    #ifdef _DEBUG
    std::cout << "aplicando modificador de boss desde CaromScene" << std::endl;
    #endif
    _currentState->finish();
}

void 
CaromScene::loadFromInventory() {
    
}

void CaromScene::instantiateBossTableShadow(){
    Entity* boss = new Entity(*this, grp::BOSS_SHADOW);
    b2Vec2 pos = PhysicsConverter::pixel2meter(sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").x, sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").y);
    auto tr = addComponent<TransformComponent>(boss, b2Vec2{2.f,2.f});
    tr->setRotation(25);
    Texture* bossImage = nullptr;
    switch(_boss){
        case Boss::COWBOY_POOL:
            bossImage = &sdlutils().images().at("cowboy_table_shadow");
            break;
        case Boss::RUSSIAN_PYRAMID:
            bossImage = &sdlutils().images().at("pyramid_table_shadow");
            break;
        default:
            bossImage = &sdlutils().images().at("pyramid_table_shadow");
            break;
    }

    float scale = sdlutils().svgs().at("boss_table_shadow").at("shadow_pos").width/ (float)sdlutils().images().at("cowboy_table_shadow").width();
    addComponent<RenderTextureComponent>(boss, bossImage, renderLayer::BOSS_SHADOW, scale);

    auto tweens = addComponent<TweenComponent>(boss);
    tweens->easePosition(pos, .5f, tween::EASE_IN_OUT_CUBIC, false, [=](){
        addComponent<RandomVibrationComponent>(boss, .05f, 1.f);
    });

    
}

void 
CaromScene::createIndicator(entity_t whiteBall) {
    _indicator = new Entity(*this, grp::FEEDBACK);
    addComponent<TransformComponent>(_indicator, b2Vec2_zero);
    addComponent<FollowComponent>(_indicator, whiteBall, true, false, false, Vector2D(0, 0));

    float wbScale = whiteBall->getTransform()->getScale().x / 2;
    addComponent<RenderTextureComponent>(_indicator, &sdlutils().images().at("russian_indicator"), renderLayer::RUSSIAN_PYRAMID_INDICATOR, wbScale);
}

void 
CaromScene::changeIndicator(entity_t whiteBall) {
    getComponent<FollowComponent>(_indicator)->setTarget(whiteBall);
}

void 
CaromScene::activateIndicator() {
    _indicator->activate();
}

void 
CaromScene::deactivateIndicator() {
    _indicator->deactivate();
}



