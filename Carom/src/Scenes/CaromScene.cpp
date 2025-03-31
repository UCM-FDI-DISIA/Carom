#include "CaromScene.h"

#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "CircleRBComponent.h"
#include "ColorHitManager.h"
#include "WhiteBallScorerComponent.h"
#include "StickInputComponent.h"
#include "Button.h"
#include "TextDisplayComponent.h"
#include "ColorBallScorerComponent.h"
#include "RNG_Manager.h"
#include "RandomItem.h"
#include "FollowComponent.h"
#include "StartMatchState.h"

#include "PhysicsUtils.h"
#include "Game.h"
#include "Vector2D.h"
#include "vector"
#include <box2d/box2d.h>

CaromScene::CaromScene(State* s, Game* g, GameScene* reward) : GameScene(g), _reward(reward), _updatePhysics(true) , _currentScore(0), _scoreToBeat(1000)
{
    // SEEDING
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
    
    // BALL TEST
    // Converts (x, y) from screen(svg) to meters and to meter coordinates
    b2Vec2 wb_pos = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("bola_blanca").x,
        *&sdlutils().svgs().at("game").at("bola_blanca").y
    );
    createWhiteBall(wb_pos, b2_dynamicBody, 1, 0.2, 1, 10);
    std::cout << sdlutils().svgs().at("game").size();
    // Apply impulse
    getEntitiesOfGroup(grp::WHITEBALL)[0]->getComponent<RigidBodyComponent>()->applyImpulseToCenter({0.0f, 0.0f});

    // EFFECT BALLS
    int n_eb = 3;
    int npos = sdlutils().svgElements_ballPos().size();
    assert(n_eb <= npos);

    std::vector<RandomItem<int>> positions;
    for(int i = 1; i <= npos; ++i)
        positions.push_back(RandomItem(i, 1.0f));

    std::vector<int> eb_selected_pos = _rngManager->getRandomItems(positions, n_eb, false);

    for(int i = 0; i < n_eb; ++i) {
        std::string s = "bola";
        if(eb_selected_pos[i] > 1)
            s += ("_" + std::to_string(eb_selected_pos[i]));
        
        auto& eb = sdlutils().svgElements_ballPos().at(s);
        auto eb_pos = PhysicsConverter::pixel2meter(eb.x, eb.y);

        createEffectBall(effect::NULO, eb_pos, b2_dynamicBody, 1, 0.2, 1, 10);
    }


    // Create table with texture and colliders
    createTable();
    createBackground("suelo");

    createScoreEntity();

    _hitManager = new ColorHitManager(this);

    _currentScoreDisplay = createScoreUI();


    setNewState(new StartMatchState(this));
}

entity_t
CaromScene::createWhiteBall(const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution, int layer) 
{
    // SCALE
    float svgSize = *&sdlutils().svgs().at("game").at("bola_blanca").width;
    float textureSize = sdlutils().images().at("bola_blanca").width();
    float scale = svgSize/textureSize;

    entity_t e = new Entity(*this, grp::WHITEBALL);

    float radius = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("bola_blanca").width/2);
    //! I don't know how to get the radius of the ball
    addComponent<CircleRBComponent>(e, pos, b2_dynamicBody, radius); 

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), layer, scale);;
    addComponent<WhiteBallScorerComponent>(e);
    Button::RadialButton rButton = Button::RadialButton(2.0);
    addComponent<Button>(e, rButton);
    e->getComponent<Button>()->setOnClick([this](){
        for (auto& e : getEntitiesOfGroup(grp::PALO))
            e->activate();
    });
    
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
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("palo1"), 20, scale);
    addComponent<StickInputComponent>(e, *&sdlutils().svgs().at("game").at("palo1").height);

    //!john cleon's stick shadow
    entity_t stickShadow = new Entity(*this, grp::PALO);
    addComponent<TransformComponent>(stickShadow, pos);
    addComponent<RenderTextureComponent>(stickShadow, &sdlutils().images().at("palo1_sombra"), 4, scale);
    addComponent<FollowComponent>(stickShadow, e, true,true,true, Vector2D{-0.05, -0.05});

    return e;
}

