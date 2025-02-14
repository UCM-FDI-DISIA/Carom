#include "MainScene.h"

MainScene::MainScene(State* s, Game* g): GameScene(g){
    setNewState(s);
}

void MainScene::setNewState(State* s){
    _currentState->onStateExit();
    delete _currentState;
    _currentState = s;
    _currentState->onStateEnter();
}

State* MainScene::getCurrentState(){ return _currentState;}

MainScene::~MainScene(){
    if(_currentState != nullptr) delete _currentState;
}

void MainScene::update(){
    State* a_stateToChange = nullptr;
    if(_currentState->checkCondition(a_stateToChange)){
        setNewState(a_stateToChange);
    }
    _currentState->update();
    GameScene::update();
}