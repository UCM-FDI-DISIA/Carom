#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"
#include "Texture.h"

class ScenesManager;
class RNG_Manager;
class b2WorldId;
class Vector2D;
class ScoreContainer;
class InputHandler;


namespace ecs{

    class ColorHitManager;
    class TextDisplayComponent;

    
    class CaromScene: public GameScene {
    //--------------------BASIC SCENE FUNCTIONALITY------------------------
    protected:
        ScenesManager* _sceneManager;
        GameScene* _reward; //La recompensa al completar la escena
        int _remainingHits = 3;

        bool _fastForwardPhysics = false;
        int _fastForwardIterations = 10;

        bool _canRestart = false; // ! DEBUG

        void updatePhysics() override;
        void updateScene() override;
    public:
        CaromScene(State* state, Game* g, GameScene* reward);
        virtual ~CaromScene();

        void handleEvent() override;
        void setCanFastForward(bool active) override;
        //Llama al update de todas las entidades de escena y maneja las físicas
        void update() override;

        inline ScenesManager* getScenesManager() const {return _sceneManager;}
        inline GameScene* getRewardScene() const {return _reward;}

        // Métodos para comprobar condiciones de estado 
        inline int getRemainingHits() { return _remainingHits; }

    //---------------------------STATE MACHINE-----------------------------
    protected:
        //el estado en el que se encuentra la escena actualmente
        State* _currentState = nullptr;
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
        int _currentScore = 0, _scoreToBeat = 10; 
        ColorHitManager* _hitManager; //El gestor de golpes entre bolas de color
    public:
        TextDisplayComponent* createScoreUI();

        inline ColorHitManager* getColorHitManager() { return _hitManager; }
        inline double getCurrentScore() { return _currentScore; }
        inline double getScoreToBeat() { return _scoreToBeat; }

        // ?Métodos para manejo de puntuación
        void setScoreToBeat(int newScoreToBeat);
        void addScore(int score);
        void removeScore(int score);
        
        inline bool roundWins() {return _currentScore >= _scoreToBeat; }

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

    //---------------------------ENTITY CREATION---------------------------------
    public:
        entity_t createStick();

        entity_t createWhiteBall(const b2Vec2& pos, b2BodyType type, float density, float friction, float restitution); 

        void createEffectBall(ecs::effect::effectId effectId, const b2Vec2& pos, b2BodyType type, 
                                float density, float friction, float restitution);

        void createEffectBalls(int n);
        
        void createBallShadow(entity_t);

        void createScoreEntity();

    private:
        // Extraido de: https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
        void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

    
    //---------------------------BOSS---------------------------------
    public:
        enum Boss {
            COWBOY_POOL = 0,
            RUSSIAN_PYRAMID = 1,
            NONE
        };
        
        inline bool isBossMatch() {return _boss != Boss::NONE; }
        void playBossTurn();

    protected:
        Boss _boss = Boss::NONE;
        virtual void clearBossModifiers();
        virtual void applyBossModifiers(); // Implementar en cada subtipo de CaromScene
    };
}