void
CaromScene::createEffectBall(effect::effectId effectId, const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution, int layer) {
    // Scale
    float svgSize = *&sdlutils().svgElements_ballPos().at("bola").width;
    float textureSize = sdlutils().images().at("bola_blanca").width(); // TODO: cambiar a textura effect ball
    float scale = svgSize/textureSize;        
    
    entity_t e = new Entity(*this, grp::EFFECTBALLS);
    
    // RB
    float radius = PhysicsConverter::pixel2meter(*&sdlutils().svgs().at("game").at("bola_blanca").width/2);
    addComponent<CircleRBComponent>(e, pos, type, radius);

    // RENDER
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), layer, scale, SDL_Color{0, 150, 100, 1});

    // SCORE
    addComponent<ColorBallScorerComponent>(e);

    // TODO: add components according to its id

    createBallShadow(e);
}

void CaromScene::createBallShadow(entity_t entity){
    //sombra de reflejo de la bola
    entity_t a_cast = new Entity(*this, grp::SHADOWS);

    float a_imgScale = sdlutils().images().at("bola_cast_sombra").width();

    float a_svg_scale = sdlutils().svgs().at("game").at("bola_cast_sombra 1").width;
    float cast_scale = a_svg_scale/a_imgScale;

    addComponent<TransformComponent>(a_cast, b2Vec2{0,0});
    addComponent<FollowComponent>(a_cast, entity, true, false, true, Vector2D(0,0));
    addComponent<RenderTextureComponent>(a_cast, &sdlutils().images().at("bola_cast_sombra"), 11, cast_scale);

    //sombra de la bola
    entity_t a_shadow = new Entity(*this, grp::SHADOWS);

    a_imgScale = sdlutils().images().at("bola_sombra").width();
    a_svg_scale = sdlutils().svgs().at("game").at("bola_sombra 1").width;
    cast_scale = a_svg_scale/a_imgScale;

    Vector2D a_relPos{
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").x - sdlutils().svgs().at("game").at("bola_sombra 1").x - 10),
        
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").y - sdlutils().svgs().at("game").at("bola_sombra 1").y)
    };

    addComponent<TransformComponent>(a_shadow, b2Vec2{0,0});
    addComponent<FollowComponent>(a_shadow, entity, true, false, true, a_relPos);
    addComponent<RenderTextureComponent>(a_shadow, &sdlutils().images().at("bola_sombra"), 2, cast_scale);

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
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("scoreSprite"), 0, scale);

    //segundo score

    entity_t e1 = new Entity(*this, grp::SCORE);

    b2Vec2 pos1 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreSpriteR").x,
        *&sdlutils().svgs().at("game").at("scoreSpriteR").y
    );

    addComponent<TransformComponent>(e1, pos1);
    addComponent<RenderTextureComponent>(e1, &sdlutils().images().at("scoreSprite"), 0, scale);

}

void CaromScene::setNewState(State* s){
    if (_currentState != nullptr) {
        _currentState->onStateExit();
        delete _currentState;
    }
    _currentState = s;
    _currentState->onStateEnter();
}

CaromScene::~CaromScene(){
    if(_currentState != nullptr) delete _currentState;

    // el mundo debe destruirse aquí, recordad que los ids son punteros con sombrero y gabardina
    b2DestroyWorld(_myB2WorldId);

    delete _hitManager;
}

void CaromScene::update(){

    auto a = Game::FIXED_TIME_STEP/1000.0;

    // En efecto, esto se hace 2 veces, John Cleon no me pegues
    b2World_Step(_myB2WorldId, Game::FIXED_TIME_STEP/2000.0, _b2Substeps);

    b2ContactEvents a_contactEvents = b2World_GetContactEvents(_myB2WorldId);
    manageEnterCollisions(a_contactEvents);
    manageExitCollisions(a_contactEvents);

    b2SensorEvents a_sensorEvents = b2World_GetSensorEvents(_myB2WorldId);
    manageEnterTriggers(a_sensorEvents);
    manageExitTriggers(a_sensorEvents);

    b2World_Step(_myB2WorldId, Game::FIXED_TIME_STEP/2000.0, _b2Substeps);

    a_contactEvents = b2World_GetContactEvents(_myB2WorldId);
    manageEnterCollisions(a_contactEvents);
    manageExitCollisions(a_contactEvents);

    a_sensorEvents = b2World_GetSensorEvents(_myB2WorldId);
    manageEnterTriggers(a_sensorEvents);
    manageExitTriggers(a_sensorEvents);

    enablePhysics();

    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }

    _hitManager->clearAllHits();

    GameScene::update();
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
    
    for(int i = 0; i < contactEvents.beginCount; ++i){
        b2ContactBeginTouchEvent* a_enter = contactEvents.beginEvents + i;

        entity_t ent1 = static_cast<entity_t>(b2Shape_GetUserData(a_enter->shapeIdA));
        entity_t ent2 = static_cast<entity_t>(b2Shape_GetUserData(a_enter->shapeIdB));

        ent1->getComponent<RigidBodyComponent>()->onCollisionEnter(ent2);
        ent2->getComponent<RigidBodyComponent>()->onCollisionEnter(ent1);
    }

}

