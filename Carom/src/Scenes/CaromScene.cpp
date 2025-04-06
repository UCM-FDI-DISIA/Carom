#include "CaromScene.h"

#include <box2d/box2d.h>
#include "PhysicsUtils.h"
#include "Vector2D.h"
#include "Game.h"
#include "InputHandler.h"

#include "TransformComponent.h"
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
#include "RewardScene.h"
#include "EndGameScene.h"
#include "ScenesManager.h"
#include "WinMatchState.h"

#include "InventoryManager.h"
#include "ShadowComponent.h"

#include "Animation.h"
#include "RenderSpritesheetComponent.h"
#include "AnimatorComponent.h"



CaromScene::CaromScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward), _updatePhysics(true) , _currentScore(0), _scoreToBeat(1000)
{
    //TODAS las caromScene se pueden pausar
    createPauseEntity();

    _sceneManager = game->getScenesManager();

    // SEEDING
    // TODO: pasar RNG a sceneManager o Game para que haya uno solo
    _rngManager = new RNG_Manager();
    unsigned seed = _rngManager->randomRange(1, 1000000); 
    _rngManager->inseminate(seed);


    // Creación del mundo físico
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _myB2WorldId = b2CreateWorld(&worldDef);
    b2World_SetRestitutionThreshold(_myB2WorldId, 0.01); // para la bola rebotear más realisticamente

    setNewState(s);
        
    createStick();
    

    // WHITE BALL
    // Converts (x, y) from screen(svg) to meters and to meter coordinates
    b2Vec2 wb_pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("bola_blanca").x,
        *&sdlutils().svgs().at("game").at("bola_blanca").y
    );
    createWhiteBall(wb_pos, b2_dynamicBody, 1, 0.2, 1);
    // Apply impulse
    getEntitiesOfGroup(grp::WHITEBALL)[0]->getComponent<RigidBodyComponent>()->applyImpulseToCenter({0.0f, 0.0f});
        


    // EFFECT BALLS
    int n_eb = 3; // TODO: obetener esto de config
    createEffectBalls(n_eb);

    // Create table with texture and colliders
    createTable();
    

    createBackground("suelo");

    createScoreEntity();

    _hitManager = new ColorHitManager(this);

    _currentScoreDisplay = createScoreUI();
    _remainingHitsDisplay = createRemainingHitsUI();

    setNewState(new StartMatchState(this));
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
    //! I don't know how to get the radius of the ball
    addComponent<CircleRBComponent>(e, pos, b2_dynamicBody, radius); 

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), renderLayer::WHITE_BALL, scale);
    addComponent<WhiteBallScorerComponent>(e);
    Button::RadialButton rButton = Button::RadialButton(2.0);
    addComponent<Button>(e, rButton);
    e->getComponent<Button>()->setOnClick([this](){
        for (auto& e : getEntitiesOfGroup(grp::PALO))
            e->activate();
    });

        addComponent<BallHandler>(e);
    
    _entsByGroup[grp::PALO][0]->getComponent<StickInputComponent>()->registerWhiteBall(e);

    createBallShadow(e);

    return e;
}

