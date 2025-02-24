#pragma once
#include "GameScene.h"
#include "State.h"
#include "Game.h"

class ScenesManager;
class b2WorldId;
class Vector2D;
class ScoreContainer;


namespace ecs{

    class ColorHitManager;

class CaromScene: public GameScene {
protected:
//el estado en el que se encuentra la escena actualmente
    State* _currentState = nullptr;
    ScenesManager* _manager;
    GameScene* _reward;
    ColorHitManager* _hitManager;
    ScoreContainer* _scoreContainer;

    b2WorldId _myB2WorldId;

    // Dividido /1000 porque b2 trabaja en segundos con float
    const float _b2timeSteps = Game::FIXED_TIME_STEP / 1000;
    // Esto de momento se inicializa en 4, no manipular
    int _b2Substeps = 4;

    // Métodos hechos por claridad, puedes meter los 4 bucles for a pelo en el update si eres un terrorista
    void manageEnterCollisions(b2ContactEvents enterContactEvents);
    void manageExitCollisions(b2ContactEvents exitContactEvents);
    void manageEnterTriggers(b2SensorEvents enterSensorEvents);
    void manageExitTriggers(b2SensorEvents exitSensorEvents);
    
public:
    CaromScene(State* s, Game* g, GameScene* reward);
    ~CaromScene();

    // TODO: provisory definition
    void createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius, int capa); 

    // TODO: provisory definition
	void createEffectBall(ecs::effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius);
    
    //Cambiar el estado actual por uno nuevo. Flujo sería:
    //- Llama a onStateExit() del estado a cambiar
    //- Cambia el estado por el nuevo
    //- Llama a onStateEnter() del nuevo estado
    void setNewState(State* s);
    //Reproduce:
    //- update() del estado actual (si tuviera algun comportamiento especifico)
    //- update() de todas las entidades de la escena
    void update() override;
    //devuelve el estado en el que se encuentra la escena principal
    State* getCurrentState();
    ColorHitManager* getColorHitManager();
    ScoreContainer* getScoreContainer();

    inline ScenesManager* getScenesManager() const {return _manager;}
    inline GameScene* getRewardScene() const {return _reward;}
    /// @brief Método para que rigidbody component reciba el id del body
    /// @param bodyType kinematic, static, dynamic
    /// @param density Kg/m2 >= 0
    /// @param friction Roce (0.0 , 1.0)
    /// @param restitution Rebote/Elasticidad (0.0, 1.0)
    /// @return 
    std::pair<b2BodyId, b2ShapeDef*> generateBodyAndShape ( ecs::entity_t ent, const Vector2D& vec, b2BodyType bodyType, 
        float density, float friction, float restitution);
};
}