void
CaromScene::manageExitCollisions(b2ContactEvents contactEvents){

    if(!_updatePhysics) return;
    
    for(int i = 0; i < contactEvents.endCount; ++i){
        b2ContactEndTouchEvent* a_exit = contactEvents.endEvents + i;
    
        entity_t ent1 = static_cast<entity_t>(b2Shape_GetUserData(a_exit->shapeIdA));
        entity_t ent2 = static_cast<entity_t>(b2Shape_GetUserData(a_exit->shapeIdB));
    
        ent1->getComponent<RigidBodyComponent>()->onCollisionExit(ent2);
        ent2->getComponent<RigidBodyComponent>()->onCollisionExit(ent1);
    }
    
}

void
CaromScene::manageEnterTriggers(b2SensorEvents sensorEvents){

    if(!_updatePhysics) return;

    for(int i = 0; i < sensorEvents.beginCount; ++i){
        b2SensorBeginTouchEvent* a_enter = sensorEvents.beginEvents + i;

        entity_t sensor = static_cast<entity_t>(b2Shape_GetUserData(a_enter->sensorShapeId));
        entity_t visitor = static_cast<entity_t>(b2Shape_GetUserData(a_enter->visitorShapeId));

        sensor->getComponent<RigidBodyComponent>()->onTriggerEnter(visitor);
    }
}

void
CaromScene::manageExitTriggers(b2SensorEvents sensorEvents){

    if(!_updatePhysics) return;

    for(int i = 0; i < sensorEvents.endCount; ++i){
        b2SensorEndTouchEvent* a_exit = sensorEvents.endEvents + i;
    
        entity_t sensor = static_cast<entity_t>(b2Shape_GetUserData(a_exit->sensorShapeId));
        entity_t visitor = static_cast<entity_t>(b2Shape_GetUserData(a_exit->visitorShapeId));
    
        sensor->getComponent<RigidBodyComponent>()->onTriggerExit(visitor);
    } 

}

TextDisplayComponent*
CaromScene::createScoreUI() {
    //CurrentScore
    entity_t currentScoreObject = new Entity(*this, grp::SCORE);
    _entsRenderable.push_back(currentScoreObject);

    b2Vec2 pos1 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreTextL").x,
        *&sdlutils().svgs().at("game").at("scoreTextL").y
    );

    currentScoreObject->addComponent(new TransformComponent(currentScoreObject, pos1));
    TextDisplayComponent* currentDisplay = new TextDisplayComponent(currentScoreObject, 1, 1.6, "0", {255, 255, 255, 255}, "Basteleur-Moonlight24");
    currentScoreObject->addComponent(currentDisplay);

    //Score to beat
    entity_t scoreToBeatObject = new Entity(*this, grp::SCORE);
    _entsRenderable.push_back(scoreToBeatObject);

    b2Vec2 pos2 = PhysicsConverter::pixel2meter(
        *&sdlutils().svgs().at("game").at("scoreTextR").x,
        *&sdlutils().svgs().at("game").at("scoreTextR").y
    );

    scoreToBeatObject->addComponent(new TransformComponent(scoreToBeatObject, pos2));         
    scoreToBeatObject->addComponent(new TextDisplayComponent(scoreToBeatObject, 1, 1.6, "1000", {255, 255, 255, 255}, "Basteleur-Moonlight24"));

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