entity_t CaromScene::createStick()
{
    // Scale
    float svgSize = *&sdlutils().svgs().at("game").at("palo1").width;
    float textureSize = sdlutils().images().at("palo1").width();
    float scale = svgSize/textureSize;

    entity_t e = new Entity(*this, grp::PALO);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("palo1").x,
        *&sdlutils().svgs().at("game").at("palo1").y
    );
    
    addComponent<TransformComponent>(e, pos);

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("palo1"), renderLayer::STICK, scale);
    addComponent<TweenComponent>(e);
    
    auto input = addComponent<StickInputComponent>(e, *&sdlutils().svgs().at("game").at("palo1").height);

    //* Used to add an effect for debugging
    //auto effect = addComponent<DonutStickEffect>(e);
    //input->registerStickEffect(effect);

    //!john cleon's stick shadow
    addComponent<ShadowComponent>(e);
    getComponent<ShadowComponent>(e)->addShadow(b2Vec2{-0.05, -0.05}, "palo1_sombra", renderLayer::STICK_SHADOW, scale, true, true, true);

    return e;
}

    
entity_t
CaromScene::createEffectBall(effect::effectId effectId, const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution, int layer) {
    // Scale
    float svgSize = *&sdlutils().svgs().at("positions").at("bola").width;
    float textureSize = sdlutils().images().at("bola_blanca").width(); // TODO: cambiar a textura effect ball
    float scale = svgSize/textureSize;        
    
    entity_t e = new Entity(*this, grp::EFFECTBALLS);
    
    // RB
    float radius = PhysicsConverter::pixel2meter(static_cast<float>(*&sdlutils().svgs().at("game").at("bola_blanca").width)/2);
    addComponent<CircleRBComponent>(e, pos, type, radius);

    // RENDER
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), renderLayer::EFFECT_BALL, scale, SDL_Color{0, 150, 100, 1});

    // SCORE
    addComponent<ColorBallScorerComponent>(e);

    // TODO: add components according to its id

    createBallShadow(e);

    addComponent<BallHandler>(e);
    addComponent<QuanticEffect>(e);

    return e;
}


/// @brief Creates and randomly places as many effect balls as specified
/// @param n Number of balls to place
void 
CaromScene::createEffectBalls(int n) {
    int npos = sdlutils().svgs().at("positions").size();
    assert(n <= npos);

    std::vector<RandomItem<int>> positions;
    for(int i = 1; i <= npos; ++i)
        positions.push_back(RandomItem(i, 1.0f));

    std::vector<int> eb_selected_pos = _rngManager->getRandomItems(positions, n, false);

    for(int i = 0; i < n; ++i) {
        std::string s = "bola";
        if(eb_selected_pos[i] > 1)
            s += ("_" + std::to_string(eb_selected_pos[i]));
        
        auto& eb = sdlutils().svgs().at("positions").at(s);
        auto eb_pos = PhysicsConverter::pixel2meter(eb.x, eb.y);

        createEffectBall(effect::NULO, eb_pos, b2_dynamicBody, 1, 0.2, 1, renderLayer::EFFECT_BALL);
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
    //primer score
    entity_t e = new Entity(*this, grp::SCORE);

    b2Vec2 pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreSpriteL").x,
        *&sdlutils().svgs().at("game").at("scoreSpriteL").y
    );

    float scale = float(sdlutils().svgs().at("game").at("scoreSpriteL").width) / float(sdlutils().images().at("scoreSprite").width());


    addComponent<TransformComponent>(e, pos);
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), renderLayer::SCORE_CONTAINER, scale);

    //segundo score

    entity_t e1 = new Entity(*this, grp::SCORE);

    b2Vec2 pos1 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreSpriteR").x,
        *&sdlutils().svgs().at("game").at("scoreSpriteR").y
    );

    addComponent<TransformComponent>(e1, pos1);
    addComponent<RenderTextureComponent>(e1, &sdlutils().images().at("scoreSprite"), renderLayer::SCORE_CONTAINER, scale);

}

void CaromScene::createFeedbackTest(b2Vec2 pos, float rot) {
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
    }
    _fastForwardPhysics = false;
    _currentState = s;
    _currentState->onStateEnter();
}

CaromScene::~CaromScene(){
    if(_currentState != nullptr) delete _currentState;

    // el mundo debe destruirse aquí, recordad que los ids son punteros con sombrero y gabardina
    b2DestroyWorld(_myB2WorldId);

    delete _hitManager;
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
    #endif

    if(ih().keyDownEvent() && ih().isKeyDown(SDLK_l)){ 
        // Al presionar la "L" te lleva a la escena de ganar.
            /*std::cout << "Carga escena de PERDER." << std::endl;
            NullState* state = new NullState(nullptr);

            // !!! CREA ENDGAMESCENE.
            GameScene*ms = new EndGameScene(game); // ! tst  
            game->getScenesManager()->pushScene(ms);*/

            // para activar invokeLose();
            _remainingHits = 0;
    }

    if(ih().keyDownEvent() && ih().isKeyDown(SDLK_w)){
        // Al presionar la "W" te lleva a la escena de perder.
            /*std::cout << "Carga escena GANAR." << std::endl;
            NullState* state = new NullState(nullptr);
            GameScene *ms = new RewardScene(game); // ! tst  
            game->getScenesManager()->pushScene(ms);*/

        // para activar roundwins();
        _currentScore = 2 * _scoreToBeat;
    }

}

