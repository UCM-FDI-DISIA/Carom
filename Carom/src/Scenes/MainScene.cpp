#include "MainScene.h"

MainScene::MainScene(State* s, Game* g): GameScene(g){
    setNewState(s);
}

void MainScene::setNewState(State* s){
    _currentState->onStateExit();
    delete _currentState;
    _currentState = s;
}

State* MainScene::getCurrentState(){ return _currentState;}

MainScene::~MainScene(){
    if(_currentState != nullptr) delete _currentState;
}

void MainScene::update(){
    State* a_sceneToChange = nullptr;
    if(_currentState->checkCondition(a_sceneToChange)){
        setNewState(a_sceneToChange);
    }
    _currentState->update();
    GameScene::update();
}