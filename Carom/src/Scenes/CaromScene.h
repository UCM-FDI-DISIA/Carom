#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"
#include "ecs.h"

#include <memory>

class RNG_Manager;
class b2WorldId;
class Vector2D;
class ScoreContainer;
class InputHandler;
class ScenesManager;
class ColorHitManager;
class TextDisplayComponent;
class StickInputComponent;
class RoundScoreAnimComponent;
class AudioManager;

    
class CaromScene: public GameScene {
//--------------------BASIC SCENE FUNCTIONALITY------------------------
protected:
    int _remainingHits = 10;

    ScenesManager* _sceneManager;
    std::shared_ptr<GameScene> _reward; //La recompensa al completar la escena

    void updatePhysics() override;
    void updateScene() override;
public:
//si quieres que caromScene comience con un estado distinto al de la partida normal, introduce el estado nuevo
    CaromScene(Game* g, State* state = nullptr);
    virtual ~CaromScene();

    void init() override;
    void initObjects() override;
    void initFunctionalities() override;
    void initGimmick() override {};
    void initBoss() override{};

    void handleEvent() override;
    //Llama al update de todas las entidades de escena y maneja las físicas
    void update() override;

    inline ScenesManager* getScenesManager() const {return _sceneManager;}
    inline std::shared_ptr<GameScene> getRewardScene() const {return _reward;}

    // Métodos para comprobar condiciones de estado 
    inline int getRemainingHits() { return _remainingHits; }

    void decrementRemainingHits();

//---------------------------STATE MACHINE-----------------------------
protected:
    //el estado en el que se encuentra la escena actualmente
    State* _currentState;
public:
    //Cambiar el estado actual por uno nuevo. Flujo sería:
    //- Llama a onStateExit() del estado a cambiar
    //- Cambia el estado por el nuevo
    //- Llama a onStateEnter() del nuevo estado
    void setNewState(State* s);

    inline State* getCurrentState() { return _currentState; }

//-------------------------------SCORE---------------------------------------
protected:
    TextDisplayComponent* _currentScoreDisplay;
    //Los acumuladores de puntuación
    int _currentScore = 0, _roundScore = 0, _scoreToBeat = 1000; 
    ColorHitManager* _hitManager; //El gestor de golpes entre bolas de color
    TextDisplayComponent* _remainingHitsDisplay;
    TextDisplayComponent* _roundScoreDisplay;
    RoundScoreAnimComponent* _roundScorer;
public:
    TextDisplayComponent* createScoreUI();
    TextDisplayComponent* createRoundScoreUI();
    TextDisplayComponent* createRemainingHitsUI();
    inline ColorHitManager* getColorHitManager() { return _hitManager; }
    inline double getRoundScore() {return _roundScore; }
    inline double getCurrentScore() { return _currentScore; }
    inline double getScoreToBeat() { return _scoreToBeat; }

    // ?Métodos para manejo de puntuación
    void setScoreToBeat(int newScoreToBeat);
    void addScore(int score);
    void addToTotalScore(int score);
    void removeScore(int score);
    void removeFromTotalScore(int score);

    void addPointsFromRound(); // Para mandar los puntos de ronda a la puntuación final
    
    inline bool roundWins() {return (_currentScore + _roundScore) >= _scoreToBeat; }
    b2Vec2 distanceToWhiteBall(b2Vec2 point);

//------------------------------MANAGERS-------------------------------------
protected:
    RNG_Manager* _rngManager;

//------------------------------PHYSICS--------------------------------------
protected:
    b2WorldId _myB2WorldId; //El mundo de box2D

    bool _updatePhysics; // * Se usa para gestionar problemas con las físicas

    // Dividido /1000 porque b2 trabaja en segundos con float
    float const _b2timeSteps = Game::FIXED_TIMESTEP / 2000.0f;
    // Esto de momento se inicializa en 4, no manipular
    int _b2Substeps = 4;

    // Métodos hechos por claridad, puedes meter los 4 bucles for a pelo en el update si eres un terrorista
    void manageEnterCollisions(b2ContactEvents enterContactEvents);
    void manageExitCollisions(b2ContactEvents exitContactEvents);
    void manageEnterTriggers(b2SensorEvents enterSensorEvents);
    void manageExitTriggers(b2SensorEvents exitSensorEvents);

public:
    inline void enablePhysics(){_updatePhysics = true;}
    inline void disablePhysics(){_updatePhysics = false;}

    /// @brief Método para que rigidbody component reciba el id del body
    b2BodyId addBodyToWorld(b2BodyDef bodyDef);
    b2RayResult castRayToWorld(b2Vec2 origin, b2Vec2 translation);

//---------------------------ENTITY CREATION---------------------------------
public:
    entity_t createStick();

    entity_t createWhiteBall(const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution); 

    virtual void createEffectBalls();
    
    void createBallShadow(entity_t);

    void createScoreEntity();

    void createFeedbackTest(b2Vec2 pos, float rot);

protected:
    // Extraido de: https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
    void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
    StickInputComponent* _stickInput;

//---------------------------BOSS---------------------------------
public:
    enum Boss {
        COWBOY_POOL = 0,
        RUSSIAN_PYRAMID = 1,
        NONE
    };
    
    inline bool isBossMatch() {return _boss != Boss::NONE; }
    void playBossTurn();

    void instantiateBossTableShadow();

protected:
    Boss _boss = Boss::NONE;
    virtual void clearBossModifiers();
    virtual void applyBossModifiers(); // Implementar en cada subtipo de CaromScene

//------------------------INVENTORY------------------------
protected: 
    void loadFromInventory();
    bool _fromInventory = false;


#ifdef _DEBUG
    public:
        void setCanFastForward(bool active) override;

    protected:
        bool _fastForwardPhysics = false;
        int _fastForwardIterations = 10;
        bool _canRestart = false;
#endif

// -----------------INDICATOR----------------------
public:
    void changeIndicator(entity_t whiteBall);
    void activateIndicator();
    void deactivateIndicator();
protected:
    entity_t _indicator;
    void createIndicator(entity_t whiteBall);
};