void CaromScene::setCanFastForward(bool active)
{
    _canFastForwardPhysics = active;
    _fastForwardPhysics = false;
}

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
    // std::cout<< "Start Change state" << std::endl;
    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    // std::cout<< "End Change state" << std::endl;
    
    _hitManager->clearAllHits();

    // std::cout<< "START GameScene Update" << std::endl;
    GameScene::update();
    // std::cout<< "END GameScene Update" << std::endl;
}

void CaromScene::update()
{
    // Iterations purpose for fast forwarding
    int iterations;
    if (_fastForwardPhysics)
        iterations = _fastForwardIterations;
    else
        iterations = 1;

    for (int i = 0; i < iterations; ++i){
        // std::cout<< "UpdatePhysics 1" << std::endl;
        updatePhysics();
        // std::cout<< "UpdatePhysics 2" << std::endl;
        updatePhysics();
        // std::cout<< "UpdateScene inicio" << std::endl;
        updateScene(); 
    }
}

b2BodyId CaromScene::addBodyToWorld(b2BodyDef bodyDef){
    return b2CreateBody(_myB2WorldId, &bodyDef);
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

        // Null check: entities might have been destroyed
        if (ent1 && ent2) {
            ent1->getComponent<RigidBodyComponent>()->onCollisionEnter(ent2);
            ent2->getComponent<RigidBodyComponent>()->onCollisionEnter(ent1);
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
            std::cout << "Invalid shape in manageExitTriggers" << std::endl;
            continue;
        }
        
        entity_t sensor = static_cast<entity_t>(b2Shape_GetUserData(a_exit->sensorShapeId));
        entity_t visitor = static_cast<entity_t>(b2Shape_GetUserData(a_exit->visitorShapeId));
        
        // Null check: entities might have been destroyed
        if (sensor && visitor) {
            std::cout << "Trigger exit" <<  std::endl;
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
    scoreToBeatObject->addComponent(new TextDisplayComponent(scoreToBeatObject, renderLayer::SCORE, 1, "1000", 
        {255, 255, 255, 255}, "Basteleur-Moonlight48"));

    return currentDisplay;
}

void CaromScene::addScore(int score) {
    _currentScore += score;
    _currentScoreDisplay->setDisplayedText(std::to_string(_currentScore));
}

void CaromScene::removeScore(int score) {
    _currentScore -= score;
    _currentScoreDisplay->setDisplayedText(std::to_string(_currentScore));
}

void CaromScene::setScoreToBeat(int score){
    _scoreToBeat = score; 
}

void CaromScene::decrementRemainingHits()
{
    if (_remainingHits > 0) {
        --_remainingHits;
        _remainingHitsDisplay->setDisplayedText(std::to_string(_remainingHits));
    }
}



//---------------------------BOSS---------------------------------

void CaromScene::playBossTurn() {
    // std::cout<< "Play Boss Turn" << std::endl;
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
    std::cout << "aplicando modificador de boss desde CaromScene" << std::endl;
    _currentState->finish();
}

void 
CaromScene::loadFromInventory() {
    _fromInventory = true; //!PROVISIONAL: Para no eliminar la destructora de escena por defecto aún

    InventoryManager* inventory = InventoryManager::Instance();
    
    entity_t whiteBall = inventory->getWhiteBall();
    whiteBall->setGameScene(this);
    _entities.push_back(whiteBall);
    _entsRenderable.push_back(whiteBall);

    auto effectBalls = inventory->getEffectBalls();
    for(entity_t ball : effectBalls) {
        ball->setGameScene(this);
        _entities.push_back(ball);
        _entsRenderable.push_back(ball);
    }

    entity_t stick = inventory->getStick();
    stick->setGameScene(this);
    _entities.push_back(stick);
    _entsRenderable.push_back(stick);
}
