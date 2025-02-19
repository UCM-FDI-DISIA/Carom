#pragma once
#include "GameScene.h"
#include "State.h"

class ScenesManager;
class CaromScene: public ecs::GameScene {
protected:
//el estado en el que se encuentra la escena actualmente
    State* _currentState = nullptr;
    ScenesManager* _manager;
    GameScene* _reward;
public:
    CaromScene(State* s, Game* g, GameScene* reward);
    ~CaromScene();

    void createWhiteBall(Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius); // TODO: provisory definition

	void createEffectBall(ecs::effect::effectId effectId, Vector2D pos, b2BodyType type, float density, float friction, float restitution, float radius); // TODO: provisory definition

	void createTable(/* type, etc */); // TODO: provisory definition

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

    inline ScenesManager* getScenesManager() const {return _manager;}
    inline GameScene* getRewardScene() const {return _reward;}
};